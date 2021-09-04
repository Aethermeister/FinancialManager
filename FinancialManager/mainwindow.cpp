#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "user.h"

#include "Core/defines.h"
#include "Authentication/authenticationwidget.h"
#include "Content/contentwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Always show the AuthenticationWidget first
    showAuthenticationWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showAuthenticationWidget()
{
    //Delete the current widget from the container widget
    deleteActiveContentWidget(ui->m_container_widget, ui->m_container_layout);

    //Create a new AuthenticationWidget and add it to the container widget
    Authentication::AuthenticationWidget* authenticationWidget = new Authentication::AuthenticationWidget(ui->m_container_widget);
    ui->m_container_layout->addWidget(authenticationWidget);

    //Connect the corresponding signals and slots
    connect(authenticationWidget, &Authentication::AuthenticationWidget::sig_authenticated, this, &MainWindow::showMainContentWidget);

    ui->m_header_widget->setVisible(false);
}

void MainWindow::showMainContentWidget(const QString& username, const QString& password, const QString& id)
{
    //Delete the current widget from the container widget
    deleteActiveContentWidget(ui->m_container_widget, ui->m_container_layout);

    //Create a new ContentWidget and add it to the container widget
    Content::ContentWidget* contentWidget = new Content::ContentWidget(std::make_shared<User>(username, password, id), ui->m_container_widget);
    ui->m_container_layout->addWidget(contentWidget);

    //Show the username in the header widget
    ui->m_title_lbl->setText(QString("Aether's Financial Manager - %0").arg(username));
    ui->m_header_widget->setVisible(true);

    connect(ui->m_profile_btn, &QPushButton::clicked, contentWidget, &Content::ContentWidget::slot_showProfileWidget);
    connect(contentWidget, &Content::ContentWidget::sig_logout, this, &MainWindow::showAuthenticationWidget);
}

