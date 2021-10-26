#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix("/Users/ekaterinalapina/Desktop/hanger1.jpg"); //path for the picture
    ui->label_pic->setPixmap(pix);

    if (!windOpen())
        ui->label1->setText("File failed to open the data");
    else
        ui->label1->setText("Connected..");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString day, item;
    day = ui->lineEdit_day->text();
    item = ui->lineEdit_item->text();

    if (!windOpen())
    {
        qDebug()<< "File failed to open the data";
        return;
    }

    windOpen(); //opening the connection
    QSqlQuery qry;
    qry.prepare("select * from store where Day= '"+day+"' and Type_of_product= '"+item+"'");

    if (qry.exec())
    {
        int count = 0;
        while (qry.next())
        {
            ++count;
        }
        if (count==1)
        {
            ui->label1->setText("day and item are correct");
            windClose(); //close the connection with database
            this->hide();
            StoreWindow storewindow; //if pass correct we are opening the second window
            storewindow.setModal(true);
            storewindow.exec();
        }
        if (count>1)
            ui->label1->setText("Dublicate day and item");
        if (count<1)
            ui->label1->setText("day and item are not correct");

    }
}

