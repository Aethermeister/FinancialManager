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

        /**
         * Returns the instance of the only ContentWidget
        */
        static ContentWidget* instance();

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
         * Shows the PocketsWidget ui in the content area
        */
        void showPocketsWidget();

        /**
         * Shows the NewRecordWidget ui in the content area
        */
        void showNewRecordWidget();

        /**
         * Shows the HistoryWidget ui in the content area
        */
        void showHistoryWidget();

        /**
         * Shows the ProfileWidget ui in the content area
        */
        void showProfileWidget();

        /**
         * Instance of the only ContentWidget
        */
        static ContentWidget* s_instance;

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
