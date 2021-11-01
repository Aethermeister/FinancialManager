#include "generaloverviewmessagewidget.h"
#include "ui_generaloverviewmessagewidget.h"

namespace Content::Overview::Components
{
    GeneralOverviewMessageWidget::GeneralOverviewMessageWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::GeneralOverviewMessageWidget)
    {
        ui->setupUi(this);
    }

    GeneralOverviewMessageWidget::~GeneralOverviewMessageWidget()
    {
        delete ui;
    }
}
