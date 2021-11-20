#include "customfilestoragewidget.h"
#include "ui_customfilestoragewidget.h"
#include "settingsmanager.h"

#include <QFileDialog>

namespace Settings
{
    CustomFileStorageWidget::CustomFileStorageWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::CustomFileStorageWidget)
    {
        ui->setupUi(this);

        initializeUi();
        initializeConnections();
    }

    CustomFileStorageWidget::~CustomFileStorageWidget()
    {
        delete ui;
    }

    QLineEdit *CustomFileStorageWidget::managedApplicationFolderLineEdit()
    {
        return ui->m_managedApplicationFolder_lineEdit;
    }

    void CustomFileStorageWidget::initializeUi()
    {
        //Get the stored custom application folder path from the settings
        //and set the corresponding QLineEdit's text with it
        const auto applicationFolderPath = SettingsManager::instance()->data<QString>(SettingsData::CUSTOM_STORAGE_PATH);
        ui->m_managedApplicationFolder_lineEdit->setText(applicationFolderPath);
    }

    void CustomFileStorageWidget::initializeConnections() const
    {
        connect(ui->m_browse_btn, &QPushButton::clicked, this, &CustomFileStorageWidget::slot_browseApplicationFolder);
        connect(ui->m_managedApplicationFolder_lineEdit, &QLineEdit::editingFinished, this, &CustomFileStorageWidget::slot_saveApplicationFolderPath);
    }

    void CustomFileStorageWidget::slot_browseApplicationFolder()
    {
        //Open a QFileDialog for directory selection using the current custom path as base path
        const auto pathBase = ui->m_managedApplicationFolder_lineEdit->text();
        QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                         pathBase,
                                                         QFileDialog::ShowDirsOnly
                                                         | QFileDialog::DontResolveSymlinks);

        //Set the corresponding QLineEdit's text with the newly selected directory path
        //and emit an editingFinished signal so the new value is saved
        ui->m_managedApplicationFolder_lineEdit->setText(dir);
        emit ui->m_managedApplicationFolder_lineEdit->editingFinished();
    }

    void CustomFileStorageWidget::slot_saveApplicationFolderPath()
    {
        //Save the currently set custom application folde path as settings data
        const auto applicationFolderPath = ui->m_managedApplicationFolder_lineEdit->text();
        SettingsManager::instance()->setData(SettingsData::CUSTOM_STORAGE_PATH, applicationFolderPath);
    }
}
