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

/***********************************************************************************************************************
 *                                                                                                                     *
 *                                                   Singleton stuff                                                   *
 *                                                                                                                     *
 **********************************************************************************************************************/

Settings* Settings::settings = nullptr;

Settings* Settings::instance()
{
    if (settings == nullptr) {
        settings = new Settings;
    }
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
