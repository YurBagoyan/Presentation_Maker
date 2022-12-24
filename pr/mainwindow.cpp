#include "mainwindow.h"
#include "ui_mainwindow.h"


#include<QFileDialog>
#include <QMessageBox>

#include <QTextEdit>
//#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Temp solution
    QTextEdit *center = new QTextEdit(this);
    center->setReadOnly(true);
    center->setMinimumSize(200, 200);
    setCentralWidget(center);


    CreateToolBar();
    SetupDockWidgets();


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::CreateToolBar()
{
    fileToolBar = new ToolBar("&File", this);
    fileToolBar->addAction(ui->actionNew_Project);
    fileToolBar->addAction(ui->actionOpen_Project);
    fileToolBar->addAction(ui->actionSave_Project);

    editToolBar = new ToolBar("&Edit", this);
    editToolBar->addAction(ui->actionCut);
    editToolBar->addAction(ui->actionCopy);
    editToolBar->addAction(ui->actionPaste);
    editToolBar->addSeparator();
    editToolBar->addAction(ui->actionDelete_Item);
    editToolBar->addAction(ui->actionBring_To_Front);
    editToolBar->addAction(ui->actionSend_Item_To_Back);


    addToolBar(fileToolBar);
    addToolBar(editToolBar);

    ui->menuTool_bars->addMenu(fileToolBar->toolbarMenu());
    ui->menuTool_bars->addMenu(editToolBar->toolbarMenu());
}

void MainWindow::SetupDockWidgets()
{
    static const struct Set {
        const char * name;
        Qt::DockWidgetArea area;
    } sets [] = {
        { "Slides", Qt::BottomDockWidgetArea },
        { "Options", Qt::RightDockWidgetArea },
        { "Basic Shapes", Qt::LeftDockWidgetArea}
    };

    const int setCount = sizeof(sets) / sizeof(Set);
    for (int i = 0; i < setCount; ++i) {
        slidesWidget = new DockWidget(sets[i].name, this);
        addDockWidget(sets[i].area, slidesWidget);

        ui->menuDock_Widgets->addMenu(slidesWidget->DockWidgetMenu());
    }
}

/// Slots
void MainWindow::on_actionAbout_QT_triggered()
{
    QApplication::aboutQt();
}

void MainWindow::on_actionSave_Project_triggered()
{
    QString fileName
        = QFileDialog::getSaveFileName(this, tr("Save Project"));

    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly)) {
        QString msg = tr("Failed to open %1\n%2")
                        .arg(QDir::toNativeSeparators(fileName), file.errorString());
        QMessageBox::warning(this, tr("Error"), msg);
        return;
    }
}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About Presentation maker"),
             tr("The <b>Presentation maker</b> is course project for Synopsys Armenia."));
}

void MainWindow::on_actionPrint_triggered()
{

}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::closeAllWindows();
}

void MainWindow::on_actionDelete_Item_triggered()
{

}


