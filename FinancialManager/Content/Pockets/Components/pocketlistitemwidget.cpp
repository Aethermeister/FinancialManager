#include "pocketlistitemwidget.h"
#include "ui_pocketlistitemwidget.h"
#include "Core/widgetdefines.h"

#include <QPixmap>

namespace Content::Pockets::Component
{
    PocketListItemWidget::PocketListItemWidget(const Pocket &pocket, QWidget *parent) :
        QWidget(parent),
        ui(new Ui::PocketListItemWidget),
        m_pocket(pocket)
    {
        ui->setupUi(this);

        initializeUi();
    }

    PocketListItemWidget::~PocketListItemWidget()
    {
        delete ui;
    }

    void PocketListItemWidget::initializeUi()
    {
        //Set the correct type indicator image according to the set PocketType
        QPixmap pixmap = QPixmap();
        if(m_pocket.type() == Content::Pockets::PocketType::CASH)
        {
            pixmap.load("://Images/cash.png");
        }
        else if(m_pocket.type() == Content::Pockets::PocketType::CARD)
        {
            pixmap.load("://Images/card.png");
        }
        ui->m_pocketImage_lbl->setPixmap(pixmap);

        //Set the name and value of the Pocket list item
        ui->m_pocketName_lbl->setText(m_pocket.name());
        setLabelNegativeState(ui->m_value_lbl, m_pocket.value());
    }
}
