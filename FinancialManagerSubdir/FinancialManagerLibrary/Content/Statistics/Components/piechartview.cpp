#include "piechartview.h"

namespace Content::Statistics::Components
{
    PieChartView::PieChartView(std::shared_ptr<User> user, QWidget *parent) : ChartViewBase(user, parent)
    {

    }

    QWidget *PieChartView::createSliceValueDisplayModifierWidget() const
    {
        //Create a container widget which will hold the modifier widgets
        QWidget* sliceModifierWidget = new QWidget();
        QHBoxLayout* sliceModifierLayout = new QHBoxLayout(sliceModifierWidget);
        sliceModifierLayout->setMargin(0);
        sliceModifierLayout->setContentsMargins(0,0,25,0); //Set the right margin so it will be appear separated from the other modifier widget group

        //Create two exclusive buttons
        //One for the value one for the percentage display
        QPushButton* valueButton = new QPushButton("Value", sliceModifierWidget);
        valueButton->setProperty("displayMode", SliceDisplayMode::VALUE);
        valueButton->setAutoExclusive(true);
        valueButton->setCheckable(true);
        valueButton->setChecked(true);
        connect(valueButton, &QPushButton::clicked, this, &PieChartView::slot_changeSliceDisplayMode);
        sliceModifierLayout->addWidget(valueButton);

        QPushButton* percentageButton = new QPushButton("Percentage", sliceModifierWidget);
        percentageButton->setProperty("displayMode", SliceDisplayMode::PERCENTAGE);
        percentageButton->setAutoExclusive(true);
        percentageButton->setCheckable(true);
        percentageButton->setChecked(false);
        connect(percentageButton, &QPushButton::clicked, this, &PieChartView::slot_changeSliceDisplayMode);
        sliceModifierLayout->addWidget(percentageButton);

        return sliceModifierWidget;
    }

    void PieChartView::slot_changeSliceDisplayMode()
    {
        //Get the sender buttons Slice Display Mode property data
        const auto senderButton = qobject_cast<QPushButton*>(sender());
        const auto newSliceDisplayMode = static_cast<SliceDisplayMode>(senderButton->property("displayMode").toInt());

        //If the new display mode differs from the currently used
        //set the new display mode and update the visible series
        if(m_sliceDisplayMode != newSliceDisplayMode)
        {
            m_sliceDisplayMode = newSliceDisplayMode;
            showSelectedPieSeries();
        }
    }
}
