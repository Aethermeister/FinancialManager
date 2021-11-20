#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H
#include "Settings/settingsmanager.h"

#include <QDialog>
#include <QRadioButton>

namespace Ui {
class SettingsWindow;
}

namespace Settings
{
    /**
     * SettingsWindow Ui class
     * This modal QDialog is the base for every settings related widget
    */
    class LIB_EXPORT SettingsWindow : public QDialog
    {
        Q_OBJECT

    public:
        explicit SettingsWindow(QWidget *parent = nullptr);
        ~SettingsWindow();

        /**
         * Returns the Settings window's local file storage QRadioButton
         * Used so test project(s) can access it
        */
        QRadioButton* localFileStorageRadioButton();
        /**
         * Returns the Settings window's custom file storage QRadioButton
         * Used so test project(s) can access it
        */
        QRadioButton* customFileStorageRadioButton();
        /**
         * Returns the Settings window's file storage container QWidget
         * Used so test project(s) can access it
        */
        QWidget* fileStorageContainerWidget();

    private:
        Ui::SettingsWindow *ui;

        /**
         * Sets the initial state of the Ui
        */
        void initializeUi();
        /**
         * Sets the common connections related to this class
        */
        void initializeConnections() const;

        /**
         * Creates the needed File Storage content widget according to the parameter given value
         * and shows this widget in the content area
        */
        void showFileStorageContentWidget(FileStorage fileStorage);

    private slots:
        /**
         * Called when the a QRadioButton changes state in the File Storage area
         * Updates the settings data and ui according to the new selection
        */
        void slot_fileStorageChanged(bool checked);
    };
}

#endif // SETTINGSWINDOW_H
