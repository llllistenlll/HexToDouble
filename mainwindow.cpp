#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"qdebug.h"
#include"QString"


using namespace std;

QString ieee754_hex_str_to_float(QByteArray array);
static double toFloat(QString list);   //数组转浮点数
QString ieee754_hex_str_to_double(QByteArray array);
QString change (QString XX);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(on_pushButton_clicked()));
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
   float f=ui->lineEdit_yuanshi_double->text().toFloat();//转换为单浮点型
   uint f_uint = *(uint*)&f;
   QString f_hex = QString("%1").arg(f_uint,4,16,QLatin1Char('0'));
   ui->float_toHEX->setText(f_hex.toUpper());
   QString YY=change(f_hex);
   ui->float_toHEX_->setText(YY.toUpper());



   double d=ui->lineEdit_yuanshi_double->text().toDouble();
   qulonglong d_long = *(qulonglong*)&d;
   QString d_hex = QString("%1").arg(d_long,8,16,QLatin1Char('0'));
   ui->double_toHEX->setText(d_hex.toUpper());
   ui->double_toHEX_->setText(change(d_hex).toUpper());

   QString hex_double =ui->lineEdit_yuanshi_HEX->text();
   QString hex_double_2=ui->lineEdit_yuanshi_HEX_->text();
   if ((hex_double.isEmpty()&&(!hex_double_2.isEmpty()))||((!hex_double.isEmpty())&&(!hex_double_2.isEmpty())))
   {

       QByteArray array_1=change(hex_double_2).toLatin1();
       QString ef=ieee754_hex_str_to_double(array_1);
       ui->lineEdit_todouble->setText(ef.toUpper());
        qDebug()<<ef<<"333333333333333333333333";


       QString gh=ieee754_hex_str_to_float(array_1);
       //double cd=toFloat(hex_double);
       qDebug()<<gh<<"444444444444444444444444989595";
       ui->lineEdit_tofloat->setText(gh.toUpper());
   }

   if ((!hex_double.isEmpty())&&(hex_double_2.isEmpty()))
   {

       QByteArray array=hex_double.toLatin1();
       QString ab=ieee754_hex_str_to_double(array);
       ui->lineEdit_todouble->setText(ab.toUpper());
       qDebug()<<ab<<"11111111111111111111111";


       QString cd=ieee754_hex_str_to_float(array);
       //double cd=toFloat(hex_double);
       qDebug()<<cd<<"222222222226565962222222222222";
       ui->lineEdit_tofloat->setText(cd.toUpper());

   }





}

QString ieee754_hex_str_to_float(QByteArray array)
{
    bool ok;
    int sign = 1;
    //QByteArray array("425AE78F");  输入QByteArray = 42 5A E7 8F;
    array = QByteArray::number(array.toLongLong(&ok,16),2);  //将十六进制数据转换为二进制
    if(array.length()==32) {
        if(array.at(0)=='1')  sign =-1;                       // 如果第0位为1 ，则表示该数为负数；
        array.remove(0,1);                                    // 移除标志位
    }
    QByteArray fraction =array.right(23);   //获取小数部分；
    double mantissa = 0;
    for(int i=0;i<fraction.length();i++)     // 迭代数组，以小数形式计算分数
        if(fraction.at(i)=='1')     mantissa += 1.0/(pow(2,i+1));
    int exponent = array.left(array.length()-23).toLongLong(&ok,2)-127;     //计算指数位；

    QString calcu_Data = QString::number( sign*pow(2,exponent)*(mantissa+1.0),'f', 6);
    qDebug() << "number= "<< QString::number( sign*pow(2,exponent)*(mantissa+1.0),'f', 6);

    // 输出单精度浮点数据 number = 54.72613
    return calcu_Data;

}

QString ieee754_hex_str_to_double(QByteArray array)
{
    bool ok;
    int sign = 1;

    array = QByteArray::number(array.toLongLong(&ok,16),2);  //将十六进制数据转换为二进制
    qDebug()<<array;
    if(array.length()==64) {
        if(array.at(0)=='1')  sign =-1;                       // 如果第0位为1 ，则表示该数为负数；
        array.remove(0,1);                                    // 移除标志位
    }
    QByteArray fraction =array.right(52);   //获取小数部分；
    double mantissa = 0;
    for(int i=0;i<fraction.length();i++)     // 迭代数组，以小数形式计算分数
        if(fraction.at(i)=='1')     mantissa += 1.0/(pow(2,i+1));
    int exponent = array.left(array.length()-52).toLongLong(&ok,2)-1023;     //计算指数位；

    QString calcu_Data = QString::number( sign*pow(2,exponent)*(mantissa+1.0),'f', 8);
    qDebug() << "number= "<< QString::number( sign*pow(2,exponent)*(mantissa+1.0),'f', 8);

    // 输出单精度浮点数据 number = 54.72613
    return calcu_Data;

}

QString change (QString XX)
{
    QString YY="";
    int len=XX.size();
    int i;

    for(i=len;i>1;i=i-2)
    {

        YY= YY+XX.right(2);
        XX.remove(i-2,2);

    }
    qDebug()<<YY;
    return YY;

}

void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit_todouble->clear();
    ui->lineEdit_tofloat ->clear();
    ui->lineEdit_yuanshi_double->clear();
    ui->lineEdit_yuanshi_HEX ->clear();
    ui->lineEdit_yuanshi_HEX_ ->clear();
    ui->double_toHEX->clear();
    ui->double_toHEX_->clear();
    ui->float_toHEX->clear();
    ui->float_toHEX_->clear();
}

