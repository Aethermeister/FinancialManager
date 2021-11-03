#ifndef WIDGETDEFINES_H
#define WIDGETDEFINES_H

#endif // WIDGETDEFINES_H

#include <QStyle>

#include <QWidget>
#include <QLayout>
#include <QLineEdit>
#include <QLabel>

/**
 * Unpolishes and polishes the style of the parameter given QWidget
*/
inline void updateWidgetStyle(QWidget* widget);

/**
 * Sets the error property for the parameter given QWidget
 * After the new property value is set updates the QWidget style
 * so the ui changes are applied
*/
inline void setWidgetErrorState(QWidget* widget, bool error);
/**
 * Sets the isNegative property for the parameter given QLabel
 * After the new property value is set updates the QLabel style
 * so the ui changes are applied
*/
inline void setLabelNegativeState(QLabel* label, int value);
/**
 * Sets the parameter given property
 * and updates the given QWidget
 * so the ui changes are applied
*/
inline void setWidgetStyleByProperty(QWidget *widget, const QString &propertyName, const QVariant &stateValue);
/**
 * Shows the parameter given QLabel and sets its text with the parameter given message
*/
inline void showInformation(QLabel* label, const QString& message);


/**
 * Removes the child T object of the parameter given parentWidget and parentLayout
 * and deletes the removed T object
*/
template<typename T>
inline void deleteActiveContentWidget(QWidget* parentWidget, QLayout* parentLayout)
{
    //Get the current T child of the parameter given parentWidget
    //and remove it from parameter given parentLayout if it is valid
    //and delete it
    //To remove the object and delete it the T object has to be casted to QWidget
    auto activeWidget = dynamic_cast<QWidget*>(parentWidget->findChild<T>());
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

inline void setWidgetErrorState(QWidget* widget, bool error)
{
    widget->setProperty("error", error);

    //Update the style of the QWidget
    //so the dynamic property dependent changes are applied
    updateWidgetStyle(widget);
}

inline void setLabelNegativeState(QLabel* label, int value)
{
    auto valueString = QString::number(value);

    //Check whether the value is negative or not
    //and change the style accordingly
    const bool isValueNegative = value < 0;
    if(!isValueNegative)
    {
        valueString = "+" + valueString;
    }
    label->setText(valueString);

    label->setProperty("isNegative", isValueNegative);

    //Update the style of the QLabel
    //so the dynamic property dependent changes are applied
    updateWidgetStyle(label);
}

inline void setWidgetStyleByProperty(QWidget *widget, const QString &propertyName, const QVariant &stateValue)
{
    widget->setProperty(propertyName.toStdString().c_str(), stateValue);
    updateWidgetStyle(widget);
}

inline void showInformation(QLabel* label, const QString& message)
{
    //Set the text of the parameter given QLabel with the message
    //and show the Qlabel
    label->setText(message);
    label->setVisible(true);
}
