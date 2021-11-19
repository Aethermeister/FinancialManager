#ifndef PROFILWIDGETTEST_H
#define PROFILWIDGETTEST_H

#include <QTest>

#include "Content/profilewidget.h"

class ProfilWidgetTest : public QObject
{
    Q_OBJECT
public:
    ProfilWidgetTest() = default;

private slots:
    void initTestCase();
    void cleanupTestCase();

    void test_initializeUiDefault();
    void test_initializeUiWithDeletion();
    void test_changePasswordFalse();
    void test_changePasswordTrue();
    void test_deleteAccount();
    void test_cancelDeletion();
};

#endif // PROFILWIDGETTEST_H
