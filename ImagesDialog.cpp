#include "ImagesDialog.hpp"
#include "ui_ImagesDialog.h"

#include <QCloseEvent>
#include <QFileDialog>
#include "MainWindow.hpp"
#include "FilterDialog.hpp"
#include "ProcessingEngine.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


ImagesDialog::ImagesDialog(QWidget* _parent, const ProcessingEngine *_engine) :
    QDialog(_parent),
    ui(new Ui::ImagesDialog),
    m_filterDialog(nullptr),
    m_engine(_engine)
{
    ui->setupUi(this);
}


ImagesDialog::~ImagesDialog()
{
    delete ui;
}


void ImagesDialog::OpenImage(QString _filename)
{
    // to do pozniejszej obrobki
    m_imgOriginal = cv::imread(_filename.toLocal8Bit().data());
    cv::cvtColor(m_imgOriginal, m_imgOriginal, CV_BGR2RGB);

    // to do wyswietlenia
    QImage imgOriginal(_filename);
    imgOriginal = imgOriginal.scaledToWidth(500);
    ui->lbl_originalImg->setPixmap(QPixmap::fromImage(imgOriginal));
}


void ImagesDialog::DisposeFilterDialog()
{
    if(nullptr != m_filterDialog) {
        delete m_filterDialog;
        m_filterDialog = nullptr;
    }
}


void ImagesDialog::SetFilter(cv::Mat _filter)
{
    m_filter = _filter;
}


void ImagesDialog::ApplyFilter()
{
    cv::Scalar sum = cv::sum(m_filter); // suma elementow macierzy filtru
    // Scalar jest 4 kanalowym wektorem, a macierz filtru ma tylko jeden kanal
    // dlatego do normalizacji pobieramy element [0]
    cv::Mat filter = m_filter * 1./sum[0]; // normalizacja

    m_engine->Filter2D(m_imgOriginal, m_imgFiltered, filter); // filtrowanie

    if(true == m_imgFiltered.empty()) {
        return;
    }

    QImage imgFiltered(m_imgFiltered.data,
                       m_imgFiltered.cols,
                       m_imgFiltered.rows,
                       m_imgFiltered.step,
                       QImage::Format_RGB888);
    imgFiltered = imgFiltered.scaledToWidth(500);
    ui->lbl_filteredImg->setPixmap(QPixmap::fromImage(imgFiltered));
}


void ImagesDialog::on_btn_setFilter_clicked()
{
    if(nullptr == m_filterDialog) {
        m_filterDialog = new FilterDialog(this, m_filter);
        m_filterDialog->show();
    }
}


void ImagesDialog::closeEvent(QCloseEvent *_event)
{
    this->DisposeFilterDialog(); // zamyka okno potomne

    if(nullptr != _event) {
        _event->accept();
    }
}


void ImagesDialog::on_btn_saveImage_clicked()
{
    if(true == m_imgFiltered.empty()) {
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this,
                                                    "Save image",
                                                    "",
                                                    "Image files (*.jpg *.bmp *.png *.tif);;All files (*.*)",
                                                    0,
                                                    QFileDialog::DontUseNativeDialog);
    if(true == filename.isEmpty()) {
        return;
    }
    QImage imgFiltered(m_imgFiltered.data,
                       m_imgFiltered.cols,
                       m_imgFiltered.rows,
                       m_imgFiltered.step,
                       QImage::Format_RGB888);
    imgFiltered.save(filename);
}

