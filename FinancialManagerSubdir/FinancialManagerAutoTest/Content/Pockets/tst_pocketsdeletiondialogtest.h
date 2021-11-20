#ifndef POCKETSDELETIONDIALOGTEST_H
#define POCKETSDELETIONDIALOGTEST_H

#include <QTest>

class PocketsDeletionDialogTest : public QObject
{
    Q_OBJECT
public:
    PocketsDeletionDialogTest() = default;

private slots:
    void test_cancelDialog();
    void test_deleteDialog();
};

#endif // POCKETSDELETIONDIALOGTEST_H
