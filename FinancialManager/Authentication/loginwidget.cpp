#include "loginwidget.h"
#include "ui_loginwidget.h"

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
        ui->m_information_lbl->setVisible(false);

        //Call the base information QLabel setter
        //so the base class will be able to use the QLabel
        setInformationLabel(ui->m_information_lbl);
    }

    void LoginWidget::initializeConnections() const
    {
        connect(ui->m_login_btn, &QPushButton::clicked, this, &LoginWidget::slot_login);
        connect(ui->m_createAccount_btn, &QPushButton::clicked, this, &LoginWidget::sig_createAccount);
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

            showErrorInformation("Username is empty");

            return;
        }

        //Check the given password and show error if it is not inputted
        if(password.trimmed().size() == 0)
        {
            setLineEditErrorState(ui->m_password_lineEdit, true);

            showErrorInformation("Password is empty");

            return;
        }

        //Check whether the given user exists
        if(!checkForExistingUsername(username, password))
        {
            setLineEditErrorState(ui->m_username_lineEdit, true);
            setLineEditErrorState(ui->m_password_lineEdit, true);

            showErrorInformation("Incorrect username and/or password");

            return;
        }

        //Emit the signal wich indicated that the user is authorized
        emit sig_loggedIn();
    }
}
