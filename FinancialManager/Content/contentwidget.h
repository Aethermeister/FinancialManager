#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H
#include "user.h"

#include <QWidget>

namespace Ui {
class ContentWidget;
}

namespace Content
{
    /**
     * This is the main content ui class
     * It contains a controller for the additional ui classes
     * and displays the selected widgets
    */
    class ContentWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit ContentWidget(std::shared_ptr<User> user, QWidget *parent = nullptr);
        ~ContentWidget();

    private:
        Ui::ContentWidget *ui;

        /**
         * Sets the common connections related to this class
        */
        void initializeConnections() const;

        /**
         * Shows the OverviewWidget ui in the content area
        */
        void showOverviewWidget();
        /**
         * Shows the NewRecordWidget ui in the content area
        */
        void showNewRecordWidget();

        std::shared_ptr<User> m_user;
    };

    #endif // CONTENTWIDGET_H
}
