#ifndef RECORDHISTORYITEMWIDGET_H
#define RECORDHISTORYITEMWIDGET_H
#include "user.h"

#include <QWidget>

namespace Ui {
class RecordHistoryItemWidget;
}

namespace Content::History::Component
{
    /**
     * Ui class which acts as indicator for a given Record
     * The RecordsHistoryWidget ui class uses a list of this RecordHistoryItemWidget
     * to list all of the Records for the current user
    */
    class RecordHistoryItemWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit RecordHistoryItemWidget(const Content::Records::Record& record, bool isInteractive, QWidget *parent = nullptr);
        ~RecordHistoryItemWidget();

        /**
         * Sets the checked state of whis object
        */
        void setChecked(bool checked);

        /**
         * Returns the Record which this object was initialized with
        */
        const Content::Records::Record& record() const;

    protected:
        void paintEvent(QPaintEvent *event) override;
        void enterEvent(QEvent *event) override;
        void leaveEvent(QEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;

    private:
        Ui::RecordHistoryItemWidget *ui;

        /**
         * Sets the initial state of the Ui
        */
        void initializeUi();

        /**
         * The Record this object is initialized with
        */
        Content::Records::Record m_record;

        /**
         * Flag which indicates whether this QWidget should be affected by the user through the mouse pointer
        */
        bool m_isInteractive;
        /**
         * Flag which indicates whether the mouse pointer is hovering this ui object
        */
        bool m_isMouseOver = false;
        /**
         * Flag which indicates whether the mouse left button is pressed on this ui object
        */
        bool m_isPressed = false;
        /**
         * Flag which indicates whether this ui object is checked
        */
        bool m_isChecked = false;

    signals:
        /**
         * Emitted when this ui object is clicked
        */
        void sig_recordItemClicked(bool checked);
    };
}

#endif // RECORDHISTORYITEMWIDGET_H
