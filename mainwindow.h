#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <memory>

namespace Ui {
class MainWindow;
}

class MainWindowController;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_debugButton_clicked();

    void on_infoButton_clicked();

    void on_warningButton_clicked();

    void on_criticalButton_clicked();

    void on_fatalButton_clicked();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<MainWindowController> mainWindowController = nullptr;
};

#endif // MAINWINDOW_H
