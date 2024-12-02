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

    //
    QTimer*    GenerationTimer;
    QShortcut* CopyShortcut;

    // Settings. Locally stored for performance
    QString TopLeft;
    QString TopCenter;
    QString TopRight;
    QString MiddleLeft;
    QString MiddleRight;
    QString BottomLeft;
    QString BottomCenter;
    QString BottomRight;
    int     EmptyLines;
    int     Width;
    bool    AutoCopy;

    void execDlgSettings();
    void updateSettings();
    void updateOutput();
    bool event(QEvent* event) override;
};

#endif // MAINWINDOW_HPP
