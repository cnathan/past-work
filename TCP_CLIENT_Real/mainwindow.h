#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdlib.h>
#include <stdio.h>
#include <QtNetwork/QTcpSocket>
#include <QAbstractSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <time.h>
#include "ui_mainwindow.h"

#define SERVERPORT		6070
#define SERVERPORT2		6075

#define MAXPKT        250       // max number of packets
#define PSIZE         1000       // size of packet
#define NAME	      20

//namespace Ui {
//    class MainWindow;
//}

class MainWindow : public QMainWindow, private Ui::MainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTcpSocket tcpSocket;
    char    input[PSIZE-NAME];
    char   name[NAME];
    char    SndPkt[PSIZE-NAME];
    int     bytes_recv;
protected:
    void changeEvent(QEvent *e);

private slots:
    void ConnectClicked();
    void addtext();
    void SendClicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

