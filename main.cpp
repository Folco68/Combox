#include "MainWindow.hpp"
#include <QApplication>
#include <QIcon>

int main(int argc, char* argv[])
{
    QApplication Application(argc, argv);
    Application.setWindowIcon(QIcon(":/Main/IconBase.png"));
    MainWindow Window;
    Window.show();
    return Application.exec();
}
