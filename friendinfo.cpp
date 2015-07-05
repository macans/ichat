#include "friendinfo.h"
#include "ui_friendinfo.h"
#include "QMessageBox"
#include "QFileDialog"
#include <QMouseEvent>
#include <QJsonArray>
#include <QJsonObject>
#include <QScriptEngine>
#include <QScriptValueIterator>

FriendInfo::FriendInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FriendInfo)
{

    ui->setupUi(this);
       //设置窗口不可拉伸
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());


    manager = new QNetworkAccessManager(this);  //获取信息的manager
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)),
               this, SLOT(finishedSlot(QNetworkReply*)));

      QUrl url("http://182.92.69.19/ichat-server/public/user/get-info");
      QByteArray append("account=66666");

      QNetworkReply* reply = manager->post(QNetworkRequest(url),append);

     //为下拉列表提供选项
      int month;
     for(int year=1900;year<=2015;year++){
         ui->YearCombo->addItem(QString::number(year));
     }

     for(month=1;month<=12;month++){
         ui->MonthCombo->addItem(QString::number(month));
     }

     if(month==0||month==2||month==4||month==6||month==7||month==9||month==11){
     for(int date=1;date<=31;date++){
         ui->DateCombo->addItem(QString::number(date));
     }
         }
     else if(month==1){
         for(int date=1;date<=28;date++){
             ui->DateCombo->addItem(QString::number(date));
         }
     }
     else {
         for(int date=1;date<=30;date++){
             ui->DateCombo->addItem(QString::number(date));
     }
         }

     hp<<"海南"<<"湖南";
     hc1<<"海口"<<"三亚";
     hc2<<"长沙"<<"岳阳";
     ha1<<"琼山"<<"府城";
     ha2<<"南山"<<"亚龙";
     ha3<<"岳麓"<<"雨花";
     ha4<<"君山"<<"岳楼";

     lp<<"湖北"<<"山东";
     lc1<<"武汉"<<"襄阳";
     lc2<<"济南"<<"青岛";
     la1<<"洪山"<<"武昌";
     la2<<"襄城"<<"樊城";
     la3<<"章丘"<<"历下";
     la4<<"崂山"<<"黄岛";

     ui->HomeP->addItems(hp);
     ui->HomeC->addItems(hc1);
     ui->HomeL->addItems(ha1);
     ui->LocalP->addItems(lp);
     ui->LocalC->addItems(lc1);
     ui->LocalL->addItems(la1);

     ui->SexCombo->addItem("FeMale");
     ui->SexCombo->addItem("Male");

    //设置为只读，并不可改
     ui->SignEdit->setReadOnly(true);
     ui->NameEdit->setReadOnly(true);
     ui->AgeEdit->setReadOnly(true);
     ui->SexCombo->setEnabled(false);
     ui->PhoneEdit->setReadOnly(true);
     ui->HomeP->setEnabled(false);
     ui->HomeC->setEnabled(false);
     ui->HomeL->setEnabled(false);
     ui->LocalP->setEnabled(false);
     ui->LocalC->setEnabled(false);
     ui->LocalL->setEnabled(false);
//    ui->SchoolEdit->setReadOnly(true);
     ui->YearCombo->setEnabled(false);
     ui->MonthCombo->setEnabled(false);
     ui->DateCombo->setEnabled(false);
}

FriendInfo::~FriendInfo()
{
    delete ui;
}

void FriendInfo::finishedSlot(QNetworkReply *reply)
{
    int i=0;
    QString usrInfo[20];
    //从服务器端获取信息
    QVariant vRes = reply->readAll();
    QString res = vRes.toString();
    QScriptValue sc;
        QScriptEngine engine;
        sc = engine.evaluate("value = " + res);
        QScriptValueIterator it(sc);
        while(it.hasNext()){
            it.next();
            QString id = it.name();
            QString value = it.value().toString();
            usrInfo[i]=value;
            i++;
     }

        //显示在资料卡上
    ui->AccountList->setText(usrInfo[1]);   //账号
    ui->NameEdit->setText(usrInfo[2]);   //昵称
    //ui->FaceButton
    ui->SignEdit->setText(usrInfo[4]);     //签名
    ui->lvLabel->setText(usrInfo[5]);       //等级
    ui->SexCombo->setCurrentIndex(usrInfo[6].toInt());   //性别
    ui->AgeEdit->setText(usrInfo[7]);      //年龄
    ui->PhoneEdit->setText(usrInfo[8]);    //电话
    int home,homeP,homeC,homeL,local,localP,localC,localL,homePx,homePy,localPx,localPy;
    home = usrInfo[9].toInt();
    homeP=home/100;
    homePx=home-homeP*100;
    homeC=homePx/10;
    homePy=homePx-homeC*10;
    homeL=homePy;
    local = usrInfo[10].toInt();
    localP=local/100;
    localPx=local-localP*100;
    localC=localPx/10;
    localPy=localPx-localC*10;
    localL=localPy;
    ui->HomeP->setCurrentIndex(homeP);      //故乡
    ui->LocalP->setCurrentIndex(localP);    //所在地
   if(ui->HomeP->currentText()=="海南"){
       ui->HomeC->clear();
       ui->HomeC->addItems(hc1);
       ui->HomeC->setCurrentIndex(homeC);
       if(ui->HomeC->currentText()=="海口"){
           ui->HomeL->clear();
           ui->HomeL->addItems(ha1);
           ui->HomeL->setCurrentIndex(homeL);
       }
       else if(ui->HomeC->currentText()=="三亚"){
           ui->HomeL->clear();
           ui->HomeL->addItems(ha2);
           ui->HomeL->setCurrentIndex(homeL);
       }
    }

   else if(ui->HomeP->currentText()=="湖南"){
       ui->HomeC->clear();
       ui->HomeC->addItems(hc2);
        ui->HomeC->setCurrentIndex(homeC);
        if(ui->HomeC->currentText()=="长沙"){
            ui->HomeL->clear();
            ui->HomeL->addItems(ha3);
            ui->HomeL->setCurrentIndex(homeL);
        }
        else if(ui->HomeC->currentText()=="岳阳"){
            ui->HomeL->clear();
            ui->HomeL->addItems(ha4);
            ui->HomeL->setCurrentIndex(homeL);
        }
   }

   if(ui->LocalP->currentText()=="湖北"){
       ui->LocalC->clear();
       ui->LocalC->addItems(lc1);
       ui->LocalC->setCurrentIndex(localC);
       if(ui->LocalC->currentText()=="武汉"){
           ui->LocalL->clear();
           ui->LocalL->addItems(la1);
           ui->LocalL->setCurrentIndex(localL);
       }
       else if(ui->LocalC->currentText()=="襄阳"){
           ui->LocalL->clear();
           ui->LocalL->addItems(la2);
           ui->LocalL->setCurrentIndex(localL);
       }
    }

   else if(ui->LocalP->currentText()=="山东"){
       ui->LocalC->clear();
       ui->LocalC->addItems(lc2);
       ui->LocalC->setCurrentIndex(localC);
       if(ui->LocalC->currentText()=="济南"){
           ui->LocalL->clear();
           ui->LocalL->addItems(la3);
           ui->LocalL->setCurrentIndex(localL);
       }
       else if(ui->LocalC->currentText()=="青岛"){
           ui->LocalL->clear();
           ui->LocalL->addItems(la4);
           ui->LocalL->setCurrentIndex(localL);
       }
    }

   QStringList birthlist = usrInfo[11].split("-"); //生日
   ui->YearCombo->setCurrentIndex(birthlist[0].toInt()-1900);
   ui->MonthCombo->setCurrentIndex((birthlist[1].toInt())-1);
   ui->DateCombo->setCurrentIndex((birthlist[2].toInt())-1);
}

void FriendInfo::on_ConfirmButton_clicked()
{
    this->close();
}