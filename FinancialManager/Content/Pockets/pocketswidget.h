#ifndef POCKETSWIDGET_H
#define POCKETSWIDGET_H
#include <user.h>

#include <QSpacerItem>
#include <QWidget>

namespace Ui {
class PocketsWidget;
}

namespace Content::Pockets
{
    /**
     * Ui class which provides interactable interface for the user to create new Pockets
     * This class is responsible for correctly creating and managing the Pockets
    */
    class PocketsWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit PocketsWidget(std::shared_ptr<User> user, QWidget *parent = nullptr);
        ~PocketsWidget();

    private:
        Ui::PocketsWidget *ui;

        /**
         * Sets the initial state of the Ui
        */
        void initializeUi();
        /**
         * Sets the common connections related to this class
        */
        void initializeConnections();
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
         * Starts the new Pcket validation and persisting procedure
        */
        void slot_createNewPocket();
    };
}

#endif // POCKETSWIDGET_H
