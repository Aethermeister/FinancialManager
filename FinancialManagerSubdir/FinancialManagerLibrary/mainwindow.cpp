#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "user.h"

#include "Core/defines.h"
#include "Authentication/authenticationwidget.h"
#include "Content/contentwidget.h"
#include "Settings/settingswindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Always show the AuthenticationWidget first
    showAuthenticationWidget();

    connect(ui->m_settings_btn, &QPushButton::clicked, this, &MainWindow::slot_showSettingsWindow);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QWidget *MainWindow::containerWidget()
{
    return ui->m_container_widget;
}

QPushButton *MainWindow::profilButton()
{
    return ui->m_profile_btn;
}

QLabel *MainWindow::titleLabel()
{
    return ui->m_title_lbl;
}

void MainWindow::showAuthenticationWidget()
{
    ui->m_profile_btn->setVisible(false);

    //Delete the current widget from the container widget
    deleteActiveContentWidget<QWidget*>(ui->m_container_widget, ui->m_container_layout);

    //Create a new AuthenticationWidget and add it to the container widget
    Authentication::AuthenticationWidget* authenticationWidget = new Authentication::AuthenticationWidget(ui->m_container_widget);
    ui->m_container_layout->addWidget(authenticationWidget);

    ui->m_title_lbl->setText(QString("Aether's Financial Manager"));

    //Connect the corresponding signals and slots
    connect(authenticationWidget, &Authentication::AuthenticationWidget::sig_authenticated, this, &MainWindow::showMainContentWidget);
}

void MainWindow::showMainContentWidget(const QString& username, const QString& password, const QString& id)
{
    ui->m_profile_btn->setVisible(true);

    //Delete the current widget from the container widget
    deleteActiveContentWidget<QWidget*>(ui->m_container_widget, ui->m_container_layout);

    //Create a new ContentWidget and add it to the container widget
    Content::ContentWidget* contentWidget = new Content::ContentWidget(std::make_shared<User>(username, password, id), ui->m_container_widget);
    ui->m_container_layout->addWidget(contentWidget);

    //Show the username in the header widget
    ui->m_title_lbl->setText(QString("Aether's Financial Manager - %0").arg(username));

    connect(ui->m_profile_btn, &QPushButton::clicked, contentWidget, &Content::ContentWidget::slot_showProfileWidget);
    connect(contentWidget, &Content::ContentWidget::sig_logout, this, &MainWindow::showAuthenticationWidget);
}

void MainWindow::slot_showSettingsWindow()
{
    //Create the Settings Window and show it as a model dialog
    Settings::SettingsWindow* settingsWindow = new Settings::SettingsWindow();
    settingsWindow->exec();
}

