#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include "window.h"
//#include "ui_window.h"

#include <QApplication>
#include <QMessageBox>
#include <QTime>
#include <QTimer>
#include <QVariant>
#include <QFontComboBox>
#include <QCloseEvent>

QString MainWindow::settingsKeyForPaths = "directory";
QString MainWindow::settingsKeyForWorkDirPath = "workdirectory";
QString MainWindow::settingsKeyForSaveDirPath = "savedirectory";

QString MainWindow::settingsKeyGeneralSettings = "general";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //----------------------------------------------------------
        // Das komplette Menü zum Hauptprogramm
            QMenu *fileMenu = new QMenu(tr("&File"), this);
            menuBar()->addMenu(fileMenu);
            act3 = fileMenu->addAction(
                        QIcon(QString("%1%2").arg(QCoreApplication::applicationDirPath()).arg("/images/cancel.png"))   ,
                        tr("Quit"),
               qApp, SLOT(quit()),
               QKeySequence(tr("Ctrl+Q", "File|Quit")) );
            act3->setStatusTip(tr("Quit Program"));
            QMenu *workMenu = new QMenu(
               tr("&Edit"), this);
            menuBar()->addMenu(workMenu);
    //--------------------------------------------------------

    //Verbinde Ereignis mit Methode
    connect (ui->pushConfirm, SIGNAL(clicked()), SLOT(pushConfirmClicked()));
    connect (ui->pushSecondInterface, SIGNAL(clicked(bool)), SLOT(on_pushSecondInterface_clicked()));

}

MainWindow::~MainWindow()
{
    delete ui;


}


// Kontextmenü verwenden contextMenuEvent
// ist eine virtuelle Methode
void MainWindow::contextMenuEvent(
    QContextMenuEvent *event) {
   QMenu *menu = new QMenu(this);
   //menu->addAction(act1);
   //menu->addAction(act2);
   menu->addAction(act3);

   menu->exec(event->globalPos());
}


void MainWindow::pushConfirmClicked(){
/*
    //Model approach (dealing with stack memory)
    StackedWindow stkwindow;    //creat object stackedwindow
    stkwindow.setModal(true);   //use object to open second window
    stkwindow.exec();           //show second window
*/


    //Model less approach (dealing with heap memory)


}


void MainWindow::on_pushSecondInterface_clicked()
{
    /*
    //Model approach (dealing with stack memory)
    Window window;    //creat object stackedwindow
    window.setModal(false);   //use object to open second window
    window.exec();           //show second window
    //window.show();
    */

    Window *window = new Window();
    window->show();
}
