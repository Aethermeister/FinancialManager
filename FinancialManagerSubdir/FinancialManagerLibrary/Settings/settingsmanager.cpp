#include "settingsmanager.h"

namespace Settings
{
    SettingsManager::SettingsManager()
    {
        initializeSettingsData();
    }

    SettingsManager* SettingsManager::m_instance = nullptr;

    SettingsManager *SettingsManager::instance()
    {
        //If the instance was not called/used yet create a new one
        if(!m_instance)
        {
            m_instance = new SettingsManager;
        }

        return m_instance;
    }

    void SettingsManager::setData(const SettingsData key, const QVariant &value)
    {
        QSettings settings;
        settings.setValue(QString::number(key), value);
    }

    void SettingsManager::setData(const SettingsData key, const QString &value)
    {
        const auto encodedSettingsData = encodeData(value);

        QSettings settings;
        settings.setValue(QString::number(key), encodedSettingsData);
    }

    void SettingsManager::initializeSettingsData()
    {
        QSettings settings;

        //Iterate over the default settings key value pairs and check whether the given key exists in the registry
        //Save the default value if the key is missing
        for(auto it = DefaultSettingsValues.begin(); it != DefaultSettingsValues.end(); ++it)
        {
            if(!settings.contains(QString::number(it.key())))
            {
                settings.setValue(QString::number(it.key()), it.value());
            }
        }
    }

    void SettingsManager::resetSettingsData()
    {
        QSettings settings;

        //Iterate over the default settings key value pairs
        //and overwrite the existing data with the default
        for(auto it = DefaultSettingsValues.begin(); it != DefaultSettingsValues.end(); ++it)
        {
            settings.setValue(QString::number(it.key()), it.value());
        }
    }
}
