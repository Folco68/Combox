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

#ifndef DLGSETTINGS_HPP
#define DLGSETTINGS_HPP

#include <QDialog>

namespace Ui {
    class DlgSettings;
}

class DlgSettings: public QDialog
{
    Q_OBJECT

  public:
    static bool execDlgSettings(QWidget* parent);

  private:
    explicit DlgSettings(QWidget* parent);
    ~DlgSettings();
    Ui::DlgSettings* ui;
};

#endif // DLGSETTINGS_HPP
