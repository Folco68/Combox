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
    ui->SpinBoxEmptyLines->setValue(Settings::instance()->emptyLines());
    ui->SpinBoxWidth->setValue(Settings::instance()->width());
    ui->CheckAutoCopy->setChecked(Settings::instance()->autoCopyToClipboard());
    ui->KeySequenceCopy->setKeySequence(Settings::instance()->copyShortcut());

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
        Settings::instance()->setEmptyLines(Dlg->ui->SpinBoxEmptyLines->value());
        Settings::instance()->setWidth(Dlg->ui->SpinBoxWidth->value());
        Settings::instance()->setautoCopyToClipboard(Dlg->ui->CheckAutoCopy->isChecked());
        Settings::instance()->setCopyShortcut(Dlg->ui->KeySequenceCopy->keySequence().toString());
    }

    /***************************************************************************
     *                                                                         *
     *                     Clean and return dialog result                      *
     *                                                                         *
     **************************************************************************/

    delete Dlg;
    return RetVal == QDialog::Accepted;
}
