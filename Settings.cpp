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

#include "Settings.hpp"
#include "Global.hpp"

/*******************************************************************************************************************
     *                                                                                                                 *
     *                                                 Singleton stuff                                                 *
     *                                                                                                                 *
     ******************************************************************************************************************/

Settings* Settings::settings = nullptr;

Settings* Settings::instance()
{
    if (settings == nullptr) {
        settings = new Settings;
    }
    /*******************************************************************************************************************
     *                                                                                                                 *
     *                                                 Singleton stuff                                                 *
     *                                                                                                                 *
     ******************************************************************************************************************/
    return settings;
}

void Settings::release()
{
    if (settings != nullptr) {
        delete settings;
        settings = nullptr;
    }
}

Settings::Settings()
    : QSettings(ORGANIZATION_NAME, APPLICATION_NAME)
{
}

Settings::~Settings()
{
    sync();
}

/*******************************************************************************************************************
     *                                                                                                                 *
     *                                                    Settings                                                     *
     *                                                                                                                 *
     ******************************************************************************************************************/

QString Settings::topLeft() const
{
    return value(KEY_TOP_LEFT, DEFAULT_TOP_LEFT).toString();
}

void Settings::setTopLeft(QString pattern)
{
    setValue(KEY_TOP_LEFT, pattern);
}

QString Settings::topCenter() const
{
    return value(KEY_TOP_CENTER, DEFAULT_TOP_CENTER).toString();
}

void Settings::setTopCenter(QString pattern)
{
    setValue(KEY_TOP_CENTER, pattern);
}

QString Settings::topRight() const
{
    return value(KEY_TOP_RIGHT, DEFAULT_TOP_RIGHT).toString();
}

void Settings::setTopRight(QString pattern)
{
    setValue(KEY_TOP_RIGHT, pattern);
}

QString Settings::middleLeft() const
{
    return value(KEY_MIDDLE_LEFT, DEFAULT_MIDDLE_LEFT).toString();
}

void Settings::setMiddleLeft(QString pattern)
{
    setValue(KEY_MIDDLE_LEFT, pattern);
}

QString Settings::middleRight() const
{
    return value(KEY_MIDDLE_RIGHT, DEFAULT_MIDDLE_RIGHT).toString();
}

void Settings::setMiddleRight(QString pattern)
{
    setValue(KEY_MIDDLE_RIGHT, pattern);
}

QString Settings::bottomLeft() const
{
    return value(KEY_BOTTOM_LEFT, DEFAULT_BOTTOM_LEFT).toString();
}

void Settings::setBottomLeft(QString pattern)
{
    setValue(KEY_BOTTOM_LEFT, pattern);
}

QString Settings::bottomCenter() const
{
    return value(KEY_BOTTOM_CENTER, DEFAULT_BOTTOM_CENTER).toString();
}

void Settings::setBottomCenter(QString pattern)
{
    setValue(KEY_BOTTOM_CENTER, pattern);
}

QString Settings::bottomRight() const
{
    return value(KEY_BOTTOM_RIGHT, DEFAULT_BOTTOM_RIGHT).toString();
}

void Settings::setBottomRight(QString pattern)
{
    setValue(KEY_BOTTOM_RIGHT, pattern);
}

int Settings::emptyLines() const
{
    return value(KEY_EMTPY_LINES, DEFAULT_EMPTY_LINES).toInt();
}

void Settings::setEmptyLines(int lines)
{
    setValue(KEY_EMTPY_LINES, lines);
}

int Settings::width() const
{
    return value(KEY_WIDTH, DEFAULT_WIDTH).toInt();
}

void Settings::setWidth(int width)
{
    setValue(KEY_WIDTH, width);
}

bool Settings::autoCopyToClipboard() const
{
    return value(KEY_AUTO_COPY_TO_CLIPBOARD, DEFAULT_AUTO_COPY_TO_CLIPBOARD).toBool();
}

void Settings::setautoCopyToClipboard(bool enabled)
{
    setValue(KEY_AUTO_COPY_TO_CLIPBOARD, enabled);
}

QString Settings::copyShortcut() const
{
    return value(KEY_COPY_SHORTCUT, DEFAULT_COPY_SHORTCUT).toString();
}

void Settings::setCopyShortcut(QString sequence)
{
    setValue(KEY_COPY_SHORTCUT, sequence);
}

int Settings::indentCount() const
{
    return value(KEY_INDENT_COUNT, DEFAULT_INDENT_COUNT).toInt();
}

void Settings::setIndentCount(int count)
{
    setValue(KEY_INDENT_COUNT, count);
}

int Settings::tabSize() const
{
    return value(KEY_TAB_SIZE, DEFAULT_TAB_SIZE).toInt();
}

void Settings::setTabSize(int size)
{
    setValue(KEY_TAB_SIZE, size);
}
