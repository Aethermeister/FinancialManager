#include "profilewidget.h"
#include "ui_profilewidget.h"
#include "Core/defines.h"
#include "Notification/notificationwidget.h"

namespace Content
{
    ProfileWidget::ProfileWidget(std::shared_ptr<User> user, QWidget *parent) :
        QWidget(parent),
        ui(new Ui::ProfileWidget),
        m_user(user)
    {
        ui->setupUi(this);

        initializeUi();
        initializeConnections();
    }

    ProfileWidget::~ProfileWidget()
    {
        delete ui;
    }

    void ProfileWidget::initializeConnections()
    {
        connect(ui->m_logout_btn, &QPushButton::clicked, this, &ProfileWidget::sig_requestLogout);
        connect(ui->m_changePassword_btn, &QPushButton::clicked, this, &ProfileWidget::slot_changePassword);
        connect(ui->m_deleteAccount_btn, &QPushButton::clicked, this, &ProfileWidget::slot_markUserForDeletion);
        connect(ui->m_cancelDeletion_btn, &QPushButton::clicked, this, &ProfileWidget::slot_cancelDeletion);
    }

    void ProfileWidget::initializeUi()
    {
        //Show the user informations
        ui->m_username_lbl->setText(m_user->username());
        ui->m_id_lbl->setText(m_user->id());
        ui->m_passwordInformation_lbl->setVisible(false);

        //Check whether the account is already scheduled for deletion
        //and show the deletion related ui elements accordingly
        if(m_user->isMarkedForDeletion())
        {
            ui->m_deleteAccount_btn->setVisible(false);
            ui->m_cancelDeletion_btn->setVisible(true);

            ui->m_deletionInformation_lbl->setVisible(true);
            showInformation(ui->m_deletionInformation_lbl, deletionMessage);
        }
        else
        {
            ui->m_deleteAccount_btn->setVisible(true);
            ui->m_cancelDeletion_btn->setVisible(false);

            ui->m_deletionInformation_lbl->setVisible(false);
        }
    }

    void ProfileWidget::slot_changePassword()
    {
        //Reset the error indicators
        ui->m_passwordInformation_lbl->setVisible(false);

        setWidgetErrorState(ui->m_oldPassword_lineEdit, false);
        setWidgetErrorState(ui->m_newPassword_lineEdit, false);
        setWidgetErrorState(ui->m_verifyNewPassword_lineEdit, false);

        //Get the passwords from the ui and run several validations
        const auto oldPassword = ui->m_oldPassword_lineEdit->text();
        const auto newPassword = ui->m_newPassword_lineEdit->text();
        const auto verifyNewPassword = ui->m_verifyNewPassword_lineEdit->text();

        const auto oldBase64Password = encodeData(oldPassword);
        const auto newBase64Password = encodeData(newPassword);

        //Check whether the user has given the correct old password
        //and show error if they are not the same
        if(oldBase64Password != m_user->password())
        {
            setWidgetErrorState(ui->m_oldPassword_lineEdit, true);

            showInformation(ui->m_passwordInformation_lbl, "Incorrect old password");

            return;
        }

        //Check whether the user given password is the same with the old password
        //and show error if they are the same
        if(newBase64Password == m_user->password())
        {
            setWidgetErrorState(ui->m_newPassword_lineEdit, true);

            showInformation(ui->m_passwordInformation_lbl, "New password cannot be the same as the old one");

            return;
        }

        //Check the given new password and show error
        //if it does not meet the minimum requirements
        const QRegularExpression re(PASSWORDREGEX);
        const QRegularExpressionMatch match = re.match(newPassword.trimmed());
        if(!match.hasMatch())
        {
            setWidgetErrorState(ui->m_newPassword_lineEdit, true);
            showInformation(ui->m_passwordInformation_lbl, "Password has to contain 8-32 characters.\nIt has to contain lower and uppercase letters and digits");
            return;
        }

        //Check whether the two new passwords are a match
        //and show error it they differ
        if(newPassword != verifyNewPassword)
        {
            setWidgetErrorState(ui->m_newPassword_lineEdit, true);
            setWidgetErrorState(ui->m_verifyNewPassword_lineEdit, true);

            showInformation(ui->m_passwordInformation_lbl, "New passwords do not match");

            return;
        }

        //Get the content of the users JSON file
        //and check whether the parameter given username exists
        const auto usersDocument = readJSONFile(USERSFILE);
        auto usersObject = usersDocument.object();

        //Modify the password in the JSON object
        auto userObject = usersObject.value(m_user->username()).toObject();
        userObject["password"] = newBase64Password;
        usersObject[m_user->username()] = userObject;

        //Save the modified JSON content to the users JSON file
        const auto modifiedUsersDocument = QJsonDocument(usersObject);
        writeJSONFile(USERSFILE, modifiedUsersDocument);
        m_user->setPassword(newBase64Password);

        //Reset the password change related ui
        ui->m_oldPassword_lineEdit->clear();
        ui->m_newPassword_lineEdit->clear();
        ui->m_verifyNewPassword_lineEdit->clear();

        //Show notification indicating that the password has been changed successfully
        Notification::NotificationWidget* passwordChangedNotification = new Notification::NotificationWidget("Password has been changed", parentWidget()->parentWidget());
        passwordChangedNotification->show();
    }

    void ProfileWidget::slot_markUserForDeletion()
    {
        //Replace the Delete Account with the Cancel Deletion QPushButton
        ui->m_deleteAccount_btn->setVisible(false);
        ui->m_cancelDeletion_btn->setVisible(true);

        m_user->setMarkedForDeletion(true);

        //Show deletion information on the ui and show a notification as well
        showInformation(ui->m_deletionInformation_lbl, deletionMessage);

        Notification::NotificationWidget* deletionNotification = new Notification::NotificationWidget("Account has been marked for deletion", parentWidget()->parentWidget());
        deletionNotification->show();
    }

    void ProfileWidget::slot_cancelDeletion()
    {
        //Replace the Cancel Deletion with the Delete Account QPushButton
        ui->m_deleteAccount_btn->setVisible(true);
        ui->m_cancelDeletion_btn->setVisible(false);

        m_user->setMarkedForDeletion(false);

        //Hide the deletion information QLabel and show notification to notify the user about the deletion cancellation
        ui->m_deletionInformation_lbl->setVisible(false);

        Notification::NotificationWidget* deletionNotification = new Notification::NotificationWidget("Account deletion has been canceled", parentWidget()->parentWidget());
        deletionNotification->show();
    }
}
