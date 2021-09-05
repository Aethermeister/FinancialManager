#ifndef PROFILEWIDGET_H
#define PROFILEWIDGET_H
#include "user.h"

#include <QWidget>

namespace Ui {
class ProfileWidget;
}

namespace Content
{
    /**
     * Ui class which provides interactable interface for the user to manage the account
    */
    class ProfileWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit ProfileWidget(std::shared_ptr<User> user, QWidget *parent = nullptr);
        ~ProfileWidget();

    private:
        Ui::ProfileWidget *ui;

        /**
         * Sets the initial state of the Ui
        */
        void initializeUi();
        /**
         * Sets the common connections related to this class
        */
        void initializeConnections();

        /**
         * The current user
        */
        std::shared_ptr<User> m_user;
        /**
         * Message which is informing the user about the scheduled deletion of the account
        */
        const QString deletionMessage = "This account was marked for deletion and will be deleted after the next logout.\n"
                                        "Cancel the deletion by clicking on the 'Cancel Deletion' button";

    private slots:
        /**
         * Called when the Change Password QPushButton is clicked
         * Changes the user password if the necessary requirements are met
        */
        void slot_changePassword();
        /**
         * Called when the Delete Account QPushButton is clicked
         * Schedules the deletion after the next logout
        */
        void slot_markUserForDeletion();
        /**
         * Called when the Cancel Deletion QPushButton is clicked
         * Cancels the deletion of the account
        */
        void slot_cancelDeletion();

    signals:
        /**
         * Emitted when the user click the Logout QPushButton
        */
        void sig_requestLogout();
    };
}
#endif // PROFILEWIDGET_H
