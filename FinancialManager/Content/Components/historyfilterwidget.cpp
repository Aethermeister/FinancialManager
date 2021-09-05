#include "historyfilterwidget.h"
#include "ui_historyfilterwidget.h"

namespace Content::Component
{
    HistoryFilterWidget::HistoryFilterWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::HistoryFilterWidget)
    {
        ui->setupUi(this);
    }

    HistoryFilterWidget::~HistoryFilterWidget()
    {
        delete ui;
    }
}
