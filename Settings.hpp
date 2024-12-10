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

//  Settings
//
// This class stores the users settings in the Windows registry.
// Every key has a getter and a setter.
// The getters provide a default value if nothing was defined yet.
//
class Settings: public QSettings
{
  public:
    // Singleton stuff

    static Settings* instance();
    static void      release();

    // Decoration
    QString topLeft() const;
    void    setTopLeft(QString pattern);

    QString topCenter() const;
    void    setTopCenter(QString pattern);

    QString topRight() const;
    void    setTopRight(QString pattern);

    QString middleLeft() const;
    void    setMiddleLeft(QString pattern);

    QString middleRight() const;
    void    setMiddleRight(QString pattern);

    QString bottomLeft() const;
    void    setBottomLeft(QString pattern);

    QString bottomCenter() const;
    void    setBottomCenter(QString pattern);

    QString bottomRight() const;
    void    setBottomRight(QString pattern);

    // Other output settings
    bool autoCopyToClipboard() const;
    void setautoCopyToClipboard(bool enabled);

    QString copyShortcut() const;
    void    setCopyShortcut(QString sequence);

    bool indentWithSpaces() const;
    void setIndentWithSpaces(bool indent);

    // Settings accessible in MainWindow
    int  emptyLines() const;
    void setEmptyLines(int lines);

    int  width() const;
    void setWidth(int width);

    int  indentCount() const;
    void setIndentCount(int count);

    int  tabSize() const;
    void setTabSize(int size);

    // Shortcuts
    QString increaseWidthShortcut() const;
    void    setIncreaseWidthShortcut(QString shortcut);

    QString increaseEmptyLinesShortcut() const;
    void    setIncreaseEmptyLinesShortcut(QString shortcut);

    QString increaseIndentShortcut() const;
    void    setIncreaseIndentShortcut(QString shortcut);

    QString increaseTabSizeShortcut() const;
    void    setIncreaseTabSizeShortcut(QString shortcut);

    QString decreaseWidthShortcut() const;
    void    setDecreaseWidthShortcut(QString shortcut);

    QString decreaseEmptyLinesShortcut() const;
    void    setDecreaseEmptyLinesShortcut(QString shortcut);

    QString decreaseIndentShortcut() const;
    void    setDecreaseIndentShortcut(QString shortcut);

    QString decreaseTabSizeShortcut() const;
    void    setDecreaseTabSizeShortcut(QString shortcut);

  private:
    // Singleton stuff
    static Settings* settings;
    Settings();
    ~Settings();
};

#define KEY_TOP_LEFT     "TopLeft"
#define DEFAULT_TOP_LEFT "/*"

#define KEY_TOP_CENTER     "TopCenter"
#define DEFAULT_TOP_CENTER "*"

#define KEY_TOP_RIGHT     "TopRight"
#define DEFAULT_TOP_RIGHT "*"

#define KEY_MIDDLE_LEFT     "MiddleLeft"
#define DEFAULT_MIDDLE_LEFT " *"

#define KEY_MIDDLE_RIGHT     "MiddleRight"
#define DEFAULT_MIDDLE_RIGHT "*"

#define KEY_BOTTOM_LEFT     "BottomLeft"
#define DEFAULT_BOTTOM_LEFT " *"

#define KEY_BOTTOM_CENTER     "BottomCenter"
#define DEFAULT_BOTTOM_CENTER "*"

#define KEY_BOTTOM_RIGHT     "BottomRight"
#define DEFAULT_BOTTOM_RIGHT "/"

#define KEY_AUTO_COPY_TO_CLIPBOARD     "AutoCopyToClipboard"
#define DEFAULT_AUTO_COPY_TO_CLIPBOARD false

#define KEY_COPY_SHORTCUT     "CopyShortcut"
#define DEFAULT_COPY_SHORTCUT "F5"

#define KEY_INDENT_WITH_SPACES     "IndentWithSpaces"
#define DEFAULT_INDENT_WITH_SPACES true

#define KEY_EMTPY_LINES     "EmptyLines"
#define DEFAULT_EMPTY_LINES 1

#define KEY_WIDTH     "Width"
#define DEFAULT_WIDTH 120

#define KEY_INDENT_COUNT     "IndentCount"
#define DEFAULT_INDENT_COUNT 1

#define KEY_TAB_SIZE     "TabSize"
#define DEFAULT_TAB_SIZE 4

#define KEY_INCREASE_WIDTH_SHORTCUT     "IncreaseWidthShortcut"
#define DEFAULT_INCREASE_WIDTH_SHORTCUT "Ctrl+W"

#define KEY_INCREASE_EMPTY_LINES_SHORTCUT     "IncreaseEmptyLines"
#define DEFAULT_INCREASE_EMPTY_LINES_SHORTCUT "Ctrl+E"

#define KEY_INCREASE_INDENT_SHORTCUT     "IncreaseIndentShortcut"
#define DEFAULT_INCREASE_INDENT_SHORTCUT "Ctrl+I"

#define KEY_INCREASE_TAB_SIZE_SHORTCUT     "IncreaseTabSizeShortcut"
#define DEFAULT_INCREASE_TAB_SIZE_SHORTCUT "Ctrl+T"

#define KEY_DECREASE_WIDTH_SHORTCUT     "DecreaseWidthShortcut"
#define DEFAULT_DECREASE_WIDTH_SHORTCUT "Shift+Ctrl+W"

#define KEY_DECREASE_EMPTY_LINES_SHORTCUT     "DecreaseEmptyLines"
#define DEFAULT_DECREASE_EMPTY_LINES_SHORTCUT "Shift+Ctrl+E"

#define KEY_DECREASE_INDENT_SHORTCUT     "DecreaseIndentShortcut"
#define DEFAULT_DECREASE_INDENT_SHORTCUT "Shift+Ctrl+I"

#define KEY_DECREASE_TAB_SIZE_SHORTCUT     "DecreaseTabSizeShortcut"
#define DEFAULT_DECREASE_TAB_SIZE_SHORTCUT "Shift+Ctrl+T"

#endif // SETTINGS_HPP
