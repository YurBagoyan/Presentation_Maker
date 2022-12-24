#ifndef DOCKWIDGET_H
#define DOCKWIDGET_H

#include <QDockWidget>

class DockWidget : public QDockWidget
{
    Q_OBJECT
public:
    DockWidget(const QString widgetName, QMainWindow *parent = nullptr);
    QMenu *DockWidgetMenu() const { return menu; }

private:
    void SetActions();
    void SetAlowedAreas();
    void SetAreaActions();

private slots:
    void changeClosable(bool on);
    void changeMovable(bool on);
    void changeFloatable(bool on);
    void changeFloating(bool on);
    void updateContextMenu();

    void allowLeft(bool allow);
    void allowRight(bool allow);
    void allowTop(bool allow);
    void allowBottom(bool allow);

    void placeLeft(bool place);
    void placeRight(bool place);
    void placeTop(bool place);
    void placeBottom(bool place);

private:
    void allow(Qt::DockWidgetArea area, bool allow);
    void place(Qt::DockWidgetArea area, bool place);

    QAction *closableAction;
    QAction *movableAction;
    QAction *floatableAction;
    QAction *floatingAction;

    QActionGroup *allowedAreasActions;
    QAction *allowLeftAction;
    QAction *allowRightAction;
    QAction *allowTopAction;
    QAction *allowBottomAction;

    QActionGroup *areaActions;
    QAction *leftAction;
    QAction *rightAction;
    QAction *topAction;
    QAction *bottomAction;

    QMenu *menu;
    QMainWindow *mainWindow;
};

#endif // DOCKWIDGET_H
