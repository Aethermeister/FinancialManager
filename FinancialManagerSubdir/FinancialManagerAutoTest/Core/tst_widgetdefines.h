#ifndef TST_WIDGETDEFINES_H
#define TST_WIDGETDEFINES_H
#include <QtTest>

#include "Core/defines.h"

namespace Test::Core
{
    class WidgetDefinesTest : public QObject
    {
        Q_OBJECT

    public:
        WidgetDefinesTest() = default;

    private slots:
        void initTestCase();
        void cleanupTestCase();
        void test_deleteActiveContentWidget();
        void test_updateWidgetStyle();
        void test_setWidgetErrorState();
        void test_setLabelNegativeState();
        void test_setWidgetStyleByProperty();
        void test_showInformation();
    };
}

#endif // TST_WIDGETDEFINES_H
