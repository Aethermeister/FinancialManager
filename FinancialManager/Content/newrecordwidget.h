#ifndef NEWRECORDWIDGET_H
#define NEWRECORDWIDGET_H
#include "user.h"

#include <QWidget>

namespace Ui {
class NewRecordWidget;
}

namespace Content
{
    /**
     * Ui class which provides interactable interface for the user to create new Records
     * This class is responsible to correctly create a new Record
    */
    class NewRecordWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit NewRecordWidget(std::shared_ptr<User> user, QWidget *parent = nullptr);
        ~NewRecordWidget();

    private:
        Ui::NewRecordWidget *ui;

        /**
         * Sets the initial state of the Ui
        */
        void initializeUi();
        /**
         * Sets the initial state of the Record Settings section of this widget
        */
        void initializeRecordSettings();
        /**
         * Sets the initial state of the Date Time Settings section of this widget
        */
        void initializeDateTimeSettings();
        /**
         * Sets the common connections related to this class
        */
        void initializeConnections();

        std::shared_ptr<User> m_user;

    private slots:
        /**
         * Called when the Submit QPushButton is clicked
         * Starts the new Record validation and persisting procedure
        */
        void slot_submit();
    };

//    class RevertRecordWidget : public QWidget
//    {
//    public:
//        RevertRecordWidget(QWidget *parent = nullptr);
//        ~RevertRecordWidget();

//    private:
//        bool eventFilter(QObject* watched, QEvent* event) override;
//        void moveActiveRevertRecordsWidget();

//        static QList<RevertRecordWidget*> ActiveRevertRecordsWidgets;

//        const int m_fixWidth = 250;
//        const int m_fixHeight = 150;

//        int m_timeout = 5;
//    };
}

#endif // NEWRECORDWIDGET_H
