#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

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
};

#endif // MAINWINDOW_HPP
