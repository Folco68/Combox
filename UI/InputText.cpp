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

#include "InputText.hpp"
#include <QMimeData>

InputText::InputText(QWidget* parent)
    : QPlainTextEdit(parent)
{
    setAcceptDrops(true);
}

// Support only text for paste function
bool InputText::canInsertFromMimeData(const QMimeData* source) const
{
    return source->hasText();
}

// Remove the decoration of pasted text
void InputText::insertFromMimeData(const QMimeData* source)
{
    QString Text = source->text();
    while (!Text.isEmpty() && !Text.front().isLetterOrNumber()) {
        Text.removeFirst();
    }
    while (!Text.isEmpty() && !Text.back().isLetterOrNumber()) {
        Text.removeLast();
    }
    clear();
    setPlainText(Text);
}

void InputText::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    }
}

void InputText::dropEvent(QDropEvent* event)
{
    insertFromMimeData(event->mimeData());
}
