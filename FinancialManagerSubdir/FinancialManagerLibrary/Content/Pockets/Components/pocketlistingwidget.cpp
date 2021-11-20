#include "pocketlistingwidget.h"
#include "pocketlistitemwidget.h"
#include "ui_pocketlistingwidget.h"

namespace Content::Pockets::Component
{
    PocketListingWidget::PocketListingWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::PocketListingWidget)
    {
        ui->setupUi(this);
    }

    PocketListingWidget::~PocketListingWidget()
    {
        delete ui;
    }

    void PocketListingWidget::initialize(std::shared_ptr<User> user)
    {
        //Get the already existing and listed PocketListItemWidgets
        //and delete them
        const auto& pocketItems = findChildren<Component::PocketListItemWidget*>();
        for(const auto& pocketItem : pocketItems)
        {
            ui->m_pocketListing_layout->removeWidget(pocketItem);
            pocketItem->setParent(nullptr);
            pocketItem->deleteLater();
        }

        //If the PocketListItemWidgets were previously listed than the spacer item is NOT nullptr
        //Delete the spacer item so the list area is totally empty
        if(m_listSpacer)
        {
            ui->m_pocketListing_layout->removeItem(m_listSpacer);
            delete m_listSpacer;
        }

        //Get the pockets and create a PocketListItemWidget for each
        const auto& pockets = user->pockets();
        for(const auto& pocket : pockets)
        {
            Component::PocketListItemWidget* pocketListItem = new Component::PocketListItemWidget(user, pocket, this);
            ui->m_pocketListing_layout->addWidget(pocketListItem);
        }

        //Create a new spacer item which correctly aligns the PocketListItemWidgets
        m_listSpacer = new QSpacerItem(10,10, QSizePolicy::Expanding, QSizePolicy::Expanding);
        ui->m_pocketListing_layout->addItem(m_listSpacer);
    }
}
