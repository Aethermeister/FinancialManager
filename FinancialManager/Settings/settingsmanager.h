#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QString>
#include <QVariant>
#include <QSettings>

namespace Settings
{
    /**
     * Enum which holds values for the File Storage selection
     *
     * LOCAL: The application files are saved to the APPDATA folder of the application
     * CUSTOM: The user can select a custom location for the application files
     * DATABASE: -
    */
    enum FileStorage
    {
        LOCAL,
        CUSTOM,
        DATABASE
    };

    /**
     * Enum which holds the keys for each settings data
     *
     * FILE_STORAGE: Has the value of the currently used FileStorage type
     * CUSTOM_STORAGE_PATH: QString value which holds the custom folder path of the application files
     * LAST_USER_NAME: The last successfully logged in user's username (if the REMEMBER_ME is true)
     * REMEMBER_ME: Indicates whether the user wants to save the last loggen in user credentials
    */
    enum SettingsData
    {
        FILE_STORAGE,
        CUSTOM_STORAGE_PATH,
        LAST_USER_NAME,
        REMEMBER_ME
    };

    /**
     * Singleton class for managing the application settings
    */
    class SettingsManager
    {
    public:
        SettingsManager();

        /**
         * Returns the instance of the SettingsManager
        */
        static SettingsManager* instance();

        /**
         * Stores the parameter given value with the given key in the registry
        */
        void setData(const SettingsData key, const QVariant &value);

        /**
         * Retrieves the settings data of the parameter given key from the registry
         * and returns it converting it to the required type
        */
        template<typename T>
        T data(const SettingsData key) const
        {
            QSettings settings;
            return qvariant_cast<T>(settings.value(QString::number(key)));
        }

    private:
        static SettingsManager* m_instance;

        /**
         * Called every instance initialization
         * Stores the default values of each missing settings key
        */
        void initializeSettingsData();

        /**
         * Default settings values mapped to their keys
        */
        const QMap<SettingsData, QVariant> DefaultSettingsValues =
        {
            {SettingsData::FILE_STORAGE, FileStorage::LOCAL},
            {SettingsData::CUSTOM_STORAGE_PATH, QString()},
            {SettingsData::LAST_USER_NAME, QString()},
            {SettingsData::REMEMBER_ME, false}
        };
    };
}

Q_DECLARE_METATYPE(Settings::FileStorage)

#endif // SETTINGSMANAGER_H
