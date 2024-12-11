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
#include "DlgAbout.hpp"
#include "DlgSettings.hpp"
#include <QClipboard>
#include <QFont>
#include <QFontMetrics>
#include <QGuiApplication>
#include <QList>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , GenerationTimer(this)
    , CopyShortcut(this)
    , IncreaseEmptyLinesShortcut(this)
    , DecreaseEmptyLinesShortcut(this)
    , IncreaseTabSizeShortcut(this)
    , DecreaseTabSizeShortcut(this)
    , IncreaseIndentShortcut(this)
    , DecreaseIndentShortcut(this)
    , IncreaseWidthShortcut(this)
    , DecreaseWidthShortcut(this)
{
    ui->setupUi(this);
    setWindowTitle(APPLICATION_NAME);

    // Generation timer
    this->GenerationTimer.setSingleShot(true);           // Update output only once when fired
    this->GenerationTimer.setTimerType(Qt::CoarseTimer); // 5% accuracy

    // Copy shortcut
    connect(&this->CopyShortcut, &QShortcut::activated, [this]() { QGuiApplication::clipboard()->setText(ui->TextEditOutput->toPlainText()); });

    // Update box settings
    ui->SpinBoxIndent->setValue(Settings::instance()->indentCount());
    ui->SpinBoxTabSize->setValue(Settings::instance()->tabSize());
    ui->SpinBoxEmptyLines->setValue(Settings::instance()->emptyLines());
    ui->SpinBoxWidth->setValue(Settings::instance()->width());
    ui->SpinBoxWidth->setSingleStep(STEP_WIDTH);

    // Update local settings and output
    updateConfiguration();
    updateOutput();

    // Buttons connections
    connect(ui->ButtonSettings, &QPushButton::clicked, this, &MainWindow::execDlgSettings);
    connect(ui->ButtonCopy, &QPushButton::clicked, [this]() { QGuiApplication::clipboard()->setText(ui->TextEditOutput->toPlainText()); });
    connect(ui->ButtonAbout, &QPushButton::clicked, [this]() { DlgAbout::execDlgAbout(this); });

    // Settings connections
    connect(ui->SpinBoxIndent, &QSpinBox::valueChanged, [this]() { this->GenerationTimer.start(GENERATION_DELAY); });
    connect(ui->SpinBoxTabSize, &QSpinBox::valueChanged, [this]() { this->GenerationTimer.start(GENERATION_DELAY); });
    connect(ui->SpinBoxEmptyLines, &QSpinBox::valueChanged, [this]() { this->GenerationTimer.start(GENERATION_DELAY); });
    connect(ui->SpinBoxWidth, &QSpinBox::valueChanged, [this]() { this->GenerationTimer.start(GENERATION_DELAY); });
    connect(ui->TextEditInput, &QPlainTextEdit::textChanged, [this]() { this->GenerationTimer.start(GENERATION_DELAY); });
    connect(&this->GenerationTimer, &QTimer::timeout, this, &MainWindow::updateOutput);

    // Shortcuts connections
    connect(&this->IncreaseEmptyLinesShortcut, &QShortcut::activated, [this]() { ui->SpinBoxEmptyLines->setValue(ui->SpinBoxEmptyLines->value() + 1); });
    connect(&this->DecreaseEmptyLinesShortcut, &QShortcut::activated, [this]() { ui->SpinBoxEmptyLines->setValue(ui->SpinBoxEmptyLines->value() - 1); });
    connect(&this->IncreaseIndentShortcut, &QShortcut::activated, [this]() { ui->SpinBoxIndent->setValue(ui->SpinBoxIndent->value() + 1); });
    connect(&this->DecreaseIndentShortcut, &QShortcut::activated, [this]() { ui->SpinBoxIndent->setValue(ui->SpinBoxIndent->value() - 1); });
    connect(&this->IncreaseTabSizeShortcut, &QShortcut::activated, [this]() { ui->SpinBoxTabSize->setValue(ui->SpinBoxTabSize->value() + 1); });
    connect(&this->DecreaseTabSizeShortcut, &QShortcut::activated, [this]() { ui->SpinBoxTabSize->setValue(ui->SpinBoxTabSize->value() - 1); });
    connect(&this->IncreaseWidthShortcut, &QShortcut::activated, [this]() { ui->SpinBoxWidth->setValue(ui->SpinBoxWidth->value() + STEP_WIDTH); });
    connect(&this->DecreaseWidthShortcut, &QShortcut::activated, [this]() { ui->SpinBoxWidth->setValue(ui->SpinBoxWidth->value() - STEP_WIDTH); });
}

MainWindow::~MainWindow()
{
    // Save and close settings
    // Settings managed by DlgSettings have already been pushed to the Settings object.
    // The local settings of MainWindow have to be saved separately
    Settings::instance()->setEmptyLines(ui->SpinBoxEmptyLines->value());
    Settings::instance()->setWidth(ui->SpinBoxWidth->value());
    Settings::instance()->setIndentCount(ui->SpinBoxIndent->value());
    Settings::instance()->setTabSize(ui->SpinBoxTabSize->value());
    Settings::release();

    delete ui;
}

void MainWindow::execDlgSettings()
{
    if (DlgSettings::execDlgSettings(this)) {
        updateConfiguration();
        updateOutput();
    }
}

void MainWindow::updateConfiguration()
{
    // These are shortcuts to avoid triggering the QSettings factory while crafting the output box
    this->TopLeft      = Settings::instance()->topLeft();
    this->TopCenter    = Settings::instance()->topCenter();
    this->TopRight     = Settings::instance()->topRight();
    this->MiddleLeft   = Settings::instance()->middleLeft();
    this->MiddleRight  = Settings::instance()->middleRight();
    this->BottomLeft   = Settings::instance()->bottomLeft();
    this->BottomCenter = Settings::instance()->bottomCenter();
    this->BottomRight  = Settings::instance()->bottomRight();

    // Shortcuts string
    QString IncreaseEmptyLinesString = Settings::instance()->increaseEmptyLinesShortcut();
    QString DecreaseEmptyLinesString = Settings::instance()->decreaseEmptyLinesShortcut();
    QString IncreaseTabSizeString    = Settings::instance()->increaseTabSizeShortcut();
    QString DecreaseTabSizeString    = Settings::instance()->decreaseTabSizeShortcut();
    QString IncreaseIndentString     = Settings::instance()->increaseIndentShortcut();
    QString DecreaseIndentString     = Settings::instance()->decreaseIndentShortcut();
    QString IncreaseWidthString      = Settings::instance()->increaseWidthShortcut();
    QString DecreaseWidthString      = Settings::instance()->decreaseWidthShortcut();

    // Shortcuts keys
    this->CopyShortcut.setKey(Settings::instance()->copyShortcut());
    this->IncreaseEmptyLinesShortcut.setKey(IncreaseEmptyLinesString);
    this->DecreaseEmptyLinesShortcut.setKey(DecreaseEmptyLinesString);
    this->IncreaseTabSizeShortcut.setKey(IncreaseTabSizeString);
    this->DecreaseTabSizeShortcut.setKey(DecreaseTabSizeString);
    this->IncreaseIndentShortcut.setKey(IncreaseIndentString);
    this->DecreaseIndentShortcut.setKey(DecreaseIndentString);
    this->IncreaseWidthShortcut.setKey(IncreaseWidthString);
    this->DecreaseWidthShortcut.setKey(DecreaseWidthString);

    // Tooltips
    if (!Settings::instance()->copyShortcut().isEmpty()) {
        ui->ButtonCopy->setToolTip(QString("Shortcut: %1").arg(Settings::instance()->copyShortcut()));
    }

    ui->SpinBoxEmptyLines->setToolTip("");
    if (!IncreaseEmptyLinesString.isEmpty() && !DecreaseEmptyLinesString.isEmpty()) {
        ui->SpinBoxEmptyLines->setToolTip(QString("%1 to increase, %2 to decrease").arg(IncreaseEmptyLinesString).arg(DecreaseEmptyLinesString));
        ui->LabelEmptyLines->setToolTip(QString("%1 to increase, %2 to decrease").arg(IncreaseEmptyLinesString).arg(DecreaseEmptyLinesString));
    }

    ui->SpinBoxIndent->setToolTip("");
    if (!IncreaseIndentString.isEmpty() && !DecreaseIndentString.isEmpty()) {
        ui->SpinBoxIndent->setToolTip(QString("%1 to increase, %2 to decrease").arg(IncreaseIndentString).arg(DecreaseIndentString));
        ui->LabelIndent->setToolTip(QString("%1 to increase, %2 to decrease").arg(IncreaseIndentString).arg(DecreaseIndentString));
    }

    ui->SpinBoxTabSize->setToolTip("");
    if (!IncreaseTabSizeString.isEmpty() && !DecreaseTabSizeString.isEmpty()) {
        ui->SpinBoxTabSize->setToolTip(QString("%1 to increase, %2 to decrease").arg(IncreaseTabSizeString).arg(DecreaseTabSizeString));
        ui->LabelTabSize->setToolTip(QString("%1 to increase, %2 to decrease").arg(IncreaseTabSizeString).arg(DecreaseTabSizeString));
    }

    ui->SpinBoxWidth->setToolTip("");
    if (!IncreaseWidthString.isEmpty() && !DecreaseWidthString.isEmpty()) {
        ui->SpinBoxWidth->setToolTip(QString("%1 to increase, %2 to decrease").arg(IncreaseWidthString).arg(DecreaseWidthString));
        ui->LabelWidth->setToolTip(QString("%1 to increase, %2 to decrease").arg(IncreaseWidthString).arg(DecreaseWidthString));
    }
}

void MainWindow::updateOutput()
{
    // Output string. Will be echoed in the output box
    QString Output;

    // Comment lines stuff
    QString     CommentSpace;                                               // Temp string containing the spaces on each side of the comments
    QStringList CommentLines(ui->TextEditInput->toPlainText().split('\n')); // List of the lines in the input box

    // Indentation
    QString IndentStr;
    int     IndentSize = ui->SpinBoxIndent->value() * ui->SpinBoxTabSize->value(); // Number of spaces of the indentation space

    if (Settings::instance()->indentWithSpaces()) {
        IndentStr.fill(' ', IndentSize);
    }
    else {
        QFont        Font(ui->TextEditInput->font());
        QFontMetrics Metrics(Font);
        qreal        TabStopDistance = ui->SpinBoxTabSize->value() * Metrics.maxWidth();
        ui->TextEditInput->setTabStopDistance(TabStopDistance);
        ui->TextEditOutput->setTabStopDistance(TabStopDistance);
        IndentStr.fill('\t', ui->SpinBoxIndent->value());
    }

    // Intendation string, full of spaces

    // Compute real width, adapted to the longest comment line
    int RealWidth = ui->SpinBoxWidth->value();
    for (int i = 0; i < CommentLines.size(); i++) {
        int LineWidth = IndentSize + MiddleLeft.size() + CommentLines.at(i).size() + MiddleRight.size();
        RealWidth     = LineWidth > RealWidth ? LineWidth : RealWidth;
    }

    // Compute intermediate lines (between the top line and the comment, then between the comment and the bottom line)
    QString IntermediateLine; // A line between the top one and the comment section
    QString Center;           // Tmp string to quickly generate the list of spaces in the center
    int     TmpWidth;         // Used to build the lines

    if (ui->SpinBoxEmptyLines->value() != 0) {
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
    for (int i = 0; i < ui->SpinBoxEmptyLines->value(); i++) {
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
    for (int i = 0; i < ui->SpinBoxEmptyLines->value(); i++) {
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
    if (Settings::instance()->autoCopyToClipboard()) {
        QGuiApplication::clipboard()->setText(Output);
    }
}

bool MainWindow::event(QEvent* event)
{
    /***************************************************************************
     *         On window activation, select the text in the input box          *
     *                          and give it the focus                          *
     **************************************************************************/
    if (event->type() == QEvent::WindowActivate) {
        ui->TextEditInput->setFocus();
        ui->TextEditInput->selectAll();
    }

    /***************************************************************************
     *             On window deactivation, force output generation             *
     **************************************************************************/
    if (event->type() == QEvent::WindowDeactivate) {
        updateOutput();
    }

    /***************************************************************************
     *                           Handle other events                           *
     **************************************************************************/
    return QMainWindow::event(event);
}
