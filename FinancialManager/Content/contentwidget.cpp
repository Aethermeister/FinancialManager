#include "contentwidget.h"
#include "ui_contentwidget.h"
#include "Core/defines.h"
#include "overviewwidget.h"
#include "newrecordwidget.h"

namespace Content
{
    ContentWidget::ContentWidget(std::shared_ptr<User> user, QWidget *parent) :
        QWidget(parent),
        ui(new Ui::ContentWidget),
        m_user(std::move(user))
    {
        ui->setupUi(this);

        //Set the initial state of the widget
        initializeConnections();
        showOverviewWidget();
    }

    ContentWidget::~ContentWidget()
    {
        delete ui;
    }

    void ContentWidget::initializeConnections() const
    {
        connect(ui->m_overview_btn, &QPushButton::clicked, this, &ContentWidget::showOverviewWidget);
        connect(ui->m_newRecord_btn, &QPushButton::clicked, this, &ContentWidget::showNewRecordWidget);

        connect(ui->m_exit_btn, &QPushButton::clicked, &QApplication::quit);
    }

    void ContentWidget::showOverviewWidget()
    {

        //Delete the current widget from the container widget
        deleteActiveContentWidget(ui->m_container_widget, ui->m_container_layout);

        //Create a new OverviewWidget and add it to the container widget
        OverviewWidget* overviewWidget = new OverviewWidget(ui->m_container_widget);
        ui->m_container_layout->addWidget(overviewWidget);
    }

    void ContentWidget::showNewRecordWidget()
    {
        //Delete the current widget from the container widget
        deleteActiveContentWidget(ui->m_container_widget, ui->m_container_layout);

        //Create a new NewRecordWidget and add it to the container widget
        NewRecordWidget* newRecordWidget = new NewRecordWidget(m_user, ui->m_container_widget);
        ui->m_container_layout->addWidget(newRecordWidget);
    }
}
