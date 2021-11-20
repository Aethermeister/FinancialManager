#include "pocketdeletiondialog.h"
#include "ui_pocketdeletiondialog.h"

namespace Content::Pockets::Component
{
    PocketDeletionDialog::PocketDeletionDialog(const QString &pocketName, int recordsCount, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::PocketDeletionDialog)
    {
        ui->setupUi(this);

        //Set the widget attributes and flags
        setWindowFlags(Qt::FramelessWindowHint);
        setAttribute(Qt::WA_DeleteOnClose);

        //Create a QString which is used as the warning message in the dialog
        //The warning message contains the Pocket to be deleted and the linked Records count
        const QString warningMessage = QString("You are about to delete the <b>%0</b> pocket which has <b>%1</b> record(s).<br>"
                                        "Both the pocket and the linked records will be deleted.<br><br>"
                                        "This operation is irreversible.<br>"
                                        "Are you sure you want to proceed?").arg(pocketName).arg(recordsCount);
        ui->m_warningInformation_lbl->setText(warningMessage);

        initializeConnections();
    }

    PocketDeletionDialog::~PocketDeletionDialog()
    {
        delete ui;
    }

    QPushButton *PocketDeletionDialog::cancelButton()
    {
        return ui->m_cancel_btn;
    }

    QPushButton *PocketDeletionDialog::deleteButton()
    {
        return ui->m_delete_btn;
    }

    void PocketDeletionDialog::initializeConnections() const
    {
        connect(ui->m_delete_btn, &QPushButton::clicked, this, &PocketDeletionDialog::slot_deleteButtonClicked);
        connect(ui->m_cancel_btn, &QPushButton::clicked, this, &PocketDeletionDialog::slot_cancelButtonClicked);
    }

    void PocketDeletionDialog::slot_deleteButtonClicked()
    {
        //Emit signal with the DELETE enum value and close this widget
        emit sig_finished(DeletionResult::DELETE);
        close();
    }

    void PocketDeletionDialog::slot_cancelButtonClicked()
    {
        //Emit signal with the CANCEL enum value and close this widget
        emit sig_finished(DeletionResult::CANCEL);
        close();
    }
}
