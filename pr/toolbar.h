#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>
#include <QAction>

class ToolBar : public QToolBar

{
    Q_OBJECT
public:
    ToolBar(const QString &title, QWidget *parent = nullptr);
    ~ToolBar() = default;

    QMenu *toolbarMenu() const { return menu; }

    void SetMovableActions();
    void SetAlowedAreas();
    void SetAreaActions();

private slots:

    void changeMovable(bool movable);

    void allowLeft(bool allow);
    void allowRight(bool allow);
    void allowTop(bool allow);
    void allowBottom(bool allow);

    void placeLeft(bool place);
    void placeRight(bool place);
    void placeTop(bool place);
    void placeBottom(bool place);

    void updateMenu();

private:
    void allow(Qt::ToolBarArea area, bool allow);
    void place(Qt::ToolBarArea area, bool place);

    QMenu *menu;
    QAction *movableAction;

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

};

#endif // TOOLBAR_H
