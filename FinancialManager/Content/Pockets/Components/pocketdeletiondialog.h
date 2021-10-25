#ifndef POCKETDELETIONDIALOG_H
#define POCKETDELETIONDIALOG_H

#include <QDialog>

namespace Ui {
class PocketDeletionDialog;
}

namespace Content::Pockets::Component
{
    /**
     * Enum holding the possible dialog result values
    */
    enum DeletionResult
    {
        DELETE,
        CANCEL
    };

    /**
     * Ui class which acts as a confirmation dialog
     * The user can cancel the Pocket deletion or confirm it
    */
    class PocketDeletionDialog : public QDialog
    {
        Q_OBJECT

    public:
        explicit PocketDeletionDialog(const QString& pocketName, int recordsCount, QWidget *parent = nullptr);
        ~PocketDeletionDialog();

    private:
        Ui::PocketDeletionDialog *ui;

        /**
         * Sets the common connections related to this class
        */
        void initializeConnections() const;

    private slots:
        /**
         * Called when the user clicks on the 'Delete' button confirming the deletion
        */
        void slot_deleteButtonClicked();
        /**
         * Called when the user clicks on the 'Cancel' button cancelling the deletion
        */
        void slot_cancelButtonClicked();

    signals:
        /**
         * Emitted when the user confirms or cancels the deletion
         * The carried parameter is set according to the dialog result
        */
        void sig_finished(Content::Pockets::Component::DeletionResult result);
    };
}

#endif // POCKETDELETIONDIALOG_H
