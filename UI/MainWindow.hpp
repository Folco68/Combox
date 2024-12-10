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

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QEvent>
#include <QMainWindow>
#include <QShortcut>
#include <QString>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow: public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

  private:
    Ui::MainWindow* ui;

    // Output timer
    QTimer GenerationTimer;

    // Settings. Locally stored for performance and display conveniency
    QString   TopLeft;
    QString   TopCenter;
    QString   TopRight;
    QString   MiddleLeft;
    QString   MiddleRight;
    QString   BottomLeft;
    QString   BottomCenter;
    QString   BottomRight;
    bool      AutoCopy;
    QShortcut CopyShortcut;
    QShortcut IncreaseEmptyLinesShortcut;
    QShortcut DecreaseEmptyLinesShortcut;
    QShortcut IncreaseTabSizeShortcut;
    QShortcut DecreaseTabSizeShortcut;
    QShortcut IncreaseIndentShortcut;
    QShortcut DecreaseIndentShortcut;
    QShortcut IncreaseWidthShortcut;
    QShortcut DecreaseWidthShortcut;

    void execDlgSettings();
    void updateConfiguration();
    void updateOutput();
    bool event(QEvent* event) override;
};

#endif // MAINWINDOW_HPP
