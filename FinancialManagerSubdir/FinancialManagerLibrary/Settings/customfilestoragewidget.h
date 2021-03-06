#ifndef CUSTOMFILESTORAGEWIDGET_H
#define CUSTOMFILESTORAGEWIDGET_H
#include "Core/global_defines.h"

#include <QWidget>
#include <QLineEdit>

namespace Ui {
class CustomFileStorageWidget;
}

namespace Settings
{
    /**
     * Ui class which provides interactable interface for the user to manage the custom application file path
     * This class is responsible for selecting, saving and indicating the user selected folder path
    */
    class LIB_EXPORT CustomFileStorageWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit CustomFileStorageWidget(QWidget *parent = nullptr);
        ~CustomFileStorageWidget();

        /**
         * Returns the custom file storage widget's custom application folder path QLineEdit
         * Used so test project(s) can access it
        */
        QLineEdit* managedApplicationFolderLineEdit();

    private:
        Ui::CustomFileStorageWidget *ui;

        /**
         * Sets the initial state of the Ui
        */
        void initializeUi();
        /**
         * Sets the common connections related to this class
        */
        void initializeConnections() const;

    private slots:
        /**
         * Called when the browse button is clicked
         * Opens a folder selecting dialog and returns and saves the newly selected path
        */
        void slot_browseApplicationFolder();
        /**
         * Called when the 'm_managedApplicationFolder_lineEdit' emits an editingFinished signal
         * Saves the new custom path to the settings
        */
        void slot_saveApplicationFolderPath();
    };
}

#endif // CUSTOMFILESTORAGEWIDGET_H
