#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMouseEvent>
#include <QFrame>
#include "QPushButton"
#include "QPropertyAnimation"
#include "msgnode.h"
#include <QUdpSocket>
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QAudioInput>
#include <QTimer>
#include <QAudioOutput>
#include "QTcpSocket"
#include "QNetworkReply"
#include "QNetworkRequest"
#include "chatmsgdlg.h"

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QFrame
{
    Q_OBJECT
private:
     QUdpSocket *sendUdpSocket;
     QString selfAccount;
     QString contactAccount;
     QString myName;     //自己昵称
     QString friName;    //好友昵称
    //QTcpServer *tcpServer;
public:
    QString getContactAccount();
    explicit ChatWindow(QString selfAccount, QString contactAccount,QString myName, QString contactName,QWidget *parent = 0);
    ~ChatWindow();
    QPropertyAnimation *m_animation;
    void imgPathToHtml(QString &path);
    void ShakeAnimation();
    QPushButton *custButton(QString str);
    QString picbath;
    QString myHead;     //用于存放自己的头像
    QString friHead;    //用于存放好友的头像
private:
    Ui::ChatWindow *ui;
    QFile outputFile;
    QAudioInput *audio;
    QFile inputFile;
    QFile *audioReceive;
    QString fileReceive;
    QAudioOutput *audio2;
private slots:
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_listenButton_clicked();
    void readBackData();

public:
    void sendTextMessage(QString content);
    void receiveMessage(QVector<MsgNode> messages);
    void receiveAudio(QFile *file);
    void receiveFile(QString filename);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
private slots:
    void on_pushButton_6_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();
    void finishedPlaying(QAudio::State);
    void startTransfer();
    void updateClientProgress(qint64); //发送数据，更新进度条
    void displayError(QAbstractSocket::SocketError); //显示错误
    void on_faceButton_clicked();
    void finishedSlot(QNetworkReply*);
    void on_minButton_clicked();
    void on_closeButton_clicked();
    void sendAudio();
    void sendError(QAbstractSocket::SocketError);

    void on_downCloseBtn_clicked();

    void on_sendButton_clicked();

    void on_pushButton_7_clicked();


    void on_fileButton_clicked();

private:
    QTcpSocket *tcpClient;
    QFile *localFile;
    qint64 totalBytes;  //数据总大小
    qint64 bytesWritten;  //已经发送数据大小
    qint64 bytesToWrite;   //剩余数据大小
    qint64 loadSize;   //每次发送数据的大小
    QString fileName;  //保存文件路径
    QByteArray fileType;
    QByteArray outBlock;
    QString friIp;      //存放好友ip
    int friPort;        //存放端口
    QNetworkAccessManager *manager1;
    QPoint dragPosition;
    QTcpSocket *tcpAudio;
    QString audioName;
    QFile *audioFile;
    qint64 totalAudio;  //录音数据总大小
    qint64 unfinished;  //剩余数据
    QByteArray audioOutblock;
    bool msgFlag;
public:
    chatMsgDlg *msgDlg;
};

#endif // CHATWINDOW_H
