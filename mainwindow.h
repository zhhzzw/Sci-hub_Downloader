#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);\
    ~MainWindow();

private slots:
    void on_Download_clicked();
    void slot_replayFinished(QNetworkReply *reply);
    void slot_DOIFinished(QNetworkReply *reply);
    void on_Download_2_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
};

#endif // MAINWINDOW_H
