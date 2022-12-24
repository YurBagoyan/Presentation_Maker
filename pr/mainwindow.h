#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "toolbar.h"
#include <dockwidget.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void CreateToolBar();
    void SetupDockWidgets();

private slots:
    void on_actionAbout_QT_triggered();

    void on_actionSave_Project_triggered();

    void on_actionAbout_triggered();

    void on_actionQuit_triggered();

    void on_actionDelete_Item_triggered();

    void on_actionPrint_triggered();

private:

    Ui::MainWindow *ui;

    ToolBar* fileToolBar{nullptr};
    ToolBar* editToolBar{nullptr};

    DockWidget* slidesWidget{nullptr};
    DockWidget* OptionsWidget{nullptr};

};
#endif // MAINWINDOW_H
