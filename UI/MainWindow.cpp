/*
    Combox - A comment formatter
    Copyright (C) 2024  Martial Demolins

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "MainWindow.hpp"
#include "../Global.hpp"
#include "../Settings.hpp"
#include "./ui_MainWindow.h"
#include "DlgSettings.hpp"
#include <QClipboard>
#include <QGuiApplication>
#include <QList>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , GenerationTimer(new QTimer(this))
    , CopyShortcut(new QShortcut(this))
{
    ui->setupUi(this);
    setWindowTitle(APPLICATION_NAME);

    // Generation timer
    this->GenerationTimer->setSingleShot(true);           // Update output only once when fired
    this->GenerationTimer->setTimerType(Qt::CoarseTimer); // 5% accuracy

    // Copy shortcut
    connect(this->CopyShortcut, &QShortcut::activated, this, [this]() { QGuiApplication::clipboard()->setText(ui->TextEditOutput->toPlainText()); });

    // Update box settings
    ui->SpinBoxIndent->setValue(Settings::instance()->indentCount());
    ui->SpinBoxTabSize->setValue(Settings::instance()->tabSize());

    // Update local settings and output
    updateSettings();
    updateOutput();

    // Connections
    connect(ui->ButtonCopy, &QPushButton::clicked, this, [this]() { QGuiApplication::clipboard()->setText(ui->TextEditOutput->toPlainText()); });
    connect(ui->ButtonSettings, &QPushButton::clicked, this, [this]() { execDlgSettings(); });
    connect(ui->SpinBoxIndent, &QSpinBox::valueChanged, this, [this]() { this->GenerationTimer->start(GENERATION_DELAY); });
    connect(ui->SpinBoxTabSize, &QSpinBox::valueChanged, this, [this]() { this->GenerationTimer->start(GENERATION_DELAY); });
    connect(ui->TextEditInput, &QPlainTextEdit::textChanged, this, [this]() { this->GenerationTimer->start(GENERATION_DELAY); });
    connect(this->GenerationTimer, &QTimer::timeout, this, [this]() { updateOutput(); });
}

MainWindow::~MainWindow()
{
    Settings::release();
    delete ui;
}

void MainWindow::execDlgSettings()
{
    if (DlgSettings::execDlgSettings(this)) {
        updateSettings();
        updateOutput();
    }
}

void MainWindow::updateSettings()
{
    this->TopLeft      = Settings::instance()->topLeft();
    this->TopCenter    = Settings::instance()->topCenter();
    this->TopRight     = Settings::instance()->topRight();
    this->MiddleLeft   = Settings::instance()->middleLeft();
    this->MiddleRight  = Settings::instance()->middleRight();
    this->BottomLeft   = Settings::instance()->bottomLeft();
    this->BottomCenter = Settings::instance()->bottomCenter();
    this->BottomRight  = Settings::instance()->bottomRight();
    this->EmptyLines   = Settings::instance()->emptyLines();
    this->Width        = Settings::instance()->width();
    this->AutoCopy     = Settings::instance()->autoCopyToClipboard();
    this->CopyShortcut->setKey(Settings::instance()->copyShortcut());
}

void MainWindow::updateOutput()
{
    // Output string. Will be echoed in the output box
    QString Output;

    // Comment lines stuff
    QString     CommentSpace;                                               // Temp string containing the spaces on each side of the comments
    QStringList CommentLines(ui->TextEditInput->toPlainText().split('\n')); // List of the lines in the input box

    // Indentation
    int     IndentSize = ui->SpinBoxIndent->value() * ui->SpinBoxTabSize->value(); // Number of spaces of the indentation space
    QString IndentStr(IndentSize, ' ');                                            // Intendation string, full of spaces

    // Compute real width, adapted to the longest comment line
    int RealWidth = Width;
    for (int i = 0; i < CommentLines.size(); i++) {
        int LineWidth = IndentSize + MiddleLeft.size() + CommentLines.at(i).size() + MiddleRight.size();
        RealWidth     = LineWidth > RealWidth ? LineWidth : RealWidth;
    }

    // Compute intermediate lines (between the top line and the comment, then between the comment and the bottom line)
    QString IntermediateLine; // A line between the top one and the comment section
    QString Center;           // Tmp string to quickly generate the list of spaces in the center
    int     TmpWidth;         // Used to build the lines

    if (EmptyLines != 0) {
        IntermediateLine.append(IndentStr).append(MiddleLeft);                      // Put the left part
        TmpWidth = RealWidth - IndentSize - MiddleLeft.size() - MiddleRight.size(); // Size of the center
        Center.fill(' ', TmpWidth);                                                 // Set the string contaning the middle
        IntermediateLine.append(Center).append(MiddleRight).append('\n');           // Finalize the line
    }

    // Upper line
    Output.append(IndentStr).append(TopLeft);                             // Put top left corner
    TmpWidth = RealWidth - IndentSize - TopLeft.size() - TopRight.size(); // Size of the center
    while (TmpWidth > TopCenter.size()) {                                 // While the available center size is greater that the pattern of the center
        TmpWidth -= TopCenter.size();                                     // Update center size
        Output.append(TopCenter);                                         // And push back the center pattern
    }
    Output.append(TopCenter.first(TmpWidth)); // Complete the center if the pattern does not fit exactly the available space
    Output.append(TopRight).append('\n');     // Finally, put the top right corner and go to the next line

    // Intermediate lines
    for (int i = 0; i < EmptyLines; i++) {
        Output.append(IntermediateLine);
    }

    // Comments
    for (int i = 0; i < CommentLines.count(); i++) {
        Output.append(IndentStr).append(MiddleLeft);
        TmpWidth = RealWidth - IndentSize - MiddleLeft.size() - CommentLines.at(i).size() - MiddleRight.size();
        CommentSpace.fill(' ', TmpWidth / 2);
        Output.append(CommentSpace).append(CommentLines.at(i)).append(CommentSpace);
        if (TmpWidth % 2) {
            Output.append(' ');
        }
        Output.append(MiddleRight).append('\n');
    }

    // Intermediate lines
    for (int i = 0; i < EmptyLines; i++) {
        Output.append(IntermediateLine);
    }

    // Lower line
    Output.append(IndentStr).append(BottomLeft);                                // Put the bottom left corner
    TmpWidth = RealWidth - IndentSize - BottomLeft.size() - BottomRight.size(); // Size of the center
    while (TmpWidth > BottomCenter.size()) {                                    // While the available center size is greater that the pattern of the center
        TmpWidth -= BottomCenter.size();                                        // Update center size
        Output.append(BottomCenter);                                            // And push back the center pattern
    }
    Output.append(BottomCenter.first(TmpWidth)); // Complete the center if the pattern does not fit exactly the available space
    Output.append(BottomRight).append('\n');     // Finally, put the top right corner and go to the next line

    // Update output box
    ui->TextEditOutput->setPlainText(Output);

    // Copy to clipboard according to settings
    if (this->AutoCopy) {
        QGuiApplication::clipboard()->setText(Output);
    }
}

// Select the text in the input box and give it the focus on windows activation
bool MainWindow::event(QEvent* event)
{
    if (event->type() == QEvent::WindowActivate) {
        ui->TextEditInput->setFocus();
        ui->TextEditInput->selectAll();
    }
    return QMainWindow::event(event);
}
