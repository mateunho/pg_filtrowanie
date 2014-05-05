#include "MainWindow.hpp"
#include <QApplication>


#include "ProcessingEngine.hpp"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    ProcessingEngine e;
    w.setWindowState(Qt::WindowActive | Qt::WindowMaximized);
    w.setWindowTitle("Filtrowanie liniowe obrazów - Projekt grupowy: M.Kacprzak, P.Dymecki");
    w.SetEngine(&e);
    w.show();

    return a.exec();
}

