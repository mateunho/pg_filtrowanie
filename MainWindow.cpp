#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QCloseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include "ImagesDialog.hpp"
#include "ProcessingEngine.hpp"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_engine(nullptr)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
    if(nullptr != m_engine) {
        delete m_engine;
    }
}


void MainWindow::SetEngine(const ProcessingEngine *_engine)
{
    m_engine = _engine;
}


void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    "Open image",
                                                    "",
                                                    "Image files (*.jpg *.bmp *.png *.tif);;All files (*.*)",
                                                    0,
                                                    QFileDialog::DontUseNativeDialog);
    if(true == filename.isEmpty()) {
        return;
    }

    ImagesDialog *image;
    image = new ImagesDialog(this, m_engine);
    image->setWindowTitle(filename);
    image->OpenImage(filename);
    image->show();
}


void MainWindow::on_actionExit_triggered()
{
    this->closeEvent(nullptr);
}


void MainWindow::on_actionUser_manual_triggered()
{
    QString brief = "This application was designed for linear filtering of greyscale or color images.";
    QString open = "1. step: Open image: File -> Open [Ctrl+O]";
    QString setFilter = "2. step: Set filter";
    QString applyFilter = "3. step: Apply specified filter";
    QString saveImage = "4. step: Save filtered image";
    QString repeat = "[repeat]";
    QString nl = "\n";
    QMessageBox msgBox;
    msgBox.addButton(QMessageBox::Close);
    msgBox.setWindowTitle("Mini tutorial");
    msgBox.setText(brief);
    msgBox.setDetailedText(open +nl+
                           setFilter +nl+
                           applyFilter +nl+
                           saveImage +nl+
                           repeat);
    msgBox.exec();
}


void MainWindow::on_actionAbout_triggered()
{
    QString brief = "This application was designed for linear filtering of greyscale or color images.";
    QString author = "Author: Mateusz Kacprzak";
    QString faculty = "wfis.uni.lodz.pl 2014";
    QString nl = "\n";
    QMessageBox::information(this,
                             "About",
                             brief +nl+nl+
                             author +nl+
                             faculty);
}


void MainWindow::closeEvent(QCloseEvent *_event)
{
    if(nullptr != _event) {
        _event->accept();
    }

    qApp->quit();
}

