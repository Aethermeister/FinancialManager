#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * MainWindow Ui class
 * This widget is the base for every other widget
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
};
#endif // MAINWINDOW_H
