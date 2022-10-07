#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class ToolBar;


class MainWindow : public QMainWindow
{
public:
    typedef QMap<QString, QSize> CustomSizeHintMap;

    explicit MainWindow(QWidget *parent = nullptr,
                        Qt::WindowFlags flags = 0);

public:
    void saveLayout();
    void createDockWidget();
    void destroyDockWidget(QAction *action);
    void about();

private:
    void setupToolBar();
    void setupMenuBar();
    void setupDockWidgets();

    QList<ToolBar*> toolBars;
    QMenu *dockWidgetMenu;
    QMenu *mainWindowMenu;
    QList<QDockWidget *> extraDockWidgets;
    QMenu *destroyDockWidgetMenu;
};

#endif // MAINWINDOW_H
