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

#ifndef INPUTTEXT_HPP
#define INPUTTEXT_HPP

#include <QPlainTextEdit>
#include <QWidget>

class InputText: public QPlainTextEdit
{
    Q_OBJECT

  public:
    InputText(QWidget* parent);
    bool canInsertFromMimeData(const QMimeData* source) const override;
    void insertFromMimeData(const QMimeData* source) override;
};

#endif // INPUTTEXT_HPP
