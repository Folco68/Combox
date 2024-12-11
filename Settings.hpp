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

#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <QKeySequence>
#include <QSettings>
#include <QString>

// Implementation of a getter and a setter for a setting
#define IMPLEMENT(TYPE, CONVERSION, GETTER, SETTER, KEY, DEFAULT_KEY) \
    TYPE GETTER() const                                               \
    {                                                                 \
        return value(KEY, DEFAULT_KEY).CONVERSION();                  \
    }                                                                 \
    void SETTER(TYPE value)                                           \
    {                                                                 \
        setValue(KEY, value);                                         \
    }


//  Settings
//
// This class stores the users settings in the Windows registry.
// Every key has a getter and a setter.
// The getters provide a default value if nothing was defined yet.
//

class Settings: public QSettings
{
  public:
    /***************************************************************************
     *                                                                         *
     *                             Singleton stuff                             *
     *                                                                         *
     **************************************************************************/

    static Settings* instance();
    static void      release();


    /***************************************************************************
     *                                                                         *
     *                             Box decoration                              *
     *                                                                         *
     **************************************************************************/

#define KEY_TOP_LEFT     "TopLeft"
#define DEFAULT_TOP_LEFT "/*"
    IMPLEMENT(QString, toString, topLeft, setTopLeft, KEY_TOP_LEFT, DEFAULT_TOP_LEFT)

#define KEY_TOP_CENTER     "TopCenter"
#define DEFAULT_TOP_CENTER "*"
    IMPLEMENT(QString, toString, topCenter, setTopCenter, KEY_TOP_CENTER, DEFAULT_TOP_CENTER)

#define KEY_TOP_RIGHT     "TopRight"
#define DEFAULT_TOP_RIGHT "*"
    IMPLEMENT(QString, toString, topRight, setTopRight, KEY_TOP_RIGHT, DEFAULT_TOP_RIGHT)

#define KEY_MIDDLE_LEFT     "MiddleLeft"
#define DEFAULT_MIDDLE_LEFT " *"
    IMPLEMENT(QString, toString, middleLeft, setMiddleLeft, KEY_MIDDLE_LEFT, DEFAULT_MIDDLE_LEFT)

#define KEY_MIDDLE_RIGHT     "MiddleRight"
#define DEFAULT_MIDDLE_RIGHT "*"
    IMPLEMENT(QString, toString, middleRight, setMiddleRight, KEY_MIDDLE_RIGHT, DEFAULT_MIDDLE_RIGHT)

#define KEY_BOTTOM_LEFT     "BottomLeft"
#define DEFAULT_BOTTOM_LEFT " *"
    IMPLEMENT(QString, toString, bottomLeft, setBottomLeft, KEY_BOTTOM_LEFT, DEFAULT_BOTTOM_LEFT)

#define KEY_BOTTOM_CENTER     "BottomCenter"
#define DEFAULT_BOTTOM_CENTER "*"
    IMPLEMENT(QString, toString, bottomCenter, setBottomCenter, KEY_BOTTOM_CENTER, DEFAULT_BOTTOM_CENTER)

#define KEY_BOTTOM_RIGHT     "BottomRight"
#define DEFAULT_BOTTOM_RIGHT "/"
    IMPLEMENT(QString, toString, bottomRight, setBottomRight, KEY_BOTTOM_RIGHT, DEFAULT_BOTTOM_RIGHT)


    /***************************************************************************
     *                                                                         *
     *                           MainWindow settings                           *
     *                                                                         *
     **************************************************************************/

#define KEY_EMPTY_LINES     "EmptyLines"
#define DEFAULT_EMPTY_LINES 1
    IMPLEMENT(int, toInt, emptyLines, setEmptyLines, KEY_EMPTY_LINES, DEFAULT_EMPTY_LINES)

#define KEY_WIDTH     "Width"
#define DEFAULT_WIDTH 120
    IMPLEMENT(int, toInt, width, setWidth, KEY_WIDTH, DEFAULT_WIDTH)

#define KEY_INDENT_COUNT     "IndentCount"
#define DEFAULT_INDENT_COUNT 1
    IMPLEMENT(int, toInt, indentCount, setIndentCount, KEY_INDENT_COUNT, DEFAULT_INDENT_COUNT)

#define KEY_TAB_SIZE     "TabSize"
#define DEFAULT_TAB_SIZE 4
    IMPLEMENT(int, toInt, tabSize, setTabSize, KEY_TAB_SIZE, DEFAULT_TAB_SIZE)


    /***************************************************************************
     *                                                                         *
     *                           Settings shortcuts                            *
     *                                                                         *
     **************************************************************************/

#define KEY_INCREASE_WIDTH_SHORTCUT     "IncreaseWidthShortcut"
#define DEFAULT_INCREASE_WIDTH_SHORTCUT "Ctrl+W"
    IMPLEMENT(QString, toString, increaseWidthShortcut, setIncreaseWidthShortcut, KEY_INCREASE_WIDTH_SHORTCUT, DEFAULT_INCREASE_WIDTH_SHORTCUT)

#define KEY_DECREASE_WIDTH_SHORTCUT     "DecreaseWidthShortcut"
#define DEFAULT_DECREASE_WIDTH_SHORTCUT "Shift+Ctrl+W"
    IMPLEMENT(QString, toString, decreaseWidthShortcut, setDecreaseWidthShortcut, KEY_DECREASE_WIDTH_SHORTCUT, DEFAULT_DECREASE_WIDTH_SHORTCUT)

#define KEY_INCREASE_EMPTY_LINES_SHORTCUT     "IncreaseEmptyLines"
#define DEFAULT_INCREASE_EMPTY_LINES_SHORTCUT "Ctrl+E"
    IMPLEMENT(QString, toString, increaseEmptyLinesShortcut, setIncreaseEmptyLinesShortcut, KEY_INCREASE_EMPTY_LINES_SHORTCUT, DEFAULT_INCREASE_EMPTY_LINES_SHORTCUT)

#define KEY_DECREASE_EMPTY_LINES_SHORTCUT     "DecreaseEmptyLines"
#define DEFAULT_DECREASE_EMPTY_LINES_SHORTCUT "Shift+Ctrl+E"
    IMPLEMENT(QString, toString, decreaseEmptyLinesShortcut, setDecreaseEmptyLinesShortcut, KEY_DECREASE_EMPTY_LINES_SHORTCUT, DEFAULT_DECREASE_EMPTY_LINES_SHORTCUT)

#define KEY_INCREASE_INDENT_SHORTCUT     "IncreaseIndentShortcut"
#define DEFAULT_INCREASE_INDENT_SHORTCUT "Ctrl+I"
    IMPLEMENT(QString, toString, increaseIndentShortcut, setIncreaseIndentShortcut, KEY_INCREASE_INDENT_SHORTCUT, DEFAULT_INCREASE_INDENT_SHORTCUT)

#define KEY_DECREASE_INDENT_SHORTCUT     "DecreaseIndentShortcut"
#define DEFAULT_DECREASE_INDENT_SHORTCUT "Shift+Ctrl+I"
    IMPLEMENT(QString, toString, decreaseIndentShortcut, setDecreaseIndentShortcut, KEY_DECREASE_INDENT_SHORTCUT, DEFAULT_DECREASE_INDENT_SHORTCUT)

#define KEY_INCREASE_TAB_SIZE_SHORTCUT     "IncreaseTabSizeShortcut"
#define DEFAULT_INCREASE_TAB_SIZE_SHORTCUT "Ctrl+T"
    IMPLEMENT(QString, toString, increaseTabSizeShortcut, setIncreaseTabSizeShortcut, KEY_INCREASE_TAB_SIZE_SHORTCUT, DEFAULT_INCREASE_TAB_SIZE_SHORTCUT)

#define KEY_DECREASE_TAB_SIZE_SHORTCUT     "DecreaseTabSizeShortcut"
#define DEFAULT_DECREASE_TAB_SIZE_SHORTCUT "Shift+Ctrl+T"
    IMPLEMENT(QString, toString, decreaseTabSizeShortcut, setDecreaseTabSizeShortcut, KEY_DECREASE_TAB_SIZE_SHORTCUT, DEFAULT_DECREASE_TAB_SIZE_SHORTCUT)


    /***************************************************************************
     *                                                                         *
     *                             Misc. settings                              *
     *                                                                         *
     **************************************************************************/

#define KEY_INDENT_WITH_SPACES     "IndentWithSpaces"
#define DEFAULT_INDENT_WITH_SPACES true
    IMPLEMENT(bool, toBool, indentWithSpaces, setIndentWithSpaces, KEY_INDENT_WITH_SPACES, DEFAULT_INDENT_WITH_SPACES)

#define KEY_AUTO_COPY_TO_CLIPBOARD     "AutoCopyToClipboard"
#define DEFAULT_AUTO_COPY_TO_CLIPBOARD false
    IMPLEMENT(bool, toBool, autoCopyToClipboard, setAutoCopyToClipboard, KEY_AUTO_COPY_TO_CLIPBOARD, DEFAULT_AUTO_COPY_TO_CLIPBOARD)

#define KEY_COPY_SHORTCUT     "CopyShortcut"
#define DEFAULT_COPY_SHORTCUT "F5"
    IMPLEMENT(QString, toString, copyShortcut, setCopyShortcut, KEY_COPY_SHORTCUT, DEFAULT_COPY_SHORTCUT)


    /***************************************************************************
     *                                                                         *
     *                                 Private                                 *
     *                                                                         *
     **************************************************************************/

  private:
    static Settings* settings; // For the singleton
    Settings();
    ~Settings();
};

#endif // SETTINGS_HPP
