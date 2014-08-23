#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    connect(Connect, SIGNAL(clicked()),this , SLOT(ConnectClicked()));
    connect(Send, SIGNAL(clicked()), this, SLOT(SendClicked()));
    connect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(addtext()));
}

MainWindow::~MainWindow()
{
//    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}
void MainWindow::SendClicked()
{
        time_t rawtime;
        struct tm * timeinfo;
        char timesent [12];
        QString tmpStr = insert->text();
        strcpy(input,tmpStr.toAscii().data());
        time (&rawtime);
        timeinfo = localtime (&rawtime);
        strftime(timesent,12,"%I:%M:%S%p",timeinfo);
        SndPkt[0]='\0';
        strcat(SndPkt,name);
        strcat(SndPkt,"(");
        strcat(SndPkt,timesent);
        strcat(SndPkt,")- ");
        strcat(SndPkt,input);
        tcpSocket.write(SndPkt,strlen(SndPkt));
        insert->setText("");    // erase the text from the box they typed in
        insert->setFocus();    // set the focus back to the LineEdit from the button
}
void MainWindow::ConnectClicked()
{
        int port = SERVERPORT;
        QString tmpStr = IP_ADDRESS->text();
        QString tmpStr2 = UserName->text();
        strcpy(name,tmpStr2.toAscii().data());
        tcpSocket.connectToHost(tmpStr,port);
        Send->setEnabled(1);
        insert->setEnabled(1);
        list->setEnabled(1);
        SndPkt[0]='\0';
        strcat(SndPkt,name);
        strcat(SndPkt," has joined the chat");
        tcpSocket.write(SndPkt,strlen(SndPkt));
}
void MainWindow::addtext()
{
    time_t rawtime;
    struct tm * timeinfo;
    char timerec [12];
    char RcvPkt[PSIZE] = {0};
    char data[PSIZE+50]={0};
    bytes_recv=tcpSocket.read(RcvPkt, tcpSocket.bytesAvailable());
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime(timerec,12,"%I:%M:%S%p",timeinfo);
    sprintf(data,"%d",bytes_recv);
    strcat(data," bytes Reveived (");
    strcat(data,timerec);
    strcat(data,"): ");
    strcat(data,RcvPkt);
    list->addItem(data);
    list->scrollToBottom();
    Connect->setEnabled(0);
    UserName->setEnabled(0);
    IP_ADDRESS->setEnabled(0);
}
