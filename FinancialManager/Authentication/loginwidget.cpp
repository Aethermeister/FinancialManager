#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "Core/defines.h"

#include <QTimer>

namespace Authentication
{
    LoginWidget::LoginWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::LoginWidget)
    {
        ui->setupUi(this);

        //Set the initial state of the widget
        initializeUi();
        initializeConnections();
    }

    LoginWidget::~LoginWidget()
    {
        delete ui;
    }

    void LoginWidget::initializeUi()
    {
        //Get the REMEMBER_ME settings value and initialize the ui according to this value
        const auto rememberMe = Settings::SettingsManager::instance()->data<bool>(Settings::SettingsData::REMEMBER_ME);
        ui->m_rememberMe_checkBox->setChecked(rememberMe);

        //If the REMEMBER_ME checkbox was previously checked get the data of the last user
        if(rememberMe)
        {
            //Get the last username stored as settings
            //and get the corresponding password using the username
            QString password = QString();
            const auto lastUsername = Settings::SettingsManager::instance()->data<QString>(Settings::SettingsData::LAST_USER_NAME);
            const auto isLastUsernameValid = checkForExistingUsername(lastUsername, &password);

            //Set the username and password QLineEdits if valid username and password was retrieved
            if(isLastUsernameValid)
            {
                ui->m_username_lineEdit->setText(lastUsername);
                ui->m_password_lineEdit->setText(password);
            }
        }

        ui->m_information_lbl->setVisible(false);

        //Call the base information QLabel setter
        //so the base class will be able to use the QLabel
        setInformationLabel(ui->m_information_lbl);
    }

    void LoginWidget::initializeConnections() const
    {
        connect(ui->m_login_btn, &QPushButton::clicked, this, &LoginWidget::slot_login);
        connect(ui->m_createAccount_btn, &QPushButton::clicked, this, &LoginWidget::sig_createAccount);

        //Create connection for the 'remember me' QCheckBox when clicked
        connect(ui->m_rememberMe_checkBox, &QCheckBox::clicked, [=](bool checked)
        {
            //Set the REMEMBER_ME settings data according to the checked state
            Settings::SettingsManager::instance()->setData(Settings::SettingsData::REMEMBER_ME, checked);

            //If the QCheckBox has been unchecked than remove the previously stored LAST_USER_NAME value from the settings
            if(!checked)
            {
                Settings::SettingsManager::instance()->setData(Settings::SettingsData::LAST_USER_NAME, QString());
            }
        });
    }

    void LoginWidget::slot_login()
    {
        //Set the ui to the default state so there is no error indication
        ui->m_information_lbl->setVisible(false);

        setLineEditErrorState(ui->m_username_lineEdit, false);
        setLineEditErrorState(ui->m_password_lineEdit, false);

        const auto username = ui->m_username_lineEdit->text();
        const auto password = ui->m_password_lineEdit->text();

        //Check the given username and show error if it is not inputted
        if(username.trimmed().size() == 0)
        {
            setLineEditErrorState(ui->m_username_lineEdit, true);

            showInformation(ui->m_information_lbl, "Username is empty");

            return;
        }

        //Check the given password and show error if it is not inputted
        if(password.trimmed().size() == 0)
        {
            setLineEditErrorState(ui->m_password_lineEdit, true);

            showInformation(ui->m_information_lbl, "Password is empty");

            return;
        }

        QString id = QString();
        //Check whether the given user exists
        if(!checkForExistingUsername(username, password, &id))
        {
            setLineEditErrorState(ui->m_username_lineEdit, true);
            setLineEditErrorState(ui->m_password_lineEdit, true);

            showInformation(ui->m_information_lbl, "Incorrect username and/or password");

            return;
        }

        //Emit the signal which indicates that the user is authorized
        emit sig_loggedIn(username, password, id);

        //During the login check whether the 'remember me' QCheckBox is checked
        //and store this username if it is checked
        if(ui->m_rememberMe_checkBox->isChecked())
        {
            Settings::SettingsManager::instance()->setData(Settings::SettingsData::LAST_USER_NAME, username);
        }
    }
}
