#include "FilterDialog.hpp"
#include "ui_FilterDialog.h"

#include <QCloseEvent>
#include <QLineEdit>
#include "ImagesDialog.hpp"


FilterDialog::FilterDialog(ImagesDialog *_parent, cv::Mat _filter) :
    QDialog(dynamic_cast<QWidget*>(_parent)),
    ui(new Ui::FilterDialog),
    m_parent(_parent)
{
    ui->setupUi(this);

    createLineEdits();

    if(false == _filter.empty()) {
        this->setFilterInterfaceData(Matx99d((const double*)_filter.data));
    }
    else {
        this->setFilterInterfaceData(getInitialMatrix());
    }
}


FilterDialog::~FilterDialog()
{
    delete ui;
}


FilterDialog::Matx99d FilterDialog::getInitialMatrix()
{
    Matx99d filter(cv::Mat(cv::Mat::zeros(9, 9, CV_64F)));
    filter(4, 4) = 1.0;
    return filter;
}


cv::Mat FilterDialog::getFilterInterfaceData()
{
    Matx99d filter;

    for (int i=0; i < 9; i++) {
        for (int j=0; j < 9; j++) {
            filter(i, j) = m_lineEdits(i, j)->text().toDouble();
        }
    }

    return cv::Mat(filter);
}


void FilterDialog::setFilterInterfaceData(Matx99d _filter)
{
    for (int i=0; i < 9; i++) {
        for (int j=0; j < 9; j++) {
            m_lineEdits(i, j)->setText(QString::number(_filter(i, j), 'f', 2));
        }
    }
}


void FilterDialog::createLineEdits()
{
    for (int i=0; i < 9; i++) {
        for (int j=0; j < 9; j++) {
            m_lineEdits(i, j) = new QLineEdit();
            ui->gridLayout->addWidget(m_lineEdits(i, j), i, j);
        }
    }
}


void FilterDialog::on_btn_applyFilter_clicked()
{
    m_parent->SetFilter(this->getFilterInterfaceData());
    m_parent->ApplyFilter();
    this->closeEvent(nullptr);
}


void FilterDialog::on_btn_cancel_clicked()
{
    this->closeEvent(nullptr);
}


void FilterDialog::closeEvent(QCloseEvent *_event)
{
    m_parent->DisposeFilterDialog(); // informuje okno rodzica

    if(nullptr != _event) {
        _event->accept();
    }
}


void FilterDialog::on_btn_resetFilter_clicked()
{
    this->setFilterInterfaceData(getInitialMatrix());
}

