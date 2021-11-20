#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Core/global_defines.h"

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * MainWindow Ui class
 * This widget is the base for every other widget
*/
class LIB_EXPORT MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QWidget* containerWidget();
    QPushButton* profilButton();
    QLabel* titleLabel();

private:
    Ui::MainWindow *ui;

    /**
     * Shows the AuthenticationWidget ui in the content area
    */
    void showAuthenticationWidget();
    /**
     * Shows the ContentWidget ui in the content area
    */
    void showMainContentWidget(const QString& username, const QString& password, const QString& id);

private slots:
    /**
     * Shows the Settings Widget as a modal dialog over the MainWindow ui
    */
    void slot_showSettingsWindow();
};
#endif // MAINWINDOW_H
