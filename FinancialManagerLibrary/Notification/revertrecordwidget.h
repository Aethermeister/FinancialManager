#ifndef REVERTRECORDWIDGET_H
#define REVERTRECORDWIDGET_H
#include "notificationbase.h"
#include "user.h"

#include <QFrame>

namespace Ui {
class RevertRecordWidget;
}

namespace Notification
{
    /**
     * Component ui class derived from the NotificationBase class
     * and used by the NewRecordWidget ui class
     * This class is responsible to schedule the persistence of the new Records
     * Also provides a 'Revert' option which nullifies the given Record
    */
    class RevertRecordWidget : public QFrame, public NotificationBase
    {
        Q_OBJECT

    public:
        explicit RevertRecordWidget(const Content::Records::Record& record, std::shared_ptr<User> user, QWidget *parent = nullptr);
        ~RevertRecordWidget();

    private:
        Ui::RevertRecordWidget *ui;

        /**
         * Sets the initial state of the Ui
        */
        void initializeUi();
        /**
         * Sets the common connections related to this class
        */
        void initializeConnections() const;

        /**
         * The new Record which needs to be persisted
        */
        Content::Records::Record m_record;
        /**
         * The current user which persists the new Record
        */
        std::shared_ptr<User> m_user;

    private slots:
        /**
         * Called when the user clicks the Revert button
         * The creation countdown stops and the Record is discarded
        */
        void slot_revertButtonClicked();
    };
}

#endif // REVERTRECORDWIDGET_H
