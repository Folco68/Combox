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
#include <QChar>
#include <QList>
#include <QMimeData>
#include <QString>

InputText::InputText(QWidget* parent)
    : QPlainTextEdit(parent)
{
    setAcceptDrops(true);
}

//  canInsertFromMimeData
//
// Paste supports only text
//
bool InputText::canInsertFromMimeData(const QMimeData* source) const
{
    return source->hasText();
}

//  insertFromMimeData
//
// Paste text and attempt to clean it.
//
// The underlying idea behind the cleaning is that the user probably wants to edit an existing comment block.
// So the function tries to remove extra lines and decorattions from the previous block.
// This function is heuristic and can't be perfect. It can be fooled in many ways,
// but it tries to be effective in the most common cases.
//
// Several rules have been tested:
//
// - Remove characters until an alphanumerical number is found (314f444cbdf2922a00c5ee8e70571f3c1e5ed253)
//   Quite good, but it was removing the parenthesis of the GPL notice
//
// - Remove all non-alphanumeric chars if they are not close to an alphanumeric char (eb776bda5a14a267329de895d429905c82e99fc9)
//   A bit better becauses it saves parenthesis and punctuation, but still fails hardly with code snippets
//
// - Remove white spaces at both sides (to discard indentation), then read the first "block" at each side:
//  - keep this block if there is at least one alphanumeric char inside
//  - discard the block if there are no alphanumeric char inside
//
void InputText::insertFromMimeData(const QMimeData* source)
{
    /************************************************************************** 
     *                                                                        * 
     *           Paste the original block to save it in the history           * 
     *                 then replace it with the clean version                 * 
     *           It allows to recover the original text with Ctrl-Z           * 
     *               if the cleaning function is too agressive                * 
     *                                                                        * 
     *         After the text has been pasted once, don't use anymore         * 
     *   setPlainText() or clear() methods because they discard the history   * 
     *                                                                        * 
     **************************************************************************/

    QString Text = source->text(); // Must read text() only once, I don't know why, else it crashes
    setPlainText(Text);            // Paste. Can't use paste(), because we are redefining it
    selectAll();                   // Prepare for cutting
    cut();                         // And cut, while it is already in the clipboard
                                   // By this time, cutting is the only way to delete the text area without clearing the history

    /***************************************************************************
     *                                                                         *
     *                        Split the input in lines                         *
     *                                                                         *
     **************************************************************************/

    QList<QString> Lines(Text.split('\n'));

    /***************************************************************************
     *                                                                         *
     *                            Clean every line                             *
     *                                                                         *
     **************************************************************************/

    for (int i = 0; i < Lines.size(); i++) {
        QString   Line           = Lines.at(i).trimmed(); // Remove leading and trailing spaces
        qsizetype Offset         = 0;
        bool      LetterOrNumber = false;

        // Clean left part
        // Find the first space in the string
        while (Offset < Line.size()) {
            if (Line.at(Offset).isSpace()) {
                break;
            }
            Offset++;
        }

        // No space in the string, keep it if there is at least one alphanumeric char
        if (Offset == Line.size()) {
            for (int i = 0; !LetterOrNumber && i < Line.size(); i++) {
                LetterOrNumber |= Line.at(i).isLetterOrNumber();
            }
            // No alphanumeric char found, clear the line
            if (!LetterOrNumber) {
                Line.clear();
            }
        }

        // There is at least one space in the string
        else {
            // Keep the first block only if it contains at least one alphanumeric char
            QString Block(Line.left(Offset));
            LetterOrNumber = false;
            for (int i = 0; !LetterOrNumber && i < Block.size(); i++) {
                LetterOrNumber |= Block.at(i).isLetterOrNumber();
            }
            // No alphanumeric char found, discard the block
            if (!LetterOrNumber) {
                Line.remove(Block);
            }

            // Clean right part
            // Find the last space in the string
            Offset = Line.size();
            while (--Offset >= 0) {
                if (Line.at(Offset).isSpace()) {
                    break;
                }
            }

            // No space in the string, keep it only if there is at least one alphanumeric char
            if (Offset < 0) {
                LetterOrNumber = false;
                for (int i = 0; !LetterOrNumber && i < Line.size(); i++) {
                    LetterOrNumber |= Line.at(i).isLetterOrNumber();
                }
                // No alphanumeric char found, clear the line
                if (!LetterOrNumber) {
                    Line.clear();
                }
            }

            // There is at least one space in the string
            else {
                Block = Line.mid(Offset);
                // Keep the last block only if it contains at least one alphanumeric char
                LetterOrNumber = false;
                for (int i = 0; !LetterOrNumber && i < Block.size(); i++) {
                    LetterOrNumber |= Block.at(i).isLetterOrNumber();
                }
                // No alphanumeric char found, discard the block
                if (!LetterOrNumber) {
                    Line.truncate(Offset);
                }
            }
        }

        // Remove spaces if a block was discarded
        Lines[i] = Line.trimmed();
    }

    /************************************************************************** 
     *                                                                        * 
     *          Trim the text for leading and trailing empty lines            * 
     *                                                                        * 
     **************************************************************************/

    // Leading lines
    while (!Lines.isEmpty() && Lines.first().isEmpty()) {
        Lines.removeFirst();
    }

    // Trailing lines
    while (!Lines.isEmpty() && Lines.last().isEmpty()) {
        Lines.removeLast();
    }

    /***************************************************************************
     *                                                                         *
     *                   Paste the cleaned lines in the ouput                  *
     *                                                                         *
     **************************************************************************/

    for (int i = 0; i < Lines.size(); i++) {
        appendPlainText(Lines.at(i)); // Empty lines do not change the input
    }
}

//  dragEnterEvent
//
// Allow potential drop only if the content is a text
//
void InputText::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    }
}

//  dropEvent
//
// On a drop, apply the procedure of pasting
//
void InputText::dropEvent(QDropEvent* event)
{
    insertFromMimeData(event->mimeData());
}
