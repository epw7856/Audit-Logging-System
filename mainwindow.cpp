#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindowcontroller.h"
#include "auditlogentry.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mainWindowController(std::make_shared<MainWindowController>())
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_debugButton_clicked()
{
    mainWindowController->logDebugMsg();
}

void MainWindow::on_infoButton_clicked()
{
    mainWindowController->logInfoMsg();
}

void MainWindow::on_warningButton_clicked()
{
    mainWindowController->logWarningMsg();
}

void MainWindow::on_criticalButton_clicked()
{
    mainWindowController->logCriticalMsg();
}

void MainWindow::on_fatalButton_clicked()
{
    mainWindowController->logFatalMsg();
}
