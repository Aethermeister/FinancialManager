#ifndef RECORDHISTORYITEMWIDGET_H
#define RECORDHISTORYITEMWIDGET_H
#include "user.h"

#include <QWidget>

namespace Ui {
class RecordHistoryItemWidget;
}

namespace Content::Component
{
    class RecordHistoryItemWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit RecordHistoryItemWidget(Record record, QWidget *parent = nullptr);
        ~RecordHistoryItemWidget();

        void setChecked(bool checked);

    protected:
        void paintEvent(QPaintEvent *event) override;
        void enterEvent(QEvent *event) override;
        void leaveEvent(QEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;

    private:
        Ui::RecordHistoryItemWidget *ui;

        void initializeUi();

        Record m_record;

        bool m_isMouseOver = false;
        bool m_isPressed = false;
        bool m_isChecked = false;

    signals:
        void sig_recordItemClicked(bool checked);
    };
}

#endif // RECORDHISTORYITEMWIDGET_H
