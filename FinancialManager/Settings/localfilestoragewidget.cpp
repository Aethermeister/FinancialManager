#include "localfilestoragewidget.h"
#include "ui_localfilestoragewidget.h"
#include "Core/defines.h"

namespace Settings
{
    LocalFileStorageWidget::LocalFileStorageWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::LocalFileStorageWidget)
    {
        ui->setupUi(this);

        //Show information for the locally used application files path using the APPDATA folder path
        ui->m_localFileStorageInformation_lbl->setText(QString("Local file storage does not need user configuration\n"
                                                        "The application files are automatically managed at %0")
                                                       .arg(APPDATALOCATION()));
    }

    LocalFileStorageWidget::~LocalFileStorageWidget()
    {
        delete ui;
    }
}
