#include "tst_widgetdefines.h"
#include "tst_encrypt.h"

#include <QtTest>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Test::Core::WidgetDefinesTest widgetDefinesTest;
    Test::Core::EncryptTest encryptTest;

    return
            (
                QTest::qExec(&widgetDefinesTest, argc, argv) ||
                QTest::qExec(&encryptTest, argc, argv)
            );
}
