#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP


#include <QMainWindow>


class ImagesDialog;
class QCloseEvent;
class ProcessingEngine;


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // ustawia wskaznik na obiekt filtrujacy
    void SetEngine(const ProcessingEngine *_engine);

private slots:
    // obsluga otwarcia obrazu w oknie z obrazkami
    void on_actionOpen_triggered();

    // obsluga zamkniecia okna
    void closeEvent(QCloseEvent *_event);

    // obsluga zamkniecia programu
    void on_actionExit_triggered();

    // obsluga wyswietlenia okna z pomoca
    void on_actionUser_manual_triggered();

    // obsluga wyswietlenia okna z informacja o autorach
    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    const ProcessingEngine *m_engine; // procesor filtrowania
};

#endif // MAINWINDOW_HPP
