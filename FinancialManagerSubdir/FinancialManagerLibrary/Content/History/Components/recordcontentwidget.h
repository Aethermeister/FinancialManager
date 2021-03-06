#ifndef RECORDCONTENTWIDGET_H
#define RECORDCONTENTWIDGET_H
#include "user.h"

#include <QWidget>
#include <QPushButton>

namespace Ui {
class RecordContentWidget;
}

namespace Content::History::Component
{
    /**
     * Ui class which acts as an indicator for the given Record
     * The details of the Record are listed within this ui class
    */
    class LIB_EXPORT RecordContentWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit RecordContentWidget(QWidget *parent = nullptr);
        ~RecordContentWidget();

        QPushButton* deleteRecordButton();

        /**
         * Externally callable initialization method
         * Sets the state of the ui according to the parameter given Record
        */
        void initializeUi(const Content::Records::Record &selectedRecord);

    private:
        Ui::RecordContentWidget *ui;

        /**
         * Sets the common connections related to this class
        */
        void initializeConnections() const;

    signals:
        /**
         * Emitted when the user clicks on the Delete Record QPushButton
        */
        void sig_deleteRecord();
    };
}

#endif // RECORDCONTENTWIDGET_H
