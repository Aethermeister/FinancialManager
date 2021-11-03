#include <QtTest>
#include <QCoreApplication>
#include <QPushButton>
#include <QComboBox>

// add necessary includes here
#include "Core/widgetdefines.h"

class Core : public QObject
{
    Q_OBJECT

public:

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

void Core::initTestCase()
{

}

void Core::cleanupTestCase()
{

}

void Core::test_deleteActiveContentWidget()
{
    QWidget* containerWidget = new QWidget();
    QHBoxLayout* containerLayout = new QHBoxLayout(containerWidget);
    containerWidget->setLayout(containerLayout);

    QLabel* label = new QLabel(containerWidget);
    containerLayout->addWidget(label);

    QPushButton* button = new QPushButton(containerWidget);
    containerLayout->addWidget(button);

    QComboBox* comboBox = new QComboBox(containerWidget);
    containerLayout->addWidget(comboBox);

    const auto expectedLabelCountBeforeTest = 1;
    const auto expectedButtonCountBeforeTest = 1;
    const auto expectedComboBoxCountBeforeTest = 1;

    QCOMPARE(containerWidget->findChildren<QLabel*>().count(), expectedLabelCountBeforeTest);
    QCOMPARE(containerWidget->findChildren<QPushButton*>().count(), expectedButtonCountBeforeTest);
    QCOMPARE(containerWidget->findChildren<QComboBox*>().count(), expectedComboBoxCountBeforeTest);

    deleteActiveContentWidget<QLabel*>(containerWidget, containerLayout);
    QVERIFY(containerWidget->findChildren<QLabel*>().empty());
    QCOMPARE(containerWidget->findChildren<QPushButton*>().count(), expectedButtonCountBeforeTest);
    QCOMPARE(containerWidget->findChildren<QComboBox*>().count(), expectedComboBoxCountBeforeTest);

    deleteActiveContentWidget<QPushButton*>(containerWidget, containerLayout);
    QVERIFY(containerWidget->findChildren<QLabel*>().empty());
    QVERIFY(containerWidget->findChildren<QPushButton*>().empty());
    QCOMPARE(containerWidget->findChildren<QComboBox*>().count(), expectedComboBoxCountBeforeTest);

    deleteActiveContentWidget<QComboBox*>(containerWidget, containerLayout);
    QVERIFY(containerWidget->findChildren<QLabel*>().empty());
    QVERIFY(containerWidget->findChildren<QPushButton*>().empty());
    QVERIFY(containerWidget->findChildren<QComboBox*>().empty());

    containerWidget->deleteLater();
}

void Core::test_updateWidgetStyle()
{
    QWidget* widget = new QWidget();
    updateWidgetStyle(widget);
}

void Core::test_setWidgetErrorState()
{
    QWidget* widgetErrorTrue = new QWidget();
    setWidgetErrorState(widgetErrorTrue, true);
    const auto trueErrorState = widgetErrorTrue->property("error").toBool();
    const auto expectedTrueErrorState = true;
    QCOMPARE(trueErrorState, expectedTrueErrorState);
    widgetErrorTrue->deleteLater();

    QWidget* widgetErrorFalse = new QWidget();
    setWidgetErrorState(widgetErrorFalse, false);
    const auto falseErrorState = widgetErrorFalse->property("error").toBool();
    const auto expectedFalseErrorState = false;
    QCOMPARE(falseErrorState, expectedFalseErrorState);
    widgetErrorFalse->deleteLater();
}

void Core::test_setLabelNegativeState()
{
    const int positiveValue = 1500;
    QLabel* positiveLabel = new QLabel();
    setLabelNegativeState(positiveLabel, positiveValue);
    const QString expectedPositiveValueText = "+1500";
    const bool expectedPositiveLabelState = false;
    QCOMPARE(positiveLabel->text(), expectedPositiveValueText);
    QCOMPARE(positiveLabel->property("isNegative").toBool(), expectedPositiveLabelState);
    positiveLabel->deleteLater();

    const int negativeValue = -5000;
    QLabel* negativeLabel = new QLabel();
    setLabelNegativeState(negativeLabel, negativeValue);
    const QString expectedNegativeValueText = "-5000";
    const bool expectedNegativeLabelState = true;
    QCOMPARE(negativeLabel->text(), expectedNegativeValueText);
    QCOMPARE(negativeLabel->property("isNegative").toBool(), expectedNegativeLabelState);
    negativeLabel->deleteLater();
}

void Core::test_setWidgetStyleByProperty()
{
    QWidget* boolWidget = new QWidget();
    const bool expectedBool = true;
    setWidgetStyleByProperty(boolWidget, "boolProperty", expectedBool);
    QCOMPARE(boolWidget->property("boolProperty").toBool(), expectedBool);
    boolWidget->deleteLater();

    QWidget* intWidget = new QWidget();
    const int expectedInt = 3;
    setWidgetStyleByProperty(intWidget, "intProperty", expectedInt);
    QCOMPARE(intWidget->property("intProperty").toInt(), expectedInt);
    intWidget->deleteLater();

    QWidget* stringWidget = new QWidget();
    const QString expectedString = "Test";
    setWidgetStyleByProperty(stringWidget, "stringProperty", expectedString);
    QCOMPARE(stringWidget->property("stringProperty").toString(), expectedString);
    stringWidget->deleteLater();
}

void Core::test_showInformation()
{
    QLabel* label = new QLabel();
    label->setGeometry(10,10,100,100);
    const QString expectedLabelText = "Test";
    showInformation(label, expectedLabelText);
    QCOMPARE(label->text(), expectedLabelText);
    QCOMPARE(label->isVisible(), true);
    label->deleteLater();
}

QTEST_MAIN(Core)

#include "tst_core.moc"
