#include "colorswatch.h"

#include <QFrame>
#include <QMainWindow>
#include <QMenu>
#include <QPainter>


QColor bgColorForName(const QString &name)
{
    if (name == "File Explorer")
        return QColor("#D8D8D8");
    if (name == "Slide Info")
        return QColor("#F1F1F1");
    if (name == "Text Tools")
        return QColor("#F1D8D8");
    if (name == "Main Tools")
        return QColor("#D8E4D8");
    if (name == "Slides")
        return QColor("#F1F0D8");
    return QColor(name).lighter(110);
}

QColor fgColorForName(const QString &name)
{
    if (name == "File Explorer")
        return QColor("#6C6C6C");
    if (name == "Slide Info")
        return QColor("#F8F8F8");
    if (name == "Text Tools")
        return QColor("#F86C6C");
    if (name == "Main Tools")
        return QColor("#6CB26C");
    if (name == "Slides")
        return QColor("#F8F76C");
    return QColor(name);
}

class ColorDock : public QFrame
{
     Q_OBJECT
public:
    explicit ColorDock(const QString &c, QWidget *parent);

    QSize sizeHint() const override { return szHint; }
    QSize minimumSizeHint() const override { return minSzHint; }

    void setCustomSizeHint(const QSize &size);

protected:
    void paintEvent(QPaintEvent *) override;

private:
    const QString color;
    QSize szHint;
    QSize minSzHint;
};

ColorDock::ColorDock(const QString &c, QWidget *parent)
    : QFrame(parent)
    , color(c)
    , szHint(-1, -1)
    , minSzHint(125, 75)
{
    QFont font = this->font();
    font.setPointSize(8);
    setFont(font);
}

void ColorDock::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.fillRect(rect(), bgColorForName(color));

    p.save();
    p.restore();
}

void ColorDock::setCustomSizeHint(const QSize &size)
{
    if (szHint != size) {
        szHint = size;
        updateGeometry();
    }
}

ColorSwatch::ColorSwatch(const QString &colorName, QMainWindow *parent, Qt::WindowFlags flags)
    : QDockWidget(parent, flags), mainWindow(parent)
{
    setObjectName(colorName + QLatin1String(" Dock Widget"));
    setWindowTitle(objectName() + QLatin1String(" [*]"));

    ColorDock *swatch = new ColorDock(colorName, this);
    swatch->setFrameStyle(QFrame::Box | QFrame::Sunken);

    setWidget(swatch);

    closableAction = new QAction(tr("Closable"), this);
    closableAction->setCheckable(true);
    connect(closableAction, &QAction::triggered, this, &ColorSwatch::changeClosable);

    movableAction = new QAction(tr("Movable"), this);
    movableAction->setCheckable(true);
    connect(movableAction, &QAction::triggered, this, &ColorSwatch::changeMovable);

    floatableAction = new QAction(tr("Floatable"), this);
    floatableAction->setCheckable(true);
    connect(floatableAction, &QAction::triggered, this, &ColorSwatch::changeFloatable);

    verticalTitleBarAction = new QAction(tr("Vertical title bar"), this);
    verticalTitleBarAction->setCheckable(true);
    connect(verticalTitleBarAction, &QAction::triggered,
            this, &ColorSwatch::changeVerticalTitleBar);

    floatingAction = new QAction(tr("Floating"), this);
    floatingAction->setCheckable(true);
    connect(floatingAction, &QAction::triggered, this, &ColorSwatch::changeFloating);

    allowedAreasActions = new QActionGroup(this);
    allowedAreasActions->setExclusive(false);

    allowLeftAction = new QAction(tr("Allow on Left"), this);
    allowLeftAction->setCheckable(true);
    connect(allowLeftAction, &QAction::triggered, this, &ColorSwatch::allowLeft);

    allowRightAction = new QAction(tr("Allow on Right"), this);
    allowRightAction->setCheckable(true);
    connect(allowRightAction, &QAction::triggered, this, &ColorSwatch::allowRight);

    allowTopAction = new QAction(tr("Allow on Top"), this);
    allowTopAction->setCheckable(true);
    connect(allowTopAction, &QAction::triggered, this, &ColorSwatch::allowTop);

    allowBottomAction = new QAction(tr("Allow on Bottom"), this);
    allowBottomAction->setCheckable(true);
    connect(allowBottomAction, &QAction::triggered, this, &ColorSwatch::allowBottom);

    allowedAreasActions->addAction(allowLeftAction);
    allowedAreasActions->addAction(allowRightAction);
    allowedAreasActions->addAction(allowTopAction);
    allowedAreasActions->addAction(allowBottomAction);

    areaActions = new QActionGroup(this);
    areaActions->setExclusive(true);

    leftAction = new QAction(tr("Place on Left") , this);
    leftAction->setCheckable(true);
    connect(leftAction, &QAction::triggered, this, &ColorSwatch::placeLeft);

    rightAction = new QAction(tr("Place on Right") , this);
    rightAction->setCheckable(true);
    connect(rightAction, &QAction::triggered, this, &ColorSwatch::placeRight);

    topAction = new QAction(tr("Place on Top") , this);
    topAction->setCheckable(true);
    connect(topAction, &QAction::triggered, this, &ColorSwatch::placeTop);

    bottomAction = new QAction(tr("Place on Bottom") , this);
    bottomAction->setCheckable(true);
    connect(bottomAction, &QAction::triggered, this, &ColorSwatch::placeBottom);

    areaActions->addAction(leftAction);
    areaActions->addAction(rightAction);
    areaActions->addAction(topAction);
    areaActions->addAction(bottomAction);

    connect(movableAction, &QAction::triggered, areaActions, &QActionGroup::setEnabled);
    connect(movableAction, &QAction::triggered, allowedAreasActions, &QActionGroup::setEnabled);
    connect(floatableAction, &QAction::triggered, floatingAction, &QAction::setEnabled);
    connect(floatingAction, &QAction::triggered, floatableAction, &QAction::setDisabled);
    connect(movableAction, &QAction::triggered, floatableAction, &QAction::setEnabled);

    menu = new QMenu(colorName, this);
    menu->addAction(toggleViewAction());
    menu->addAction(tr("Raise"), this, &QWidget::raise);

    menu->addSeparator();
    menu->addAction(closableAction);
    menu->addAction(movableAction);
    menu->addAction(floatableAction);
    menu->addAction(floatingAction);
    menu->addAction(verticalTitleBarAction);
    menu->addSeparator();
    menu->addActions(allowedAreasActions->actions());
    menu->addSeparator();
    menu->addActions(areaActions->actions());
    menu->addSeparator();
    menu->addSeparator();
}



void ColorSwatch::resizeEvent(QResizeEvent *e)
{
    QDockWidget::resizeEvent(e);
}

void ColorSwatch::allow(Qt::DockWidgetArea area, bool a)
{
    Qt::DockWidgetAreas areas = allowedAreas();
    areas = a ? areas | area : areas & ~area;
    setAllowedAreas(areas);

    if (areaActions->isEnabled()) {
        leftAction->setEnabled(areas & Qt::LeftDockWidgetArea);
        rightAction->setEnabled(areas & Qt::RightDockWidgetArea);
        topAction->setEnabled(areas & Qt::TopDockWidgetArea);
        bottomAction->setEnabled(areas & Qt::BottomDockWidgetArea);
    }
}

void ColorSwatch::place(Qt::DockWidgetArea area, bool p)
{
    if (!p)
        return;

    mainWindow->addDockWidget(area, this);

    if (allowedAreasActions->isEnabled()) {
        allowLeftAction->setEnabled(area != Qt::LeftDockWidgetArea);
        allowRightAction->setEnabled(area != Qt::RightDockWidgetArea);
        allowTopAction->setEnabled(area != Qt::TopDockWidgetArea);
        allowBottomAction->setEnabled(area != Qt::BottomDockWidgetArea);
    }
}

void ColorSwatch::setCustomSizeHint(const QSize &size)
{
    if (ColorDock *dock = qobject_cast<ColorDock*>(widget()))
        dock->setCustomSizeHint(size);
}

void ColorSwatch::changeClosable(bool on)
{ setFeatures(on ? features() | DockWidgetClosable : features() & ~DockWidgetClosable); }

void ColorSwatch::changeMovable(bool on)
{ setFeatures(on ? features() | DockWidgetMovable : features() & ~DockWidgetMovable); }

void ColorSwatch::changeFloatable(bool on)
{ setFeatures(on ? features() | DockWidgetFloatable : features() & ~DockWidgetFloatable); }

void ColorSwatch::changeFloating(bool floating)
{ setFloating(floating); }

void ColorSwatch::allowLeft(bool a)
{ allow(Qt::LeftDockWidgetArea, a); }

void ColorSwatch::allowRight(bool a)
{ allow(Qt::RightDockWidgetArea, a); }

void ColorSwatch::allowTop(bool a)
{ allow(Qt::TopDockWidgetArea, a); }

void ColorSwatch::allowBottom(bool a)
{ allow(Qt::BottomDockWidgetArea, a); }

void ColorSwatch::placeLeft(bool p)
{ place(Qt::LeftDockWidgetArea, p); }

void ColorSwatch::placeRight(bool p)
{ place(Qt::RightDockWidgetArea, p); }

void ColorSwatch::placeTop(bool p)
{ place(Qt::TopDockWidgetArea, p); }

void ColorSwatch::placeBottom(bool p)
{ place(Qt::BottomDockWidgetArea, p); }

void ColorSwatch::changeVerticalTitleBar(bool on)
{
    setFeatures(on ? features() | DockWidgetVerticalTitleBar
                    : features() & ~DockWidgetVerticalTitleBar);
}

#include "colorswatch.moc"
