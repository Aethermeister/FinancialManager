#ifndef GENERALOVERVIEWMESSAGEWIDGET_H
#define GENERALOVERVIEWMESSAGEWIDGET_H
#include "Core/global_defines.h"

#include <QWidget>

namespace Ui {
class GeneralOverviewMessageWidget;
}

namespace Content::Overview::Components
{
    /**
     * Ui class which provides general help information to the user
    */
    class LIB_EXPORT GeneralOverviewMessageWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit GeneralOverviewMessageWidget(QWidget *parent = nullptr);
        ~GeneralOverviewMessageWidget();

    private:
        Ui::GeneralOverviewMessageWidget *ui;
    };
}

#endif // GENERALOVERVIEWMESSAGEWIDGET_H
