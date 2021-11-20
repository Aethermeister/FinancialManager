#ifndef POCKETLISTINGWIDGET_H
#define POCKETLISTINGWIDGET_H
#include "user.h"

#include <QSpacerItem>
#include <QWidget>

namespace Ui {
class PocketListingWidget;
}

namespace Content::Pockets::Component
{
    /**
     * Ui class which lists the given User's pockets
     * This class is responsible for keeping the listed pockets up-to-date
    */
    class LIB_EXPORT PocketListingWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit PocketListingWidget(QWidget *parent = nullptr);
        ~PocketListingWidget();

        /**
         * Initializes the widget by listing every Pocket of the given User
         * Also handles the user's interactions made on the listed Pocket items
        */
        void initialize(std::shared_ptr<User> user);

    private:
        Ui::PocketListingWidget *ui;

        /**
         * Spacer item which is used to align the listed Pocket list items correctly
        */
        QSpacerItem* m_listSpacer = nullptr;
    };
}

#endif // POCKETLISTINGWIDGET_H
