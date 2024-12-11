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

#include "DlgSettings.hpp"
#include "../Settings.hpp"
#include "ui_DlgSettings.h"

//  DlgSettings
//
// Constructor
//
DlgSettings::DlgSettings(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::DlgSettings)
{
    ui->setupUi(this);

    /***************************************************************************
     *                                                                         *
     *                  Prepare the UI with current settings                   *
     *                                                                         *
     **************************************************************************/

    ui->EditTopLeft->setText(Settings::instance()->topLeft());
    ui->EditTopCenter->setText(Settings::instance()->topCenter());
    ui->EditTopRight->setText(Settings::instance()->topRight());
    ui->EditMiddleLeft->setText(Settings::instance()->middleLeft());
    ui->EditMiddleRight->setText(Settings::instance()->middleRight());
    ui->EditBottomLeft->setText(Settings::instance()->bottomLeft());
    ui->EditBottomCenter->setText(Settings::instance()->bottomCenter());
    ui->EditBottomRight->setText(Settings::instance()->bottomRight());
    ui->CheckIndentWithSpaces->setChecked(Settings::instance()->indentWithSpaces());
    ui->CheckAutoCopy->setChecked(Settings::instance()->autoCopyToClipboard());
    ui->KeySequenceCopy->setKeySequence(Settings::instance()->copyShortcut());
    ui->KeySequenceIncreaseEmptyLines->setKeySequence(Settings::instance()->increaseEmptyLinesShortcut());
    ui->KeySequenceDecreaseEmptyLines->setKeySequence(Settings::instance()->decreaseEmptyLinesShortcut());
    ui->KeySequenceIncreaseIndent->setKeySequence(Settings::instance()->increaseIndentShortcut());
    ui->KeySequenceDecreaseIndent->setKeySequence(Settings::instance()->decreaseIndentShortcut());
    ui->KeySequenceIncreaseTabSize->setKeySequence(Settings::instance()->increaseTabSizeShortcut());
    ui->KeySequenceDecreaseTabSize->setKeySequence(Settings::instance()->decreaseTabSizeShortcut());
    ui->KeySequenceIncreaseWidth->setKeySequence(Settings::instance()->increaseWidthShortcut());
    ui->KeySequenceDecreaseWidth->setKeySequence(Settings::instance()->decreaseWidthShortcut());


    /***************************************************************************
     *                                                                         *
     *                           Buttons connections                           *
     *                                                                         *
     **************************************************************************/

    connect(ui->ButtonOK, &QPushButton::clicked, this, [this]() { accept(); });
    connect(ui->ButtonCancel, &QPushButton::clicked, this, [this]() { reject(); });
}

DlgSettings::~DlgSettings()
{
    delete ui;
}

//  execDlgSettings
//
// Static method displaying the dialog and updating the config in the registry in case of validation
//
bool DlgSettings::execDlgSettings(QWidget* parent)
{
    /***************************************************************************
     *                                                                         *
     *                             Show the dialog                             *
     *                                                                         *
     **************************************************************************/

    DlgSettings* Dlg    = new DlgSettings(parent);
    int          RetVal = Dlg->exec();

    /***************************************************************************
     *                                                                         *
     *              Save the settings if the dialog was validated              *
     *                                                                         *
     **************************************************************************/

    if (RetVal == QDialog::Accepted) {
        Settings::instance()->setTopLeft(Dlg->ui->EditTopLeft->text());
        Settings::instance()->setTopCenter(Dlg->ui->EditTopCenter->text());
        Settings::instance()->setTopRight(Dlg->ui->EditTopRight->text());
        Settings::instance()->setMiddleLeft(Dlg->ui->EditMiddleLeft->text());
        Settings::instance()->setMiddleRight(Dlg->ui->EditMiddleRight->text());
        Settings::instance()->setBottomLeft(Dlg->ui->EditBottomLeft->text());
        Settings::instance()->setBottomCenter(Dlg->ui->EditBottomCenter->text());
        Settings::instance()->setBottomRight(Dlg->ui->EditBottomRight->text());
        Settings::instance()->setIndentWithSpaces(Dlg->ui->CheckIndentWithSpaces->isChecked());
        Settings::instance()->setAutoCopyToClipboard(Dlg->ui->CheckAutoCopy->isChecked());
        Settings::instance()->setCopyShortcut(Dlg->ui->KeySequenceCopy->keySequence().toString());
        Settings::instance()->setIncreaseEmptyLinesShortcut(Dlg->ui->KeySequenceIncreaseEmptyLines->keySequence().toString());
        Settings::instance()->setDecreaseEmptyLinesShortcut(Dlg->ui->KeySequenceDecreaseEmptyLines->keySequence().toString());
        Settings::instance()->setIncreaseIndentShortcut(Dlg->ui->KeySequenceIncreaseIndent->keySequence().toString());
        Settings::instance()->setDecreaseIndentShortcut(Dlg->ui->KeySequenceDecreaseIndent->keySequence().toString());
        Settings::instance()->setIncreaseTabSizeShortcut(Dlg->ui->KeySequenceIncreaseTabSize->keySequence().toString());
        Settings::instance()->setDecreaseTabSizeShortcut(Dlg->ui->KeySequenceDecreaseTabSize->keySequence().toString());
        Settings::instance()->setIncreaseWidthShortcut(Dlg->ui->KeySequenceIncreaseWidth->keySequence().toString());
        Settings::instance()->setDecreaseWidthShortcut(Dlg->ui->KeySequenceDecreaseWidth->keySequence().toString());
    }

    /***************************************************************************
     *                                                                         *
     *                     Clean and return dialog result                      *
     *                                                                         *
     **************************************************************************/

    delete Dlg;
    return RetVal == QDialog::Accepted;
}
