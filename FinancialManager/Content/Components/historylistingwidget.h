#ifndef HISTORYLISTINGWIDGET_H
#define HISTORYLISTINGWIDGET_H
#include "recordcontentwidget.h"
#include "recordhistoryitemwidget.h"
#include "user.h"

#include <QWidget>

namespace Ui {
class HistoryListingWidget;
}

namespace Content::Component
{
    /**
     * Ui class which lists the given User's records
     * This class is responsible for keeping the listed records up-to-date
    */
    class HistoryListingWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit HistoryListingWidget(QWidget *parent = nullptr);
        ~HistoryListingWidget();

        /**
         * Initializes the widget by listing every Record of the given User
         * Also handles the user's interactions made on the listed Record items
        */
        void initialize(std::shared_ptr<User> user, Component::RecordContentWidget* recordContentWidget);
        /**
         * Initializes the widget by kisting the first X (parameter given) Record of the given User
        */
        void initialize(std::shared_ptr<User> user, int listedItemsCount = 10);

        /**
         * Returns the currently active/selected Record History Item Widget
        */
        Component::RecordHistoryItemWidget* activeRecordItemWidget() const;
        /**
         * Sets the active/selected Record History Item Widget
        */
        void setActiveRecordItemWidget(Component::RecordHistoryItemWidget* recordItemWidget);

        /**
         * Returns the listed Record History Item Widgets
        */
        QList<Component::RecordHistoryItemWidget*> recordItemWidgets() const;

    private:
        Ui::HistoryListingWidget *ui;

        /**
         * The currently selected Record item
         * It is initialized with nullptr because there is no selection at the beginning
        */
        Component::RecordHistoryItemWidget* m_activeRecordItemWidget = nullptr;

        /**
         * Shows an information QLabel instead of listing the Record items
         * This is automatically called when there is no Record during the initialization of the ui
        */
        void showNoRecordMessage();

    private slots:
        /**
         * Called when the user creates a new Record and the User object emits the corresponding signal
         * Creates a Record History Item Widget using the parameter given Record and inserts it in the index defined position
        */
        void slot_newRecordAdded(int index, const Record &record);
        /**
         * Called when the user deletes a Record and the User object emits the corresponding signal
         * Deletes the Record History Item Widget created with the parameter given Record
        */
        void slot_recordDeleted(const Record &record);
    };
}

#endif // HISTORYLISTINGWIDGET_H
