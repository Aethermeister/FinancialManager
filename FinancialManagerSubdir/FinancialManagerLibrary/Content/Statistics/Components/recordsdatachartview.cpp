#include "recordsdatachartview.h"

#include <execution>

namespace Content::Statistics::Components
{
    RecordsDataChartView::RecordsDataChartView(std::shared_ptr<User> user, QWidget *parent) : ChartViewBase(user, parent)
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
        showSelectedBarSeries();
    }

    void RecordsDataChartView::initializeChartAdjustingWidgets()
    {
        //Create the chart modifier widgets
        m_chartAdjustingWidgets.push_back(createRecordsDisplayModeModifierWidgets());
        m_chartAdjustingWidgets.push_back(createRecordsDisplayTypeModifierWidgets());
        m_chartAdjustingWidgets.push_back(createPocketFilterButton());
        m_chartAdjustingWidgets.push_back(createIgnoreExtremesButton());

        //Invert the vector so the contained widgets will appear in the correct order
        std::reverse(m_chartAdjustingWidgets.begin(), m_chartAdjustingWidgets.end());
    }

    void RecordsDataChartView::showSelectedBarSeries()
    {
        //Remove and delete the attached series
        //Only one QBarSeries is initialized at the same time so deleteAllSeries is safe
        m_chart->removeAllSeries();

        m_barSeries = new QBarSeries();

        //Counters for the negative and positive QBarSets
        int negativeValueCounter = -1;
        int positiveValueCounter = -1;

        //Get the summarized (and sorted) Records data and create a QBarSet for each
        const auto& summarizedRecordsData = summarizeRecordsData();
        for(const auto& [item, value] : summarizedRecordsData)
        {
            QBarSet* barSet = new QBarSet(item);
            barSet->setLabelColor(Qt::white);

            //Set the color of the QBarSet according to the current value and counter
            if(value >= 0 )
            {
                barSet->setBrush(calculateColor(positiveValueCounter, true));
            }
            else
            {
                barSet->setBrush(calculateColor(negativeValueCounter, false));
            }

            barSet->append(value);
            m_barSeries->append(barSet);
        }

        //Check whether the extreme QBarSets should be ignored
        ignoreExtremeBars();

        //Set the series and axis of the QChart
        m_chart->addSeries(m_barSeries);
        m_chart->createDefaultAxes();
        //The X axis is not needed remove and delete it
        if(!m_chart->axes(Qt::Horizontal).empty())
        {
            auto xAxis = m_chart->axes(Qt::Horizontal).at(0);
            m_chart->removeAxis(xAxis);
            xAxis->deleteLater();
        }

        //Show the QChart labels with adjusted fonts
        m_chart->legend()->setVisible(true);
        m_chart->legend()->setAlignment(Qt::AlignRight);

        QFont font = m_chart->legend()->font();
        font.setPointSizeF(14);
        m_chart->legend()->setFont(font);

        //Set additional QChart texts (Title and Labels)
        adjustSeriesDisplay();
        m_barSeries->setLabelsPosition(QAbstractBarSeries::LabelsPosition::LabelsOutsideEnd);
        m_barSeries->setLabelsPrecision(10);
        m_barSeries->setLabelsVisible();
    }

    QColor RecordsDataChartView::calculateColor(int &counter, bool isPositive)
    {
        counter += 1;
        QColor color;

        //Check whether the current color is needed for positive or negative QBarSet
        if(isPositive)
        {
            //Two types of green is used
            //1. For the first 10 positive green color: rgb(x, 255, x)
            //2. From the eleventh color: rgb(0, 155 + x, 0)
            if(counter > 10)
            {
                color = QColor((counter - 10) * 10, 255, (counter - 10) * 10);
            }
            else
            {
                color = QColor(0, 155 + (counter * 10), 0);
            }
        }
        else
        {
            //Two types of red is used
            //1. For the first 6 negative red color: rgb(255 - x, 0, 0)
            //2. From the sixth color: rgb(255, 60 - x , 60 - x)
            if(counter > 6)
            {
                color = QColor(255 - ((counter-6) * 10), 0, 0);
            }
            else
            {
                color = QColor(255, 60 - (counter * 10), 60 - (counter * 10));
            }
        }

        return color;
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

                showSelectedBarSeries();
            });

            filterMenu->addAction(filterAction);
        }

        filterButton->setMenu(filterMenu);

        return filterButton;
    }

    QPushButton *RecordsDataChartView::createIgnoreExtremesButton()
    {
        //Create a checkable QPushButton for the ignore extremes function
        QPushButton* ignoreExtremesButton = new QPushButton("Ignore Extremes");
        ignoreExtremesButton->setCheckable(true);
        ignoreExtremesButton->setChecked(false);

        //If the button is toggled adjust the corresponding flag and show the modified series
        connect(ignoreExtremesButton, &QPushButton::toggled, [=] (bool checked)
        {
            m_ignoreExtremes = checked;
            showSelectedBarSeries();
        });

        return ignoreExtremesButton;
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

    void RecordsDataChartView::adjustSeriesDisplay()
    {
        //According to the currently set Records Data Display Mode value
        //set the newly used series and modify the displayed information
        if(m_recordsDataDisplayMode == RecordsDataDisplayMode::RECORDS_VALUE)
        {
            m_chart->setTitle("Records Value Chart");
            m_chart->axes(Qt::Vertical).at(0)->setTitleText("Value (HUF)");
        }
        else if(m_recordsDataDisplayMode == RecordsDataDisplayMode::RECORDS_COUNT)
        {
            m_chart->setTitle("Records Count Chart");
            m_chart->axes(Qt::Vertical).at(0)->setTitleText("Value (Records count)");
        }
        else
        {
            return;
        }
    }

    void RecordsDataChartView::ignoreExtremeBars()
    {
        //Check whether the series' extreme QBarSets should be ignored
        if(m_ignoreExtremes)
        {
            //Calculate the absolute sum of the QBarSets
            int sum = 0;
            const auto& bars = m_barSeries->barSets();
            std::for_each(std::execution::par, bars.begin(), bars.end(), [&](QBarSet* barSet)
            {
                sum += std::abs(barSet->sum());
            });

            //Remove the QBarSets from the series which QBarSet's value is over the calculated average*2
            const int avg = sum / bars.size();
            std::for_each(bars.begin(), bars.end(), [&](QBarSet* barSet)
            {
                if(std::abs(barSet->sum()) > (avg * 2))
                {
                    m_barSeries->remove(barSet);
                }
            });
        }
    }

    const std::vector<std::pair<QString, int>> RecordsDataChartView::summarizeRecordsData()
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

        //Create a sorted vector from the created map
        std::vector<std::pair<QString, int>> sortedRecordsData;
        sortSummarizedRecordsData(summarizedRecordsData, sortedRecordsData);

        return sortedRecordsData;
    }

    void RecordsDataChartView::sortSummarizedRecordsData(const std::unordered_map<QString, int>& summarizedRecordsData, std::vector<std::pair<QString, int>>& sortedRecordsData)
    {
        sortedRecordsData.reserve(summarizedRecordsData.size());

        //Convert the parameter given map to a vector
        for(const auto& it : summarizedRecordsData)
        {
            sortedRecordsData.push_back(it);
        }

        //Sort the vector
        std::sort(std::execution::par, sortedRecordsData.begin(), sortedRecordsData.end(), [](const std::pair<QString, int>& a, const std::pair<QString, int>& b)
        {
            return a.second > b.second;
        });
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
            showSelectedBarSeries();
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
            showSelectedBarSeries();
        }
    }
}
