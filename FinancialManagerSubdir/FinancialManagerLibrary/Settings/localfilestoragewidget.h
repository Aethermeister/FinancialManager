#ifndef LOCALFILESTORAGEWIDGET_H
#define LOCALFILESTORAGEWIDGET_H
#include "Core/global_defines.h"

#include <QWidget>

namespace Ui {
class LocalFileStorageWidget;
}

namespace Settings
{
    /**
     * Ui class which shows basic information for the locally used application files path
    */
    class LIB_EXPORT LocalFileStorageWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit LocalFileStorageWidget(QWidget *parent = nullptr);
        ~LocalFileStorageWidget();

    private:
        Ui::LocalFileStorageWidget *ui;
    };
}

#endif // LOCALFILESTORAGEWIDGET_H
