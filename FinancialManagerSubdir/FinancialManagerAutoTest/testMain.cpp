#include "Core/tst_widgetdefines.h"
#include "Core/tst_encrypt.h"
#include "Core/tst_defines.h"

#include <QtTest>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Test::Core::WidgetDefinesTest widgetDefinesTest;
    Test::Core::EncryptTest encryptTest;
    Test::Core::DefinesTest definesTest;

    return
            (
                QTest::qExec(&widgetDefinesTest, argc, argv) ||
                QTest::qExec(&encryptTest, argc, argv) ||
                QTest::qExec(&definesTest, argc, argv)
            );
}
