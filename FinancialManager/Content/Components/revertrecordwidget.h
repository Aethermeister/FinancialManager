#ifndef REVERTRECORDWIDGET_H
#define REVERTRECORDWIDGET_H
#include <user.h>

#include <QFrame>

namespace Ui {
class RevertRecordWidget;
}

namespace Content::Component
{
    /**
     * Component ui class used by the NewRecordWidget ui class
     * This class is responsible to schedule the persistence of the new Records
     * Also provides a 'Revert' option which nullifies the given Record
    */
    class RevertRecordWidget : public QFrame
    {
        Q_OBJECT

    public:
        explicit RevertRecordWidget(const Record& record, std::shared_ptr<User> user, QWidget *parent = nullptr);
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
         * Overridden EventFilter so custom behaviour can be implemented
        */
        bool eventFilter(QObject* watched, QEvent* event) override;
        /**
         * Move the currently active RevertRecordWidget widgets
         * so they are shown in their correct position
        */
        void moveActiveRevertRecordsWidgets();

        /**
         * Persist the Record in memory if the user did not reverted the Record creation
        */
        void persistRecord();

        /**
         * Stores the currently active RevertRecordWidget widgets
        */
        static QList<RevertRecordWidget*> ActiveRevertRecordsWidgets;

        Record m_record;
        std::shared_ptr<User> m_user;

        QTimer* m_timer;
        const int m_timeout = 50; //The interval for the QTimer timeout signal
        const int m_time = 5000; //The QTimer runs for this long [ms]
        int m_remainingTime = m_time; //The QTimer has this long to run [ms]
        bool m_isRevertClicked = false; //This flag indicates whether the Record should be persisted or not

    private slots:
        /**
         * Called when the user clicks the Revert button
         * The creation countdown stops and the Record is discarded
        */
        void slot_revertButtonClicked();
    };
}

#endif // REVERTRECORDWIDGET_H
