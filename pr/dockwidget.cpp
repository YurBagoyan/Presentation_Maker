#include "dockwidget.h"

#include <QDockWidget>
#include <QMainWindow>
#include <QActionGroup>
#include <QMenu>

DockWidget::DockWidget(const QString widgetName, QMainWindow *parent)
    : QDockWidget(parent)
    , mainWindow(parent)
{
    setObjectName(widgetName);
    setWindowTitle(widgetName);

    SetActions();
    SetAlowedAreas();
    SetAreaActions();

    menu = new QMenu(widgetName, this);
    menu->addAction(closableAction);
    menu->addAction(movableAction);
    menu->addAction(floatableAction);
    menu->addAction(floatingAction);

    menu->addSeparator();
    menu->addActions(allowedAreasActions->actions());
    menu->addSeparator();
    menu->addActions(areaActions->actions());

    connect(menu, &QMenu::aboutToShow, this, &DockWidget::updateContextMenu);
}

void DockWidget::SetActions()
{
    closableAction = new QAction(tr("Closable"), this);
    closableAction->setCheckable(true);
    connect(closableAction, &QAction::triggered, this, &DockWidget::changeClosable);

    movableAction = new QAction(tr("Movable"), this);
    movableAction->setCheckable(true);
    connect(movableAction, &QAction::triggered, this, &DockWidget::changeMovable);

    floatableAction = new QAction(tr("Floatable"), this);
    floatableAction->setCheckable(true);
    connect(floatableAction, &QAction::triggered, this, &DockWidget::changeFloatable);

    floatingAction = new QAction(tr("Floating"), this);
    floatingAction->setCheckable(true);
    connect(floatingAction, &QAction::triggered, this, &DockWidget::changeFloating);

    connect(floatableAction, &QAction::triggered, floatingAction, &QAction::setEnabled);
    connect(floatingAction, &QAction::triggered, floatableAction, &QAction::setDisabled);
    //connect(movableAction, &QAction::triggered, areaActions, &QActionGroup::setEnabled);
    //connect(movableAction, &QAction::triggered, allowedAreasActions, &QActionGroup::setEnabled);
    connect(movableAction, &QAction::triggered, floatableAction, &QAction::setEnabled);

}

void DockWidget::SetAlowedAreas()
{
    allowedAreasActions = new QActionGroup(this);
    allowedAreasActions->setExclusive(false);

    allowLeftAction = new QAction(tr("Allow on Left"), this);
    allowLeftAction->setCheckable(true);
    connect(allowLeftAction, &QAction::triggered, this, &DockWidget::allowLeft);

    allowRightAction = new QAction(tr("Allow on Right"), this);
    allowRightAction->setCheckable(true);
    connect(allowRightAction, &QAction::triggered, this, &DockWidget::allowRight);

    allowTopAction = new QAction(tr("Allow on Top"), this);
    allowTopAction->setCheckable(true);
    connect(allowTopAction, &QAction::triggered, this, &DockWidget::allowTop);

    allowBottomAction = new QAction(tr("Allow on Bottom"), this);
    allowBottomAction->setCheckable(true);
    connect(allowBottomAction, &QAction::triggered, this, &DockWidget::allowBottom);

    allowedAreasActions->addAction(allowLeftAction);
    allowedAreasActions->addAction(allowRightAction);
    allowedAreasActions->addAction(allowTopAction);
    allowedAreasActions->addAction(allowBottomAction);
}

void DockWidget::SetAreaActions()
{
    areaActions = new QActionGroup(this);
    areaActions->setExclusive(true);

    leftAction = new QAction(tr("Place on Left") , this);
    leftAction->setCheckable(true);
    connect(leftAction, &QAction::triggered, this, &DockWidget::placeLeft);

    rightAction = new QAction(tr("Place on Right") , this);
    rightAction->setCheckable(true);
    connect(rightAction, &QAction::triggered, this, &DockWidget::placeRight);

    topAction = new QAction(tr("Place on Top") , this);
    topAction->setCheckable(true);
    connect(topAction, &QAction::triggered, this, &DockWidget::placeTop);

    bottomAction = new QAction(tr("Place on Bottom") , this);
    bottomAction->setCheckable(true);
    connect(bottomAction, &QAction::triggered, this, &DockWidget::placeBottom);

    areaActions->addAction(leftAction);
    areaActions->addAction(rightAction);
    areaActions->addAction(topAction);
    areaActions->addAction(bottomAction);
}

void DockWidget::updateContextMenu()
{
    const Qt::DockWidgetArea area = mainWindow->dockWidgetArea(this);
    const Qt::DockWidgetAreas areas = allowedAreas();

    closableAction->setChecked(features() & QDockWidget::DockWidgetClosable);
    if (windowType() == Qt::Drawer) {
        floatableAction->setEnabled(false);
        floatingAction->setEnabled(false);
        movableAction->setEnabled(false);
    } else {
        floatableAction->setChecked(features() & QDockWidget::DockWidgetFloatable);
        floatingAction->setChecked(isWindow());
        // done after floating, to get 'floatable' correctly initialized
        movableAction->setChecked(features() & QDockWidget::DockWidgetMovable);
    }

    allowLeftAction->setChecked(isAreaAllowed(Qt::LeftDockWidgetArea));
    allowRightAction->setChecked(isAreaAllowed(Qt::RightDockWidgetArea));
    allowTopAction->setChecked(isAreaAllowed(Qt::TopDockWidgetArea));
    allowBottomAction->setChecked(isAreaAllowed(Qt::BottomDockWidgetArea));

    if (allowedAreasActions->isEnabled()) {
        allowLeftAction->setEnabled(area != Qt::LeftDockWidgetArea);
        allowRightAction->setEnabled(area != Qt::RightDockWidgetArea);
        allowTopAction->setEnabled(area != Qt::TopDockWidgetArea);
        allowBottomAction->setEnabled(area != Qt::BottomDockWidgetArea);
    }

    {
        const QSignalBlocker blocker(leftAction);
        leftAction->setChecked(area == Qt::LeftDockWidgetArea);
    }
    {
        const QSignalBlocker blocker(rightAction);
        rightAction->setChecked(area == Qt::RightDockWidgetArea);
    }
    {
        const QSignalBlocker blocker(topAction);
        topAction->setChecked(area == Qt::TopDockWidgetArea);
    }
    {
        const QSignalBlocker blocker(bottomAction);
        bottomAction->setChecked(area == Qt::BottomDockWidgetArea);
    }

    if (areaActions->isEnabled()) {
        leftAction->setEnabled(areas & Qt::LeftDockWidgetArea);
        rightAction->setEnabled(areas & Qt::RightDockWidgetArea);
        topAction->setEnabled(areas & Qt::TopDockWidgetArea);
        bottomAction->setEnabled(areas & Qt::BottomDockWidgetArea);
    }


}

void DockWidget::allow(Qt::DockWidgetArea area, bool allow)
{
    Qt::DockWidgetAreas areas = allowedAreas();
    areas = allow ? areas | area : areas & ~area;
    setAllowedAreas(areas);

    if (areaActions->isEnabled()) {
        leftAction->setEnabled(areas & Qt::LeftDockWidgetArea);
        rightAction->setEnabled(areas & Qt::RightDockWidgetArea);
        topAction->setEnabled(areas & Qt::TopDockWidgetArea);
        bottomAction->setEnabled(areas & Qt::BottomDockWidgetArea);
    }
}

void DockWidget::place(Qt::DockWidgetArea area, bool place)
{
    if (!place)
        return;

    mainWindow->addDockWidget(area, this);

    if (allowedAreasActions->isEnabled()) {
        allowLeftAction->setEnabled(area != Qt::LeftDockWidgetArea);
        allowRightAction->setEnabled(area != Qt::RightDockWidgetArea);
        allowTopAction->setEnabled(area != Qt::TopDockWidgetArea);
        allowBottomAction->setEnabled(area != Qt::BottomDockWidgetArea);
    }
}

void DockWidget::changeClosable(bool on)
{ setFeatures(on ? features() | DockWidgetClosable : features() & ~DockWidgetClosable); }

void DockWidget::changeMovable(bool on)
{ setFeatures(on ? features() | DockWidgetMovable : features() & ~DockWidgetMovable); }

void DockWidget::changeFloatable(bool on)
{ setFeatures(on ? features() | DockWidgetFloatable : features() & ~DockWidgetFloatable); }

void DockWidget::changeFloating(bool floating)
{ setFloating(floating); }

void DockWidget::allowLeft(bool a)
{ allow(Qt::LeftDockWidgetArea, a); }

void DockWidget::allowRight(bool a)
{ allow(Qt::RightDockWidgetArea, a); }

void DockWidget::allowTop(bool a)
{ allow(Qt::TopDockWidgetArea, a); }

void DockWidget::allowBottom(bool a)
{ allow(Qt::BottomDockWidgetArea, a); }

void DockWidget::placeLeft(bool p)
{ place(Qt::LeftDockWidgetArea, p); }

void DockWidget::placeRight(bool p)
{ place(Qt::RightDockWidgetArea, p); }

void DockWidget::placeTop(bool p)
{ place(Qt::TopDockWidgetArea, p); }

void DockWidget::placeBottom(bool p)
{ place(Qt::BottomDockWidgetArea, p); }
