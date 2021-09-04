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

    public slots:
        /**
         * Q_SLOT of the showProfileWidget method to make it public
        */
        void slot_showProfileWidget();

    protected:
        void resizeEvent(QResizeEvent *event);

    private:
        Ui::ContentWidget *ui;

        /**
         * Sets the common connections related to this class
        */
        void initializeConnections() const;

        /**
         * Sets the checked state of the QPushButtons in the control menu area
        */
        void adjustControlButtons();

        /**
         * Shows the OverviewWidget ui in the content area
        */
        void showOverviewWidget();
        /**
         * Shows the NewRecordWidget ui in the content area
        */
        void showNewRecordWidget();

        /**
         * Shows the ProfileWidget ui in the content area
        */
        void showProfileWidget();

        /**
         * The current user
        */
        std::shared_ptr<User> m_user;

    signals:
        /**
         * Signal emitted when the user wants to logout
        */
        void sig_logout();
    };

    #endif // CONTENTWIDGET_H
}
