#include "signupwidget.h"
#include "ui_signupwidget.h"
#include "Core/defines.h"

#include <QStyle>
#include <QUuid>
#include <QDebug>
#include <QFileDialog>

namespace Authentication
{
    SignUpWidget::SignUpWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::SignUpWidget)
    {
        ui->setupUi(this);

        //Set the initial state of the widget
        initializeUi();
        initializeConnections();
    }

    SignUpWidget::~SignUpWidget()
    {
        delete ui;
    }

    void SignUpWidget::initializeUi()
    {
        ui->m_information_lbl->setVisible(false);

        //Call the base information QLabel setter
        //so the base class will be able to use the QLabel
        setInformationLabel(ui->m_information_lbl);
    }

    void SignUpWidget::initializeConnections() const
    {
        connect(ui->m_signUp_btn, &QPushButton::clicked, this, &SignUpWidget::slot_signUp);
        connect(ui->m_backToLogin_btn, &QPushButton::clicked, this, &SignUpWidget::sig_backToLogin);
    }

    void SignUpWidget::slot_signUp()
    {
        //Set the ui to the default state so there is no error indication
        ui->m_information_lbl->setVisible(false);

        setLineEditErrorState(ui->m_username_lineEdit, false);
        setLineEditErrorState(ui->m_password_lineEdit, false);
        setLineEditErrorState(ui->m_verifyPassword_lineEdit, false);

        const auto username = ui->m_username_lineEdit->text();
        const auto password = ui->m_password_lineEdit->text();
        const auto verifiedPassword = ui->m_verifyPassword_lineEdit->text();

        //Check the given username and show error if it is not inputted
        if(username.trimmed().size() == 0)
        {
            setLineEditErrorState(ui->m_username_lineEdit, true);

            showInformation(ui->m_information_lbl, "Username cannot be empty");

            return;
        }

        //Check the given password and show error
        //if it does not meet the minimum requirement
        if(password.trimmed().size() < 6)
        {
            setLineEditErrorState(ui->m_password_lineEdit, true);

            showInformation(ui->m_information_lbl, "Password has to contain at least 6 characters");

            return;
        }

        //Check whether the two passwords are a match
        //and show error it they differ
        if(password != verifiedPassword)
        {
            setLineEditErrorState(ui->m_password_lineEdit, true);
            setLineEditErrorState(ui->m_verifyPassword_lineEdit, true);

            showInformation(ui->m_information_lbl, "Passwords do not match");

            return;
        }

        //Check whether there is an existing user with the given username
        //and show error if there is such user
        if(checkForExistingUsername(username))
        {
            setLineEditErrorState(ui->m_username_lineEdit, true);

            showInformation(ui->m_information_lbl, "Username is already used");

            return;
        }

        //Create unique id for the new user
        const auto id = QUuid::createUuid().toString();
        const auto base64Password = encodeData(password);

        //Create a JSON object with id and password elements
        QJsonObject newUserObject
        {
            {"id", id},
            {"password", base64Password}
        };

        //Get the content of the users JSON file
        //and update it with the new user' information
        const auto usersDocument = readJSONFile(USERSFILE);
        auto usersObject = usersDocument.object();
        usersObject[username] = newUserObject;

        //Save the new JSON content to the users JSON file
        const auto newUsersDocument = QJsonDocument(usersObject);
        writeJSONFile(USERSFILE, newUsersDocument);

        //Emit the signal which indicates that the user is signed up and authorized
        emit sig_signedUp(username, base64Password, id);
    }
}
