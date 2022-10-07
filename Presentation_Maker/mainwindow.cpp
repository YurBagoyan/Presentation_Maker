#include "mainwindow.h"
#include "colorswatch.h"
#include "toolbar.h"

#include <QLayout>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QFileDialog>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QApplication>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QTextEdit>


static const char message[] =
    "<p><b>My Coursework</b></p>"
    "<p>The tool bar and dock widgets can be dragged around and rearranged using the mouse.</p>";

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
    setWindowTitle("My Power Point");

    QTextEdit *center = new QTextEdit(this);
    center->setReadOnly(true);
    center->setMinimumSize(400, 205);
    setCentralWidget(center);

    setupMenuBar();
    setupDockWidgets();
    statusBar()->showMessage(tr("Status Bar"));
}

void MainWindow::setupMenuBar()
{
    QMenu *menu = menuBar()->addMenu(tr("&File"));

    menu->addAction(tr("Save layout"), this, &MainWindow::saveLayout);
    menu->addAction(tr("&Quit"), this, &QWidget::close);

    mainWindowMenu = menuBar()->addMenu(tr("Main window"));
    mainWindowMenu = menuBar()->addMenu(tr("Tool bars"));
    dockWidgetMenu = menuBar()->addMenu(tr("&Dock Widgets"));

    QMenu *aboutMenu = menuBar()->addMenu(tr("About"));
    QAction *aboutAct = aboutMenu->addAction(tr("&About"), this, &MainWindow::about);
    aboutAct->setStatusTip(tr("Show the application's About box"));

    QAction *aboutQtAct = aboutMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
}

void MainWindow::saveLayout()
{
    QString fileName
        = QFileDialog::getSaveFileName(this, tr("Save layout"));
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly)) {
        QString msg = tr("Failed to open %1\n%2")
                        .arg(QDir::toNativeSeparators(fileName), file.errorString());
        QMessageBox::warning(this, tr("Error"), msg);
        return;
    }

    QByteArray geo_data = saveGeometry();
    QByteArray layout_data = saveState();

    bool ok = file.putChar((uchar)geo_data.size());
    if (ok)
        ok = file.write(geo_data) == geo_data.size();
    if (ok)
        ok = file.write(layout_data) == layout_data.size();

    if (!ok) {
        QString msg = tr("Error writing to %1\n%2")
                        .arg(QDir::toNativeSeparators(fileName), file.errorString());
        QMessageBox::warning(this, tr("Error"), msg);
        return;
    }
}

void MainWindow::setupDockWidgets()
{
    struct Set {
        const char * name;
        Qt::DockWidgetArea area;
    };

    static const Set sets [] = {
        { "File Explorer", Qt::LeftDockWidgetArea },
        { "Slide Info", Qt::RightDockWidgetArea },
        { "Text Tools", Qt::TopDockWidgetArea },
        { "Main Tools", Qt::TopDockWidgetArea },
        { "Slides", Qt::BottomDockWidgetArea }
    };

    const int setCount = sizeof(sets) / sizeof(Set);

    for (int i = 0; i < setCount; ++i) {
        ColorSwatch *swatch = new ColorSwatch(tr(sets[i].name), this, Qt::WindowFlags());

        QString name = QString::fromLatin1(sets[i].name);
        addDockWidget(sets[i].area, swatch);
        dockWidgetMenu->addMenu(swatch->colorSwatchMenu());
    }

    destroyDockWidgetMenu = new QMenu(tr("Destroy dock widget"), this);
    destroyDockWidgetMenu->setEnabled(false);
    connect(destroyDockWidgetMenu, &QMenu::triggered, this, &MainWindow::destroyDockWidget);

    dockWidgetMenu->addSeparator();
    dockWidgetMenu->addAction(tr("Add dock widget"), this, &MainWindow::createDockWidget);
    dockWidgetMenu->addMenu(destroyDockWidgetMenu);
}

class CreateDockWidgetDialog : public QDialog
{
public:
    explicit CreateDockWidgetDialog(QWidget *parent = nullptr);

    QString enteredObjectName() const { return m_objectName->text(); }
    Qt::DockWidgetArea location() const;

private:
    QLineEdit *m_objectName;
    QComboBox *m_location;
};

/// Create Dock Widget
CreateDockWidgetDialog::CreateDockWidgetDialog(QWidget *parent)
    : QDialog(parent)
    , m_objectName(new QLineEdit(this))
    , m_location(new QComboBox(this))
{
    setWindowTitle(tr("Add Dock Widget"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    QGridLayout *layout = new QGridLayout(this);

    layout->addWidget(new QLabel(tr("Object name:")), 0, 0);
    layout->addWidget(m_objectName, 0, 1);

    layout->addWidget(new QLabel(tr("Location:")), 1, 0);
    m_location->setEditable(false);
    m_location->addItem(tr("Top"));
    m_location->addItem(tr("Left"));
    m_location->addItem(tr("Right"));
    m_location->addItem(tr("Bottom"));
    m_location->addItem(tr("Restore"));
    layout->addWidget(m_location, 1, 1);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    layout->addWidget(buttonBox, 2, 0, 1, 2);
}

Qt::DockWidgetArea CreateDockWidgetDialog::location() const
{
    switch (m_location->currentIndex()) {
        case 0: return Qt::TopDockWidgetArea;
        case 1: return Qt::LeftDockWidgetArea;
        case 2: return Qt::RightDockWidgetArea;
        case 3: return Qt::BottomDockWidgetArea;
        default:
            break;
    }
    return Qt::NoDockWidgetArea;
}

void MainWindow::createDockWidget()
{
    CreateDockWidgetDialog dialog(this);
    if (dialog.exec() == QDialog::Rejected)
        return;

    QDockWidget *dw = new QDockWidget;
    const QString name = dialog.enteredObjectName();
    dw->setObjectName(name);
    dw->setWindowTitle(name);
    dw->setWidget(new QTextEdit);

    Qt::DockWidgetArea area = dialog.location();
    switch (area) {
        case Qt::LeftDockWidgetArea:
        case Qt::RightDockWidgetArea:
        case Qt::TopDockWidgetArea:
        case Qt::BottomDockWidgetArea:
            addDockWidget(area, dw);
            break;
        default:
            if (!restoreDockWidget(dw)) {
                QMessageBox::warning(this, QString(), tr("Failed to restore dock widget"));
                delete dw;
                return;
            }
            break;
    }

    extraDockWidgets.append(dw);
    destroyDockWidgetMenu->setEnabled(true);
    destroyDockWidgetMenu->addAction(new QAction(name, this));
}

void MainWindow::destroyDockWidget(QAction *action)
{
    int index = destroyDockWidgetMenu->actions().indexOf(action);
    delete extraDockWidgets.takeAt(index);
    destroyDockWidgetMenu->removeAction(action);
    action->deleteLater();

    if (destroyDockWidgetMenu->isEmpty())
        destroyDockWidgetMenu->setEnabled(false);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About MainWindows"), message);
}
