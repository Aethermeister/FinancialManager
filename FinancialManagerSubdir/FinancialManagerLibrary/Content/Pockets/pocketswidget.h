#ifndef POCKETSWIDGET_H
#define POCKETSWIDGET_H
#include <user.h>

#include <QSpacerItem>
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>

namespace Ui {
class PocketsWidget;
}

namespace Content::Pockets
{
    /**
     * Ui class which provides interactable interface for the user to create new Pockets
     * This class is responsible for correctly creating and managing the Pockets
    */
    class LIB_EXPORT PocketsWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit PocketsWidget(std::shared_ptr<User> user, QWidget *parent = nullptr);
        ~PocketsWidget();

        /**
         * Returns the pockets widget's new pocket name QLineEdit
         * Used so test project(s) can access it
        */
        QLineEdit* pocketNameLineEdit();
        /**
         * Returns the pockets widget's new pocket initial value QLineEdit
         * Used so test project(s) can access it
        */
        QLineEdit* pocketInitialValueLineEdit();
        /**
         * Returns the pockets widget's new pocket type QComboBox
         * Used so test project(s) can access it
        */
        QComboBox* pocketTypeComboBox();
        /**
         * Returns the pockets widget's create new pocket QPushButton
         * Used so test project(s) can access it
        */
        QPushButton* createNewPocketButton();
        /**
         * Returns the pockets widget's new pocket creation information QLabel
         * Used so test project(s) can access it
        */
        QLabel* informationLabel();
        /**
         * Returns the pockets widget's pockets listing QWidget
         * Used so test project(s) can access it
        */
        QWidget* pocketListingWidget();

    private:
        Ui::PocketsWidget *ui;

        /**
         * Sets the initial state of the Ui
        */
        void initializeUi();
        /**
         * Sets the common connections related to this class
        */
        void initializeConnections() const;
        /**
         * Lists the user's available Pockets
        */
        void updatePocketList();

        /**
         * The current user
        */
        std::shared_ptr<User> m_user;

    private slots:
        /**
         * Called when the Create New Pocket QPushButton is clicked
         * Starts the new Pocket validation and persisting procedure
        */
        void slot_createNewPocket();
    };
}

#endif // POCKETSWIDGET_H
