#ifndef OVERVIEWWIDGET_H
#define OVERVIEWWIDGET_H
#include "Core/global_defines.h"
#include "user.h"

#include <QWidget>

namespace Ui {
class OverviewWidget;
}

namespace Content::Overview
{
    /**
     * Ui class which provides a general overview of the user created Records and Pockets
     * If the user is new eand there are no Pockets or Records general help is provided
    */
    class LIB_EXPORT OverviewWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit OverviewWidget(std::shared_ptr<User> user, QWidget *parent = nullptr);
        ~OverviewWidget();

    private:
        Ui::OverviewWidget *ui;

        /**
         * Sets the initial state of the Ui
        */
        void initializeUi();
        /**
         * Shows the widget with a general help information
        */
        void showGeneralOverviewMessage();
        /**
         * Shows the statistics overview widget
        */
        void showStatisticsOverview();

        std::shared_ptr<User> m_user;
    };
}

#endif // OVERVIEWWIDGET_H
