#ifndef IMAGESDIALOG_HPP
#define IMAGESDIALOG_HPP


#include <QDialog>


#include <opencv2/core/core.hpp> // cv::Mat


class QCloseEvent;
class ProcessingEngine;
class FilterDialog;


namespace Ui {
class ImagesDialog;
}


class ImagesDialog : public QDialog
{
    Q_OBJECT

public:
    ImagesDialog(QWidget *_parent, const ProcessingEngine *_engine);
    ~ImagesDialog();

    // otwiera podany obrazek i zapisuje w "m_imgOriginal"
    void OpenImage(QString _filename);

    // pozbywa sie okienka filtrowania "m_filterDialog"
    void DisposeFilterDialog();

    // umozliwia zmiane wartosci filtra "m_filter"
    void SetFilter(cv::Mat _filter);

    // wywoluje metode filtrujaca
    // i ustawia przefiltrowany obrazek w interfejsie i zapisuje w "m_imgFiltered"
    void ApplyFilter();

private slots:
    // obsluga tworzenia okna ustawiania filtra
    void on_btn_setFilter_clicked();

    // obsluga zamkniecia okna
    void closeEvent(QCloseEvent *_event);

    // obsluga zapisu przefiltrowanego obrazka
    void on_btn_saveImage_clicked();

private:
    Ui::ImagesDialog *ui;
    cv::Mat m_imgOriginal, m_imgFiltered;   // przechowuje obrazki
    cv::Mat m_filter;                       // przechowuje stan filtra
    FilterDialog *m_filterDialog;           // wskaznik na okienko z ustawieniami filtra
    const ProcessingEngine *m_engine;       // procesor filtrowania
};

#endif // IMAGESDIALOG_HPP
