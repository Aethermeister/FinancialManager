#ifndef WIDGETDEFINES_H
#define WIDGETDEFINES_H

#endif // WIDGETDEFINES_H

#include <QStyle>

#include <QWidget>
#include <QLayout>
#include <QLineEdit>
#include <QLabel>

/**
 * Removes the child QWidget of the parameter given parentWidget and parentLayout
 * and deletes the removed QWidget
*/
inline void deleteActiveContentWidget(QWidget* parentWidget, QLayout* parentLayout);

/**
 * Unpolishes and polishes the style of the parameter given QWidget
*/
inline void updateWidgetStyle(QWidget* widget);

/**
 * Sets the error property for the parameter given QLineEdit
 * After the new property value is set updates the QLineEdit style
 * so the ui changes are applied
*/
inline void setLineEditErrorState(QLineEdit* lineEdit, bool error);
/**
 * Sets the isNegative property for the parameter given QLabel
 * After the new property value is set updates the QLabel style
 * so the ui changes are applied
*/
inline void setLabelNegativeState(QLabel* label, bool isNegative);

/**
 * Shows the parameter given QLabel and sets its text with the parameter given message
*/
inline void showInformation(QLabel* label, const QString& message);


inline void deleteActiveContentWidget(QWidget* parentWidget, QLayout* parentLayout)
{
    //Get the current QWidget child to the parameter given parentWidget
    //and remove it from parameter given parentLayout if it is valid
    //and delete it
    auto activeWidget = parentWidget->findChild<QWidget*>();
    if(activeWidget)
    {
        parentLayout->removeWidget(activeWidget);
        activeWidget->deleteLater();
    }
}

inline void updateWidgetStyle(QWidget* widget)
{
    widget->style()->unpolish(widget);
    widget->style()->polish(widget);
}

inline void setLineEditErrorState(QLineEdit* lineEdit, bool error)
{
    lineEdit->setProperty("error", error);

    //Update the style of the QLineEdit
    //so the dynamic property dependent changes are applied
    updateWidgetStyle(lineEdit);
}

inline void setLabelNegativeState(QLabel* label, bool isNegative)
{
    label->setProperty("isNegative", isNegative);

    //Update the style of the QLabel
    //so the dynamic property dependent changes are applied
    updateWidgetStyle(label);
}

inline void showInformation(QLabel* label, const QString& message)
{
    //Set the text of the parameter given QLabel with the message
    //and show the Qlabel
    label->setText(message);
    label->setVisible(true);
}
