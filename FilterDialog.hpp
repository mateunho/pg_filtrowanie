#ifndef FILTERDIALOG_HPP
#define FILTERDIALOG_HPP


#include <QDialog>


#include <opencv2/core/core.hpp> // cv::Matx


class ImagesDialog;
class QLineEdit;


namespace Ui {
class FilterDialog;
}


class FilterDialog : public QDialog
{
    Q_OBJECT

public:
    FilterDialog(ImagesDialog *_parent, cv::Mat _filter);
    ~FilterDialog();
    typedef cv::Matx<double, 9, 9> Matx99d;
    typedef cv::Matx<QLineEdit*, 9, 9> Matx99qle;

private:
    // tworzy macierz zer 9x9 z jedynka na przecieciu przekatnych
    Matx99d getInitialMatrix();

    // zbiera dane z interfejsu i zwraca w postaci macierzy
    cv::Mat getFilterInterfaceData();

    // ustawia w interfejsie dane wartosci filtra
    void setFilterInterfaceData(Matx99d _filter);

    // tworzy w interfejsie pola wprowadzania danych
    void createLineEdits();

private slots:
    // obsluga zastosowania filtra
    void on_btn_applyFilter_clicked();

    // obsluga anulowania
    void on_btn_cancel_clicked();

    // obsluga zamkniecia okna
    void closeEvent(QCloseEvent *_event);

    // obsluga ustawienia domyslnego filtra
    void on_btn_resetFilter_clicked();

private:
    Ui::FilterDialog *ui;
    ImagesDialog *m_parent; // wskaznik na okno z obrazkami
    Matx99qle m_lineEdits; // wektor z polami wpisywania danych
};

#endif // FILTERDIALOG_HPP
