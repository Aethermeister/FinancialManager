#include "recordsdatachartview.h"

namespace Content::Statistics::Components
{
    RecordsDataChartView::RecordsDataChartView(std::shared_ptr<User> user, QWidget *parent) : PieChartView(user, parent)
    {

    }

    RecordsDataChartView::~RecordsDataChartView()
    {

    }

    void RecordsDataChartView::initializeSeries()
    {
        //Process the records and map them
        //and show the default series
        collectRecordsData();
        showSelectedPieSeries();
    }

    void RecordsDataChartView::initializeChartAdjustingWidgets()
    {
        //Create the chart modifier widgets
        m_chartAdjustingWidgets.push_back(createSliceValueDisplayModifierWidget());
        m_chartAdjustingWidgets.push_back(createRecordsDisplayModeModifierWidgets());
        m_chartAdjustingWidgets.push_back(createRecordsDisplayTypeModifierWidgets());
        m_chartAdjustingWidgets.push_back(createPocketFilterButton());

        //Invert the vector so the contained widgets will appear in the correct order
        std::reverse(m_chartAdjustingWidgets.begin(), m_chartAdjustingWidgets.end());
    }

    void RecordsDataChartView::showSelectedPieSeries()
    {
        //Remove and delete the attached series
        //Only one QPieSeries is initialized at the same time so deleteAllSeries is safe
        m_chart->removeAllSeries();

        //Getthe summarized map for the currently set display mode/type
        const auto& summarizedRecordsData = summarizeRecordsData();

        QPieSeries* series = new QPieSeries();

        //Iterate over the summarized map and create a slice for each entry
        for(const auto& [item, value] : summarizedRecordsData)
        {
            auto slice = series->append("", value);
            slice->setProperty("name", item);
            slice->setProperty("sliceValue", value);
            slice->setExploded();
        }

        //Adjust the slice label according to the current slice display mode
        adjustSeriesDisplay(series);

        //Show the slice labels and add the new series to the chart
        series->setLabelsVisible();
        m_chart->addSeries(series);
    }

    void RecordsDataChartView::collectRecordsData()
    {
        //Iterate over the records and map their values
        const auto& records = m_user->records();
        for(const auto& record : records)
        {
            const auto& pocketName = record.pocketName();

            //Map the items value and count of the Records to the given Pocket
            m_recordsItemsValueMap[pocketName][record.item()] += record.value();
            m_recordsItemsCountMap[pocketName][record.item()] += 1;

            //Map the locations value and count of the Records to the given Pocket
            m_recordsLocationsValueMap[pocketName][record.location()] += record.value();
            m_recordsLocationsCountMap[pocketName][record.location()] += 1;
        }
    }

    QPushButton *RecordsDataChartView::createPocketFilterButton()
    {
        //Create a button with a menu attached to it which lists the available Pockets
        QPushButton* filterButton = new QPushButton("Pocket Filter");
        QMenu* filterMenu = new QMenu(filterButton);

        //Iterate over the Pockets
        //and create a checkable action for each
        const auto& pockets = m_user->pockets();
        for(const auto& pocket : pockets)
        {
            const auto& pocketName = pocket.name();
            QAction* filterAction = new QAction(pocketName, filterMenu);
            filterAction->setCheckable(true);
            filterAction->setChecked(true); //As default the Pockets are checked so there is no filter
            connect(filterAction, &QAction::toggled, this, [=](bool checked)
            {
                //If the action is toggled change the pocket filter list according to the check state
                //and show the updated series
                if(checked)
                {
                    m_pocketFilter.removeOne(pocketName);
                }
                else
                {
                    m_pocketFilter.append(pocketName);
                }

                showSelectedPieSeries();
            });

            filterMenu->addAction(filterAction);
        }

        filterButton->setMenu(filterMenu);

        return filterButton;
    }

    QWidget *RecordsDataChartView::createRecordsDisplayModeModifierWidgets() const
    {
        //Create a container widget which will hold the modifier widgets
        QWidget* recordsDisplayModeModifierWidget = new QWidget();
        QHBoxLayout* recordsDisplayModeModifierLayout = new QHBoxLayout(recordsDisplayModeModifierWidget);
        recordsDisplayModeModifierLayout->setMargin(0);
        recordsDisplayModeModifierLayout->setContentsMargins(0,0,25,0); //Set the right margin so it will be appear separated from the other modifier widget group

        //Create two exclusive buttons
        //One for the Pocket value one for the Pocket usage display
        QPushButton* recordsValueButton = new QPushButton("Records Value", recordsDisplayModeModifierWidget);
        recordsValueButton->setProperty("recordsDisplayMode", RecordsDataDisplayMode::RECORDS_VALUE);
        recordsValueButton->setAutoExclusive(true);
        recordsValueButton->setCheckable(true);
        recordsValueButton->setChecked(true);
        connect(recordsValueButton, &QPushButton::clicked, this, &RecordsDataChartView::slot_changeRecordsDisplayMode);
        recordsDisplayModeModifierLayout->addWidget(recordsValueButton);

        QPushButton* recordsCountButton = new QPushButton("Records Count", recordsDisplayModeModifierWidget);
        recordsCountButton->setProperty("recordsDisplayMode", RecordsDataDisplayMode::RECORDS_COUNT);
        recordsCountButton->setAutoExclusive(true);
        recordsCountButton->setCheckable(true);
        recordsCountButton->setChecked(false);
        connect(recordsCountButton, &QPushButton::clicked, this, &RecordsDataChartView::slot_changeRecordsDisplayMode);
        recordsDisplayModeModifierLayout->addWidget(recordsCountButton);

        return recordsDisplayModeModifierWidget;
    }

    QWidget *RecordsDataChartView::createRecordsDisplayTypeModifierWidgets() const
    {
        //Create a container widget which will hold the modifier widgets
        QWidget* recordsDisplayTypeModifierWidget = new QWidget();
        QHBoxLayout* recordsDisplayTypeModifierLayout = new QHBoxLayout(recordsDisplayTypeModifierWidget);
        recordsDisplayTypeModifierLayout->setMargin(0);
        recordsDisplayTypeModifierLayout->setContentsMargins(0,0,25,0); //Set the right margin so it will be appear separated from the other modifier widget group

        //Create two exclusive buttons
        //One for the Pocket value one for the Pocket usage display
        QPushButton* recordsItemsButton = new QPushButton("Items", recordsDisplayTypeModifierWidget);
        recordsItemsButton->setProperty("recordsDisplayType", RecordsDataDisplayType::ITEM);
        recordsItemsButton->setAutoExclusive(true);
        recordsItemsButton->setCheckable(true);
        recordsItemsButton->setChecked(true);
        connect(recordsItemsButton, &QPushButton::clicked, this, &RecordsDataChartView::slot_changeRecordsDisplayType);
        recordsDisplayTypeModifierLayout->addWidget(recordsItemsButton);

        QPushButton* recordsLocationsButton = new QPushButton("Locations", recordsDisplayTypeModifierWidget);
        recordsLocationsButton->setProperty("recordsDisplayType", RecordsDataDisplayType::LOCATION);
        recordsLocationsButton->setAutoExclusive(true);
        recordsLocationsButton->setCheckable(true);
        recordsLocationsButton->setChecked(false);
        connect(recordsLocationsButton, &QPushButton::clicked, this, &RecordsDataChartView::slot_changeRecordsDisplayType);
        recordsDisplayTypeModifierLayout->addWidget(recordsLocationsButton);

        return recordsDisplayTypeModifierWidget;
    }

    void RecordsDataChartView::adjustSeriesDisplay(QPieSeries *series)
    {
        QString valuePostfix;

        //According to the currently set Records Data Display Mode value
        //set the newly used series and modify the displayed information (Slice label postfix and title)
        if(m_recordsDataDisplayMode == RecordsDataDisplayMode::RECORDS_VALUE)
        {
            valuePostfix = "HUF";
            m_chart->setTitle("Records Value Chart");
        }
        else if(m_recordsDataDisplayMode == RecordsDataDisplayMode::RECORDS_COUNT)
        {
            valuePostfix = "record(s)";
            m_chart->setTitle("Records Count Chart");
        }
        else
        {
            return;
        }

        //Iterate over the series' slices and set their display property
        for(auto& slice : series->slices())
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
    }

    std::unordered_map<QString, int> RecordsDataChartView::summarizeRecordsData()
    {
        std::unordered_map<QString, int> summarizedRecordsData;
        //Get which map should be summarized according to the set display mode/type
        const auto& recordsData = selectedRecordsData();

        //Iterate over the retrieved records data
        for(const auto& [pocketName, valuesMap] : recordsData)
        {
            //Filter out the unwanted Pockets
            if(!m_pocketFilter.contains(pocketName))
            {
                //Store the values in one simple map
                for(const auto& [item, value] : valuesMap)
                {
                    summarizedRecordsData[item] += value;
                }
            }
        }

        return summarizedRecordsData;
    }

    std::unordered_map<QString, std::unordered_map<QString, int>>& RecordsDataChartView::selectedRecordsData()
    {
        //Check the current display mode/type and return the needed map
        if(m_recordsDataDisplayMode == RecordsDataDisplayMode::RECORDS_VALUE)
        {
            if(m_recordsDataDisplayType == RecordsDataDisplayType::ITEM)
            {
                return m_recordsItemsValueMap;
            }
            else if(m_recordsDataDisplayType == RecordsDataDisplayType::LOCATION)
            {
                return m_recordsLocationsValueMap;
            }
        }
        else if(m_recordsDataDisplayMode == RecordsDataDisplayMode::RECORDS_COUNT)
        {
            if(m_recordsDataDisplayType == RecordsDataDisplayType::ITEM)
            {
                return m_recordsItemsCountMap;
            }
            else if(m_recordsDataDisplayType == RecordsDataDisplayType::LOCATION)
            {
                return m_recordsLocationsCountMap;
            }
        }

        //Return the items value map as default
        //Added to terminate warning
        return m_recordsItemsValueMap;
    }

    void RecordsDataChartView::slot_changeRecordsDisplayMode()
    {
        //Get the sender buttons Records Data Display Mode property data
        const auto senderButton = qobject_cast<QPushButton*>(sender());
        const auto newRecordsDisplayMode = static_cast<RecordsDataDisplayMode>(senderButton->property("recordsDisplayMode").toInt());

        //If the new display mode differs from the currently used
        //set the new display mode and update the visible series
        if(m_recordsDataDisplayMode != newRecordsDisplayMode)
        {
            m_recordsDataDisplayMode = newRecordsDisplayMode;
            showSelectedPieSeries();
        }
    }

    void RecordsDataChartView::slot_changeRecordsDisplayType()
    {
        //Get the sender buttons Records Data Display Type property data
        const auto senderButton = qobject_cast<QPushButton*>(sender());
        const auto newRecordsDisplayType = static_cast<RecordsDataDisplayType>(senderButton->property("recordsDisplayType").toInt());

        //If the new display type differs from the currently used
        //set the new display type and update the visible series
        if(m_recordsDataDisplayType != newRecordsDisplayType)
        {
            m_recordsDataDisplayType = newRecordsDisplayType;
            showSelectedPieSeries();
        }
    }
}
