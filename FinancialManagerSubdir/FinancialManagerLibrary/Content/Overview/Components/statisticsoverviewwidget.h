#ifndef STATISTICSOVERVIEWWIDGET_H
#define STATISTICSOVERVIEWWIDGET_H
#include "user.h"

#include <QWidget>

namespace Ui {
class StatisticsOverviewWidget;
}

namespace Content::Overview::Components
{
    /**
     * Ui class which provides base statistics information
     * Lists the recent Records and shows charts
    */
    class StatisticsOverviewWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit StatisticsOverviewWidget(std::shared_ptr<User> user, QWidget *parent = nullptr);
        ~StatisticsOverviewWidget();

    private:
        Ui::StatisticsOverviewWidget *ui;

        void initializeUi();

        std::shared_ptr<User> m_user;
    };
}
#endif // STATISTICSOVERVIEWWIDGET_H
