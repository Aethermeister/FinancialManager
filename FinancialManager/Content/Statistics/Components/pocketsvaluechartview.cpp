#include "pocketsvaluechartview.h"

namespace Content::Statistics::Components
{
    PocketsValueChartView::PocketsValueChartView(std::shared_ptr<User> user, QWidget *parent) : ChartViewBase(user, parent)
    {
    }

    PocketsValueChartView::~PocketsValueChartView()
    {
    }

    void PocketsValueChartView::initializeSeries()
    {
        //Create the Pocket value and usage QPieSeries and store them in the vector
        m_pocketValueSeries = createPocketValueSeries();
        m_pocketUsageSeries = createPocketUsageSeries();

        m_chartSeries.push_back(m_pocketValueSeries);
        m_chartSeries.push_back(m_pocketUsageSeries);

        //Show the default series in the chart
        showSelectedSeries();
    }

    void PocketsValueChartView::initializeChartAdjustingWidgets()
    {
        //Create the chart modifier widgets for the value display and Pocket type display
        m_chartAdjustingWidgets.push_back(createSliceValueDisplayModifierWidget());
        m_chartAdjustingWidgets.push_back(createPocketTypeDisplayModifierWidget());

        //Invert the vector so the contained widgets will appear in the correct order
        std::reverse(m_chartAdjustingWidgets.begin(), m_chartAdjustingWidgets.end());
    }

    QPieSeries *PocketsValueChartView::createPocketValueSeries() const
    {
        //Get the user's pockets list and initialize a QPieSeries with its values
        const auto& pockets = m_user->pockets();
        QPieSeries* valueSeries = new QPieSeries();

        //Iterate over the retrieved pockets
        for(const auto& pocket : pockets)
        {
            //Create slice and set its properties according to the given Pocket value data
            auto slice = valueSeries->append("", pocket.value());
            slice->setProperty("name", pocket.name());
            slice->setProperty("sliceValue", pocket.value());
            slice->setExploded();
        }

        return valueSeries;
    }

    QPieSeries *PocketsValueChartView::createPocketUsageSeries() const
    {
        //Get the user's pockets list and initialize a QPieSeries with its usage values
        const auto& pockets = m_user->pockets();
        QPieSeries* usageSeries = new QPieSeries();

        //Iterate over the retrieved pockets
        for(const auto& pocket : pockets)
        {
            //Create slice and set its properties according to the given Pocket usage data
            auto slice = usageSeries->append("", pocket.recordsCount());
            slice->setProperty("name", pocket.name());
            slice->setProperty("sliceValue", pocket.recordsCount());
            slice->setExploded();
        }

        return usageSeries;
    }

    QWidget *PocketsValueChartView::createSliceValueDisplayModifierWidget() const
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
        connect(valueButton, &QPushButton::clicked, this, &PocketsValueChartView::slot_changeSliceDisplayMode);
        sliceModifierLayout->addWidget(valueButton);

        QPushButton* percentageButton = new QPushButton("Percentage", sliceModifierWidget);
        percentageButton->setProperty("displayMode", SliceDisplayMode::PERCENTAGE);
        percentageButton->setAutoExclusive(true);
        percentageButton->setCheckable(true);
        percentageButton->setChecked(false);
        connect(percentageButton, &QPushButton::clicked, this, &PocketsValueChartView::slot_changeSliceDisplayMode);
        sliceModifierLayout->addWidget(percentageButton);

        return sliceModifierWidget;
    }

    QWidget *PocketsValueChartView::createPocketTypeDisplayModifierWidget() const
    {
        //Create a container widget which will hold the modifier widgets
        QWidget* pocketModifierWidget = new QWidget();
        QHBoxLayout* pocketModifierLayout = new QHBoxLayout(pocketModifierWidget);
        pocketModifierLayout->setMargin(0);

        //Create two exclusive buttons
        //One for the Pocket value one for the Pocket usage display
        QPushButton* pocketValueButton = new QPushButton("Pocket Value", pocketModifierWidget);
        pocketValueButton->setProperty("pocketType", PocketTypeDisplay::POCKET_VALUE);
        pocketValueButton->setAutoExclusive(true);
        pocketValueButton->setCheckable(true);
        pocketValueButton->setChecked(true);
        connect(pocketValueButton, &QPushButton::clicked, this, &PocketsValueChartView::slot_changePocketTypeDisplay);
        pocketModifierLayout->addWidget(pocketValueButton);

        QPushButton* pocketUsageButton = new QPushButton("Pocket Usage", pocketModifierWidget);
        pocketUsageButton->setProperty("pocketType", PocketTypeDisplay::POCKET_USAGE);
        pocketUsageButton->setAutoExclusive(true);
        pocketUsageButton->setCheckable(true);
        pocketUsageButton->setChecked(false);
        connect(pocketUsageButton, &QPushButton::clicked, this, &PocketsValueChartView::slot_changePocketTypeDisplay);
        pocketModifierLayout->addWidget(pocketUsageButton);

        return pocketModifierWidget;
    }

    void PocketsValueChartView::showSelectedSeries()
    {
        //Remove the currently attached series from teh chart
        if(auto attachedSeries = m_chart->series(); !attachedSeries.empty())
        {
            for(const auto series : attachedSeries)
            {
                m_chart->removeSeries(series);
            }

            attachedSeries.clear();
        }

        QPieSeries* newSeries = nullptr;
        QString valuePostfix;

        //According to the currently set Pocket Type Display value
        //set the newly used series and modify the displayed information (Slice label postfix and title)
        if(m_pocketTypeDisplay == PocketTypeDisplay::POCKET_VALUE)
        {
            newSeries = m_pocketValueSeries;
            valuePostfix = "HUF";
            m_chart->setTitle("Pockets Value Chart");
        }
        else if(m_pocketTypeDisplay == PocketTypeDisplay::POCKET_USAGE)
        {
            newSeries = m_pocketUsageSeries;
            valuePostfix = "record(s)";
            m_chart->setTitle("Pockets Usage Chart");
        }
        else
        {
            return;
        }

        //Iterate over the series' slices and set their display property
        for(auto& slice : newSeries->slices())
        {
            QString sliceLabel = "%0 | %1";
            const auto sliceName = slice->property("name").toString();

            //According to the currently set Slice Display Mode set the displayed slice information with the correct data
            QString displayedValue;
            if(m_sliceDisplayMode == SliceDisplayMode::VALUE)
            {
                displayedValue = QString::number(slice->property("sliceValue").toInt()) + " " + valuePostfix;
            }
            else if(m_sliceDisplayMode == SliceDisplayMode::PERCENTAGE)
            {
                displayedValue = QString::number(slice->percentage() * 100, 'f', 2) + "%";
            }

            slice->setLabel(sliceLabel.arg(sliceName, displayedValue));
        }

        //Show the labels of the series and attach it to the chart
        newSeries->setLabelsVisible();
        m_chart->addSeries(newSeries);
    }

    void PocketsValueChartView::slot_changeSliceDisplayMode()
    {
        //Get the sender buttons Slice Display Mode property data
        const auto senderButton = qobject_cast<QPushButton*>(sender());
        const auto newSliceDisplayMode = static_cast<SliceDisplayMode>(senderButton->property("displayMode").toInt());

        //If the new display mode differs from the currently used
        //set the new display mode and update the visible series
        if(m_sliceDisplayMode != newSliceDisplayMode)
        {
            m_sliceDisplayMode = newSliceDisplayMode;
            showSelectedSeries();
        }
    }

    void PocketsValueChartView::slot_changePocketTypeDisplay()
    {
        //Get the sender buttons Pocket Type Display property data
        const auto senderButton = qobject_cast<QPushButton*>(sender());
        const auto newPocketTypeDisplay = static_cast<PocketTypeDisplay>(senderButton->property("pocketType").toInt());

        //If the new pocket type differs from the currently used
        //set the new pocket type and update the visible series
        if(m_pocketTypeDisplay != newPocketTypeDisplay)
        {
            m_pocketTypeDisplay = newPocketTypeDisplay;
            showSelectedSeries();
        }
    }
}
