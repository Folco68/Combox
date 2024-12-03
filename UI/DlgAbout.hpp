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

#ifndef DLGABOUT_HPP
#define DLGABOUT_HPP

#include <QDialog>

namespace Ui {
    class DlgAbout;
}

//  DlgAbout
//
// Simple dialog showing About, HowTo and License texts
//
class DlgAbout: public QDialog
{
    Q_OBJECT

  public:
    static void execDlgAbout(QWidget* parent);

  private:
    Ui::DlgAbout* ui;
    DlgAbout(QWidget* parent = nullptr);
    ~DlgAbout();
};

#endif // DLGABOUT_HPP
