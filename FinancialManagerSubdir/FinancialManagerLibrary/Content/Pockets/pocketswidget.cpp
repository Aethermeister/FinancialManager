#include "pocketswidget.h"
#include "ui_pocketswidget.h"
#include "Core/defines.h"
#include "Components/pocketlistitemwidget.h"

namespace Content::Pockets
{
    PocketsWidget::PocketsWidget(std::shared_ptr<User> user, QWidget *parent) :
        QWidget(parent),
        ui(new Ui::PocketsWidget),
        m_user(user)
    {
        ui->setupUi(this);

        initializeUi();
        initializeConnections();
    }

    PocketsWidget::~PocketsWidget()
    {
        delete ui;
    }

    QLineEdit *PocketsWidget::pocketNameLineEdit()
    {
        return ui->m_newPocketName_lineEdit;
    }

    QLineEdit *PocketsWidget::pocketInitialValueLineEdit()
    {
        return ui->m_newPocketInitialValue_lineEdit;
    }

    QComboBox *PocketsWidget::pocketTypeComboBox()
    {
        return ui->m_pocketType_comboBox;
    }

    QPushButton *PocketsWidget::createNewPocketButton()
    {
        return ui->m_createNewPocket_btn;
    }

    QLabel *PocketsWidget::informationLabel()
    {
        return ui->m_information_lbl;
    }

    QWidget *PocketsWidget::pocketListingWidget()
    {
        return ui->m_pocketListing_widget;
    }

    void PocketsWidget::initializeUi()
    {
        //Make the Pcket type combobox editable so a QLineEdit is created automatically
        //Set the state of the automatic QLineEdit
        ui->m_pocketType_comboBox->setEditable(true);
        ui->m_pocketType_comboBox->lineEdit()->setReadOnly(true);
        ui->m_pocketType_comboBox->lineEdit()->setAlignment(Qt::AlignCenter);
        ui->m_pocketType_comboBox->lineEdit()->setPlaceholderText("Select Pocket Type");

        ui->m_information_lbl->setVisible(false);

        //Populate the type combobox with the Pocket types
        QStringList pocketTypes;
        for(int it = Content::Pockets::PocketType::CASH; it != Content::Pockets::PocketType::END_OF_ENUM; it++)
        {
            pocketTypes << Pocket::pocketTypeToString(static_cast<Content::Pockets::PocketType>(it));
        }
        ui->m_pocketType_comboBox->addItems(pocketTypes);
        ui->m_pocketType_comboBox->setCurrentIndex(-1);

        //List the available Pockets
        updatePocketList();
    }

    void PocketsWidget::initializeConnections() const
    {
        connect(ui->m_createNewPocket_btn, &QPushButton::clicked, this, &PocketsWidget::slot_createNewPocket);
    }

    void PocketsWidget::updatePocketList()
    {
        ui->m_pocketListing_widget->initialize(m_user);
    }

    void PocketsWidget::slot_createNewPocket()
    {
        //Reset the error state
        setWidgetErrorState(ui->m_newPocketName_lineEdit, false);
        setWidgetErrorState(ui->m_newPocketInitialValue_lineEdit, false);
        setWidgetErrorState(ui->m_pocketType_comboBox, false);
        ui->m_information_lbl->setVisible(false);

        //Get the new Pocket information from the Ui
        const auto pocketName = ui->m_newPocketName_lineEdit->text();
        const auto pocketValueString = ui->m_newPocketInitialValue_lineEdit->text();
        const auto pockeType = ui->m_pocketType_comboBox->currentText();

        //Get the pocket name from the ui and check whether it is a NOT empty QString
        //Set error style in case of error
        if(pocketName.trimmed().isEmpty())
        {
            setWidgetErrorState(ui->m_newPocketName_lineEdit, true);
            showInformation(ui->m_information_lbl, "Pocket name cannot be empty");

            return;
        }

        //Check whether the new Pocket name already exists
        //Set error style if the name already exists
        for(auto& pocket : m_user->pockets())
        {
            if(pocket.name() == pocketName)
            {
                setWidgetErrorState(ui->m_newPocketName_lineEdit, true);
                showInformation(ui->m_information_lbl, "Pocket with the same name already exists");

                return;
            }
        }

        //Get the value from the ui and check whether it is a valid integer
        //Set error style in case of error
        bool isValueValid = false;
        const auto pocketValue = pocketValueString.toInt(&isValueValid);
        if(!isValueValid)
        {
            setWidgetErrorState(ui->m_newPocketInitialValue_lineEdit, true);
            showInformation(ui->m_information_lbl, "Pocket initial value is invalid");

            return;
        }

        //Check whether the Pocket type is set
        //Set error style in case of error
        if(pockeType.isEmpty())
        {
            setWidgetErrorState(ui->m_pocketType_comboBox, true);
            showInformation(ui->m_information_lbl, "Pocket type cannot be empty");

            return;
        }

        //Create a new Pocket and update the user's list and the Ui
        Pocket pocket{pocketName, pockeType, pocketValue};
        m_user->addNewPocket(pocket);

        updatePocketList();
    }
}
