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

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

// QCoreApplication settings (for QSettings) + app name
#define ORGANIZATION_NAME "FolcoSoft"
#define APPLICATION_NAME  "Combox"

// Generation timer delay (ms)
// After a keystroke in the input box, wait the exhaust of this timer to update the output
#define GENERATION_DELAY 200

// Step of increment/decrement of the total width
#define STEP_WIDTH 10

#endif // GLOBAL_HPP
