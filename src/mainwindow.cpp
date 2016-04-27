#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stackedwindow.h"
#include "ui_stackedwindow.h"

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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //-----------------------------Menüleiste------------------------------------------
    //Menüleiste für Hauptfenster (&Datei)
    QMenu *fileMenu = new QMenu(tr("&Datei"),this);
    menuBar()->addMenu(fileMenu);
    fileMenu->addSeparator();   //Menü mit linie
        act2 = fileMenu->addAction(
            QIcon(QString("%1%2").arg(QCoreApplication::applicationDirPath()).arg("/images/cancel.png"))   ,
             tr("Be&enden"),
                    qApp, SLOT(quit()),
           QKeySequence(tr("Ctrl+E", "Datei|Beenden")) );
        act2->setStatusTip(tr("Programm beenden"));

   //Menüleiste für Hauptfenster (&Bearbeiten)
    QMenu *workMenu = new QMenu(tr("&Bearbeiten"), this);
    menuBar()->addMenu(workMenu);
        act4 = workMenu->addAction(
               tr("&Suchen"), this, SLOT(search()),
               QKeySequence(tr("Ctrl+S", "Bearbeiten|Suchen")));
        act4->setStatusTip(
               tr("Nach einer Stringfolge suchen") );
            // Menü mit Linie von der Leiste Abnehmbar
            fileMenu->setSeparatorsCollapsible(true);
   //----------------------------Menüleiste Ende!--------------------------------------------

    //Verbinde Ereignis mit Methode
    connect (ui->pushConfirm, SIGNAL(clicked()), SLOT(pushConfirmClicked()));
    connect (ui->pushSecondInterface, SIGNAL(clicked(bool)), SLOT(on_pushSecondInterface_clicked()));

}

MainWindow::~MainWindow()
{
    delete ui;


}
//-----------------------------Menüleiste------------------------------------------
// Im Editor nach einer bestimmten Textfolge suchen
void MainWindow::search( ) {
  bool ok;
  QString text = QInputDialog::getText(
     this, "Suchdialog", "Text zur Suche eingeben :",
     QLineEdit::Normal, "Suche eingeben", &ok );
  // Einen einfachen Fortschrittsbalken zur Suche
  // in der Statusleiste simulieren
  QProgressBar* pbar = new QProgressBar;
  // min. und max. Werte festlegen
  pbar->setRange( 0, 500 );
  statusBar()->addWidget(pbar);
  for (int i = 0; i < 500; i++) {
     pbar->setValue(i);
     for( int j=0; j < 12345678; ++j);
        //... copy one file
     }
  pbar->setValue(500);
  statusBar()->removeWidget(pbar);
  if (ok && !text.isEmpty())
     editor->find(text);
  statusBar()->showMessage(tr("Suche beendet"), 3000);
}
 //----------------------------Menüleiste Ende!--------------------------------------------

// Kontextmenü verwenden contextMenuEvent
// ist eine virtuelle Methode
void MainWindow::contextMenuEvent(
    QContextMenuEvent *event) {
   QMenu *menu = new QMenu(this);
   //menu->addAction(act1);
   menu->addAction(act2);

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
    stackedwin = new StackedWindow(this);
    stackedwin->show();
    ui->pushConfirm->setVisible(false);



}


void MainWindow::on_pushSecondInterface_clicked()
{
    //Model approach (dealing with stack memory)
    Window window;    //creat object stackedwindow
    window.setModal(true);   //use object to open second window
    window.exec();           //show second window
}
