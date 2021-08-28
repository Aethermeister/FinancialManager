#include "widgetstylebase.h"

#include <QStyle>

void WidgetStyleBase::updateWidgetStyle(QWidget *widget)
{
    widget->style()->unpolish(widget);
    widget->style()->polish(widget);
}

void WidgetStyleBase::setLineEditErrorStyle(QLineEdit *lineEdit, bool error)
{
    lineEdit->setProperty("error", error);
    updateWidgetStyle(lineEdit);
}
