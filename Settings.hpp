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

class Settings: public QSettings
{
  public:
    // Singleton stuff
    static Settings* instance();
    static void      release();

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

    int  emptyLines() const;
    void setEmptyLines(int lines);

    int  width() const;
    void setWidth(int width);

    bool autoCopyToClipboard() const;
    void setautoCopyToClipboard(bool enabled);

    QString copyShortcut() const;
    void    setCopyShortcut(QString sequence);

    int  indentCount() const;
    void setIndentCount(int count);

    int  tabSize() const;
    void setTabSize(int size);

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

#define KEY_EMTPY_LINES     "EmptyLines"
#define DEFAULT_EMPTY_LINES 1

#define KEY_WIDTH     "Width"
#define DEFAULT_WIDTH 120

#define KEY_AUTO_COPY_TO_CLIPBOARD     "AutoCopyToClipboard"
#define DEFAULT_AUTO_COPY_TO_CLIPBOARD false

#define KEY_COPY_SHORTCUT     "CopyShortcut"
#define DEFAULT_COPY_SHORTCUT "F5"

#define KEY_INDENT_COUNT     "IndentCount"
#define DEFAULT_INDENT_COUNT 1

#define KEY_TAB_SIZE     "TabSize"
#define DEFAULT_TAB_SIZE 4

#endif // SETTINGS_HPP
