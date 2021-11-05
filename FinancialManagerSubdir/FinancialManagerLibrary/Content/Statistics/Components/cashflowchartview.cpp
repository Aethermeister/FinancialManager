#include "cashflowchartview.h"

namespace Content::Statistics::Components
{
    CashFlowChartView::CashFlowChartView(std::shared_ptr<User> user, QWidget* parent) : ChartViewBase(user, parent)
    {

    }

    CashFlowChartView::~CashFlowChartView()
    {

    }

    void CashFlowChartView::initializeSeries()
    {
        //Collect the necessary data for series creation
        collectRecordsSeriesData();

        //Iterate over the collected data and create a series for each Pocket
        for(const auto& [pocketName, records] : m_pocketCashFlowMap)
        {
            QLineSeries* series = new QLineSeries();
            //Iterate over the summarized record values of each day of the Pocket
            for(const auto& [date, value] : records)
            {
                //Add the date and value to the series
                series->append(date.startOfDay().toMSecsSinceEpoch(), value);
            }

            //Add the series to the chart and store the series mapped to the Pocket
            series->setName(pocketName);
            m_chart->addSeries(series);
            m_pocketSeries[pocketName] = series;
        }

        //Create the axes of the chart
        //After creation update them so the chart is shown in the needed axis range
        createChartAxes();
        updateChartAxes();

        //Set the rubber band so zooming is enabled
        setRubberBand(QChartView::RubberBand::HorizontalRubberBand);
        //Show the legends at the top
        m_chart->legend()->setVisible(true);
        m_chart->legend()->setAlignment(Qt::AlignTop);
    }

    void CashFlowChartView::initializeChartAdjustingWidgets()
    {
        //Create the chart modifier widgets
        m_chartAdjustingWidgets.push_back(createIntervalButton());
        m_chartAdjustingWidgets.push_back(createPocketFilterButton());

        //Invert the vector so the contained widgets will appear in the correct order
        std::reverse(m_chartAdjustingWidgets.begin(), m_chartAdjustingWidgets.end());
    }

    void CashFlowChartView::mousePressEvent(QMouseEvent *event)
    {
        return QChartView::mousePressEvent(event);
    }

    void CashFlowChartView::mouseReleaseEvent(QMouseEvent *event)
    {
        //If the right mouse button is clicked restore the original axis range
        if(event->button() == Qt::RightButton)
        {
            m_chart->zoomReset();
        }
        else
        {
            return QChartView::mouseReleaseEvent(event);
        }
    }

    QString CashFlowChartView::convertCashFlowIntervalToString(const CashFlowInterval &interval)
    {
        QString intervalString;

        //According to the parameter given enum value return its QString representation
        if(interval == CashFlowInterval::WEEK)
        {
            intervalString = "Week";
        }
        else if(interval == CashFlowInterval::MONTH)
        {
            intervalString = "Month";
        }
        else if(interval == CashFlowInterval::YEAR)
        {
            intervalString = "Year";
        }
        else if(interval == CashFlowInterval::FULL)
        {
            intervalString = "Full";
        }

        return intervalString;
    }

    void CashFlowChartView::collectRecordsSeriesData()
    {
        //Iterate over the user's records and map the records value and creation date as a list to their Pockets
        //Reverse iteration is needed so the oldest value is at top
        std::unordered_map<QString, std::vector<std::pair<QDate, int>>> recordsValuesWithDateTimeToPocket;
        for(auto rit = m_user->records().rbegin(); rit != m_user->records().rend(); ++rit)
        {
            const auto& pocketName = rit->pocketName();
            const auto& recordValue = rit->value();
            const auto& recordDate = rit->date();

            recordsValuesWithDateTimeToPocket[pocketName].emplace_back(recordDate, recordValue);
        }

        //Iterate over the Pockets list and map the initial value and creation date of the Pocket
        std::unordered_map<QString, std::pair<QDate, int>> initialPocketValues;
        for(const auto& pocket : m_user->pockets())
        {
            initialPocketValues[pocket.name()] = {pocket.creationDate().date(), pocket.initialValue()};
        }

        //Iterate over the previously created raw Record values and dates of each Pocket
        //and summarize their value for each day
        for(const auto& [pocketName, records] : recordsValuesWithDateTimeToPocket)
        {
            //Initialize the first date and valu with the given Pocket's initial value and creation date
            QDate& firstDate = initialPocketValues[pocketName].first;
            int value = initialPocketValues[pocketName].second;

            //Use day counter so a value for each day can be added between the date range
            int dayCounter = 0;
            auto it = records.begin();
            while(firstDate.addDays(dayCounter) <= QDateTime::currentDateTime().date())
            {
                //If the iterator reaches the end just save the same value for the rest of teh days until the current date
                if(it == records.end())
                {
                    const auto date = firstDate.addDays(dayCounter);
                    m_pocketCashFlowMap[pocketName].emplace_back(date, value);

                    dayCounter += 1;
                    continue;
                }

                //If the iterator's date is the same as the checked date update the value and whatch the next Record by incrementing the iterator
                //In this case the day counter must not be updated because multiple Records can be on teh same day
                if(it->first == firstDate.addDays(dayCounter))
                {
                    value += it->second;
                    it++;
                }
                else //If the current iterator's date is not the same with the checked date save the current value for the current date
                    //and check the next day by incrementing the day counter
                {
                    const auto date = firstDate.addDays(dayCounter);
                    m_pocketCashFlowMap[pocketName].emplace_back(date, value);

                    dayCounter += 1;
                }
            }
        }
    }

    QPushButton *CashFlowChartView::createIntervalButton()
    {
        //Create a button with a menu attached to it which lists the available interval options
        QPushButton* intervalButton = new QPushButton(convertCashFlowIntervalToString(CashFlowInterval::WEEK));
        QMenu* intervalMenu = new QMenu(intervalButton);
        QActionGroup* actionGroup = new QActionGroup(intervalMenu);
        actionGroup->setExclusive(true); //The interval options must be exclusive

        //Iterate over the CashFlowInterval enum so a QAction is created for each value
        for(int it = CashFlowInterval::WEEK; it != CashFlowInterval::END_OF_ENUM; it++)
        {
            //Create an action for the current enum value and store the value as property
            const auto& intervalName = convertCashFlowIntervalToString(static_cast<CashFlowInterval>(it));
            QAction* action = new QAction(intervalName, actionGroup);
            action->setProperty("cashFlowIntervalType", it);
            action->setCheckable(true);
            action->setChecked(it == CashFlowInterval::WEEK);

            intervalMenu->addAction(action);

            //If the action is triggered update the interval variable and update the chart axes
            connect(action, &QAction::triggered, intervalButton, [=]
            {
                intervalButton->setText(intervalName);
                m_interval = static_cast<CashFlowInterval>(action->property("cashFlowIntervalType").toInt());
                updateChartAxes();
            });
        }

        intervalButton->setMenu(intervalMenu);

        return intervalButton;
    }

    QPushButton *CashFlowChartView::createPocketFilterButton()
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
                //and show the updated series and axes
                if(checked)
                {
                    m_pocketFilter.removeOne(pocketName);
                }
                else
                {
                    m_pocketFilter.append(pocketName);
                }


                updateChartAxes();
                filterSeries();
            });

            filterMenu->addAction(filterAction);
        }

        filterButton->setMenu(filterMenu);

        return filterButton;
    }

    void CashFlowChartView::createChartAxes()
    {
        //Create the base date axis and attach it to the chart
        m_dateAxis = new QDateTimeAxis;
        m_dateAxis->setTitleText("Date");
        m_chart->addAxis(m_dateAxis, Qt::AlignBottom);

        //Create the base value axis and attach it to the chart
        m_valueAxis = new QValueAxis;
        m_valueAxis->setLabelFormat("%i");
        m_valueAxis->setTitleText("Value [HUF]");
        m_chart->addAxis(m_valueAxis, Qt::AlignLeft);

        //Attach the created axes to the series of the chart
        for(auto& series : m_chart->series())
        {
            series->attachAxis(m_dateAxis);
            series->attachAxis(m_valueAxis);
        }
    }

    void CashFlowChartView::updateChartAxes()
    {
        //Initialize default setup of the chart axes
        QString dateFormat = "yyyy. MM. dd.";
        QDateTime minDateTime = QDate::currentDate().endOfDay();
        int tickCount = 10;

        //Set the date format, min of the date range and the tick count according to the selected interval
        if(m_interval == CashFlowInterval::WEEK)
        {
            dateFormat = "dd.";
            minDateTime = minDateTime.addDays(-7);
            tickCount = 8;
        }
        else if(m_interval == CashFlowInterval::MONTH)
        {
            dateFormat = "MM. dd.";
            minDateTime = minDateTime.addMonths(-1);
        }
        else if(m_interval == CashFlowInterval::YEAR)
        {
            dateFormat = "yyyy. MM. dd.";
            minDateTime = minDateTime.addYears(-1);
        }
        else if(m_interval == CashFlowInterval::FULL)
        {
            dateFormat = "yyyy. MM. dd.";
            minDateTime = filteredFirstDate();
        }

        m_dateAxis->setFormat(dateFormat);
        m_dateAxis->setRange(minDateTime, QDateTime::currentDateTime());
        m_dateAxis->setTickCount(tickCount);

        //Get the min and max values of the currently used date range and update the value axis
        const auto& [min, max] = filteredMinMaxValues(minDateTime);
        m_valueAxis->setRange(min, max);
    }

    void CashFlowChartView::filterSeries()
    {
        //Iterate over the series mapped to the Pockets
        //and adjust the series visibility according to the filter list
        for(const auto& [pocketName, series] : m_pocketSeries)
        {
            series->setVisible(!m_pocketFilter.contains(pocketName));
        }
    }

    QDateTime CashFlowChartView::filteredFirstDate() const
    {
        //Iterate over the user's Pockets and get the creation date of teh oldest Pocket
        //Ignore the filtered Pockets
        QDate firstDate = QDate(3000, 1, 1); //The initial value of the first date is a magic number
        for(const auto& pocket : m_user->pockets())
        {
            if(!m_pocketFilter.contains(pocket.name()))
            {
                if(firstDate > pocket.creationDate().date())
                {
                    firstDate = pocket.creationDate().date();
                }
            }
        }

        return firstDate.endOfDay();
    }

    std::pair<int, int> CashFlowChartView::filteredMinMaxValues(QDateTime minDateTime) const
    {
        //Initialize the min and max values
        //min with int max limit
        //max with int min limit
        int minValue = std::numeric_limits<int>::max();
        int maxValue = std::numeric_limits<int>::min();

        //Iterate over the series mapped to the Pockets
        //Ignore the filtered Pockets
        for(const auto& [pocket, series] : m_pocketSeries)
        {
            if(!m_pocketFilter.contains(pocket))
            {
                //Get the points list of the current series
                //and reverse iterate over them so the iteration begins from the current date
                const auto& points = series->points();
                for(auto it = points.rbegin(); it != points.rend(); ++it)
                {
                    //Get the current date time and value data
                    const auto& dateTime = QDateTime::fromMSecsSinceEpoch(it->x());
                    const auto& value = it->y();

                    //If the date time is lesser than the declared/parameter given min date time value break the iteration
                    //because the rest of the points data is ignored with the current date axis range
                    if(dateTime < minDateTime)
                    {
                        break;
                    }

                    //Check the min and max values and update them is needed
                    if(minValue > value)
                    {
                        minValue = value;
                    }
                    if(maxValue < value)
                    {
                        maxValue = value;
                    }
                }
            }
        }

        return std::make_pair(minValue * 0.9, maxValue * 1.1);
    }
}
