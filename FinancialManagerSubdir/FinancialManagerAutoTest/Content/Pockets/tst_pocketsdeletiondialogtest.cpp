#include "tst_pocketsdeletiondialogtest.h"
#include "Content/Pockets/Components/pocketdeletiondialog.h"

#include <QSignalSpy>

void PocketsDeletionDialogTest::test_cancelDialog()
{
    Content::Pockets::Component::PocketDeletionDialog* deletionDialog = new Content::Pockets::Component::PocketDeletionDialog("test", 10);

    qRegisterMetaType<Content::Pockets::Component::DeletionResult>();
    QSignalSpy spy(deletionDialog, &Content::Pockets::Component::PocketDeletionDialog::sig_finished);

    deletionDialog->cancelButton()->click();

    QList<QVariant> arguments = spy.takeFirst();
    QCOMPARE(arguments.at(0), Content::Pockets::Component::DeletionResult::CANCEL);
}

void PocketsDeletionDialogTest::test_deleteDialog()
{
    Content::Pockets::Component::PocketDeletionDialog* deletionDialog = new Content::Pockets::Component::PocketDeletionDialog("test", 10);

    qRegisterMetaType<Content::Pockets::Component::DeletionResult>();
    QSignalSpy spy(deletionDialog, &Content::Pockets::Component::PocketDeletionDialog::sig_finished);

    deletionDialog->deleteButton()->click();

    QList<QVariant> arguments = spy.takeFirst();
    QCOMPARE(arguments.at(0), Content::Pockets::Component::DeletionResult::DELETE);
}
