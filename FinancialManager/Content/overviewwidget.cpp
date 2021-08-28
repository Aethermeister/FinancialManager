#include "overviewwidget.h"
#include "ui_overviewwidget.h"

namespace Content
{
    OverviewWidget::OverviewWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::OverviewWidget)
    {
        ui->setupUi(this);
    }

    OverviewWidget::~OverviewWidget()
    {
        delete ui;
    }
}
