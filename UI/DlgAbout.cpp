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

#include "DlgAbout.hpp"
#include "../BeforeRelease.hpp"
#include "ui_DlgAbout.h"
#include <QFile>
#include <QPushButton>
#include <QString>
#include <QTextStream>

DlgAbout::DlgAbout(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::DlgAbout)
{
    ui->setupUi(this);
    ui->Tabs->setCurrentIndex(0);
    connect(ui->ButtonClose, &QPushButton::clicked, this, [this]() { close(); });

    // About
    QFile FileAbout(":/Main/ABOUT");
    if (FileAbout.open(QIODeviceBase::ReadOnly)) {
        QTextStream StreamReadme(&FileAbout);
        QString     About = StreamReadme.readAll();

        About.replace("PLACEHOLDER_POSITION_STR", POSITION_STR);
        About.replace("PLACEHOLDER_COPYRIGHT_STR", COPYRIGHT_STR);
        About.replace("PLACEHOLDER_APPLICATION_VERSION_STR", APPLICATION_VERSION_STR);
        About.replace("PLACEHOLDER_QT_VERSION_STR", QT_VERSION_STR);
        About.replace("PLACEHOLDER_EMAIL_PERSONAL", EMAIL_PERSONAL);
        About.replace("PLACEHOLDER_EMAIL_PROFESSIONAL", EMAIL_PROFESSIONAL);

        ui->TextEditAbout->setPlainText(About);
    }

    // HowTo
    QFile FileHowTo(":/Main/HOWTO");
    if (FileHowTo.open(QIODeviceBase::ReadOnly)) {
        QTextStream StreamReadme(&FileHowTo);
        QString     HowTo = StreamReadme.readAll();
        ui->TextEditHowTo->setPlainText(HowTo);
    }

    // License
    QFile FileLicense(":/Main/LICENSE");
    if (FileLicense.open(QIODeviceBase::ReadOnly)) {
        QTextStream StreamReadme(&FileLicense);
        QString     License = StreamReadme.readAll();
        ui->TextEditLicense->setPlainText(License);
    }
}

DlgAbout::~DlgAbout()
{
    delete ui;
}

void DlgAbout::execDlgAbout(QWidget* parent)
{
    DlgAbout* Dlg = new DlgAbout(parent);
    Dlg->exec();
    delete Dlg;
}
