#ifndef POCKETLISTITEMWIDGET_H
#define POCKETLISTITEMWIDGET_H
#include "user.h"

#include <QWidget>

namespace Ui {
class PocketListItemWidget;
}

namespace Content::Pockets::Component
{
    /**
     * Ui class which acts as indicator for a given Pocket
     * This ui class is used by the PocketsWidget by listing the existing Pockets
    */
    class PocketListItemWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit PocketListItemWidget(std::shared_ptr<User> user, const Pocket& pocket, QWidget *parent = nullptr);
        ~PocketListItemWidget();

    private:
        Ui::PocketListItemWidget *ui;

        /**
         * Sets the initial state of the Ui
        */
        void initializeUi();

        /**
         * Sets the common connections related to this class
        */
        void initializeConnections();

        /**
         * The current user
        */
        std::shared_ptr<User> m_user;

        /**
         * The Pocket this object is initialized with
        */
        Pocket m_pocket;
    };
}

#endif // POCKETLISTITEMWIDGET_H
