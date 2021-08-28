#ifndef WIDGETSTYLEBASE_H
#define WIDGETSTYLEBASE_H

#include <QWidget>
#include <QLineEdit>

class WidgetStyleBase
{
public:
    WidgetStyleBase() = default;

protected:
    void updateWidgetStyle(QWidget* widget);

    void setLineEditErrorStyle(QLineEdit* lineEdit, bool error);
};

#endif // WIDGETSTYLEBASE_H
