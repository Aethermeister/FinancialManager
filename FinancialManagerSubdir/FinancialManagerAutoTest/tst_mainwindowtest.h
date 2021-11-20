#ifndef MAINWINDOWTEST_H
#define MAINWINDOWTEST_H

#include <QTest>

class MainWindowTest : public QObject
{
    Q_OBJECT
public:
    MainWindowTest() = default;

private slots:
    void initTestCase();
    void cleanupTestCase();

    void test_mainWindowContents();
};

#endif // MAINWINDOWTEST_H
