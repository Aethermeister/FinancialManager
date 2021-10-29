#include "settingswindow.h"
#include "ui_settingswindow.h"
#include "Core/defines.h"
#include "localfilestoragewidget.h"
#include "customfilestoragewidget.h"

namespace Settings
{
    SettingsWindow::SettingsWindow(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::SettingsWindow)
    {
        ui->setupUi(this);

        //initializeConnections is called before the initializeUi so the initial content widget can be shown as well
        initializeConnections();
        initializeUi();
    }

    SettingsWindow::~SettingsWindow()
    {
        delete ui;
    }

    void SettingsWindow::initializeUi()
    {
        //Set the QDialog properties
        setWindowFlags(Qt::FramelessWindowHint);
        setFixedSize(500, 350);

        //Add dynamic properties to the sile storage QRadioButtons for future usage
        ui->m_local_radioBtn->setProperty("FILE_STORAGE", FileStorage::LOCAL);
        ui->m_custom_radioBtn->setProperty("FILE_STORAGE", FileStorage::CUSTOM);
        ui->m_database_radioBtn->setProperty("FILE_STORAGE", FileStorage::DATABASE);

        //Get the File Storage settings data and set the ui according to this value
        const auto selectedFileStorage = SettingsManager::instance()->data<int>(SettingsData::FILE_STORAGE);
        if(selectedFileStorage == FileStorage::LOCAL)
        {
            ui->m_local_radioBtn->setChecked(true);
        }
        else if(selectedFileStorage == FileStorage::CUSTOM)
        {
            ui->m_custom_radioBtn->setChecked(true);
        }
        else if(selectedFileStorage == FileStorage::DATABASE)
        {
            ui->m_database_radioBtn->setChecked(true);
        }
    }

    void SettingsWindow::initializeConnections() const
    {
        connect(ui->m_local_radioBtn, &QRadioButton::toggled, this, &SettingsWindow::slot_fileStorageChanged);
        connect(ui->m_custom_radioBtn, &QRadioButton::toggled, this, &SettingsWindow::slot_fileStorageChanged);
        connect(ui->m_database_radioBtn, &QRadioButton::toggled, this, &SettingsWindow::slot_fileStorageChanged);

        connect(ui->m_ok_btn, &QPushButton::clicked, this, &QDialog::deleteLater);
    }

    void SettingsWindow::showFileStorageContentWidget(FileStorage fileStorage)
    {
        //Delete the current widget from the container widget
        deleteActiveContentWidget<QWidget*>(ui->m_fileStorageContainer_widget, ui->m_fileStorageContainer_layout);

        //Create the needed File Storage content widget according to the current selection
        if(fileStorage == FileStorage::LOCAL)
        {
            LocalFileStorageWidget* localFileStorageWidget = new LocalFileStorageWidget(ui->m_fileStorageContainer_widget);
            ui->m_fileStorageContainer_layout->addWidget(localFileStorageWidget);
        }
        else if(fileStorage == FileStorage::CUSTOM)
        {
            CustomFileStorageWidget* customFileStorageWidget = new CustomFileStorageWidget(ui->m_fileStorageContainer_widget);
            ui->m_fileStorageContainer_layout->addWidget(customFileStorageWidget);
        }
    }

    void SettingsWindow::slot_fileStorageChanged(bool checked)
    {
        //If the parameter given value is false/the sender QRadioButton is unchecked do nothing
        if(!checked)
        {
            return;
        }

        //Get the sender QRadioButton and get its FILE_STORAGE dynamic property
        const auto senderButton = qobject_cast<QRadioButton*>(sender());
        const auto fileStorage = senderButton->property("FILE_STORAGE");

        //Store the new File Storage value as settings data and show the needed File Storage content widget
        SettingsManager::instance()->setData(SettingsData::FILE_STORAGE, fileStorage);
        showFileStorageContentWidget(qvariant_cast<FileStorage>(fileStorage));
    }
}
