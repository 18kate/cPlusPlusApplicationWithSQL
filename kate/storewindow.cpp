#include "storewindow.h"
#include "ui_storewindow.h"
#include "QMessageBox"

StoreWindow::StoreWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StoreWindow)
{
    ui->setupUi(this);
    if (!windOpen())
        ui->label_secondstatus->setText("File failed to open the data");
    else
        ui->label_secondstatus->setText("Connected..");
}
QSqlDatabase file;
StoreWindow::~StoreWindow()
{
    delete ui;
}
bool windClose()
{
    file.close();
    file.removeDatabase(QSqlDatabase::defaultConnection); //removing class QSqlDatabase
}
bool windOpen()
{
    file=QSqlDatabase::addDatabase("QSQLITE"); //created the connection
    file.setDatabaseName("/Users/ekaterinalapina/Desktop/sqlite.db");

    if (!file.open())
    {
        qDebug()<<("File failed to open the data");
        return false;
    }
    else
    {
        qDebug()<<("Connected..");
        return true;
    }
}

void StoreWindow::on_pushButton_clicked() //similar to the first button
{
    QString id, type, day,pp,sp,disc,isold,iperc;
    id = ui->txt_id->text();
    type = ui->txt_type->text();
    day = ui->txt_day->text();
    pp = ui->txt_pp->text();
    sp = ui->txt_sp->text();
    disc = ui->txt_disc->text();
    isold = ui->txt_isold->text();
    iperc = ui->txt_iperc->text();

    if (!windOpen())
    {
        qDebug()<< "File failed to open the data";
        return;
    }
    windOpen(); //opening the connection
    QSqlQuery qry;
    qry.prepare("insert into store (id,Type_of_product,Day,Purchase_price,Selling_price,Discount_price,Items_sold,Items_purchased) values('"+id+"','"+type+"','"+day+"','"+pp+"','"+sp+"','"+disc+"','"+isold+"','"+iperc+"')");

    if (qry.exec())
    {
        QMessageBox::critical(this,tr("INFO"),tr("Data is saved"));
        windClose(); //everything is ok=> we close the connection with the database
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }
}


void StoreWindow::on_pushButton_2_clicked()
{
    MainWindow wind; // need this object of mainwindow class for open/close functions
    QString id, type, day,pp,sp,disc,isold,iperc;
    id = ui->txt_id->text();
    type = ui->txt_type->text();
    day = ui->txt_day->text();
    pp = ui->txt_pp->text();
    sp = ui->txt_sp->text();
    disc = ui->txt_disc->text();
    isold = ui->txt_isold->text();
    iperc = ui->txt_iperc->text();

    if (!windOpen())
    {
        qDebug()<< "File failed to open the data";
        return;
    }
    windOpen(); //opening the connection
    QSqlQuery qry;
    qry.prepare("update store set id='"+id+"',Type_of_product='"+type+"',Purchase_price='"+pp+"',Selling_price='"+sp+"',Discount_price='"+disc+"',Items_sold='"+isold+"',Items_purchased='"+iperc+"' where id='"+id+"' ");

    if (qry.exec())
    {
        QMessageBox::critical(this,tr("INFO"),tr("Data is updated"));
        windClose(); //everything is ok=> we close the connection with the database
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }
}


void StoreWindow::on_pushButton_3_clicked()
{
    QString id, type, day,pp,sp,disc,isold,iperc;
    id = ui->txt_id->text();
    type = ui->txt_type->text();
    day = ui->txt_day->text();
    pp = ui->txt_pp->text();
    sp = ui->txt_sp->text();
    disc = ui->txt_disc->text();
    isold = ui->txt_isold->text();
    iperc = ui->txt_iperc->text();

    if (!windOpen())
    {
        qDebug()<< "File failed to open the data";
        return;
    }
    windOpen(); //opening the connection
    QSqlQuery qry;
    qry.prepare("Delete from store where id='"+id+"' ");

    if (qry.exec())
    {
        QMessageBox::critical(this,tr("INFO"),tr("Data is deleted"));
        windClose(); //everything is ok=> we close the connection with the database
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }
}


void StoreWindow::on_pushButton_4_clicked()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("select* from store");
    windOpen();
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(model);
    proxyModel->setSourceModel(model);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->setModel(proxyModel);
    windClose();
    qDebug() << (model->rowCount());
}


void StoreWindow::on_pushButton_5_clicked()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    windOpen();
    QSqlQuery* qry = new QSqlQuery(file);
    qry-> prepare("select id from store");
    qry->exec();
    model->setQuery(*qry);
    ui->comboBox->setModel(model);
    windClose();
    qDebug() << (model->rowCount());
}


void StoreWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    QString id=ui->comboBox->currentText();
    if (!windOpen())
    {
        qDebug()<< "File failed to open the data";
        return;
    }
    windOpen(); //opening the connection

    QSqlQuery qry;
    qry.prepare("select * from store where id = '"+id+"' ");

    if (qry.exec())
    {
        while(qry.next())
        {
            ui->txt_id-> setText(qry.value(0).toString()); // due to id is a zero column
            ui->txt_type-> setText(qry.value(1).toString());
            ui->txt_day-> setText(qry.value(2).toString());
            ui->txt_pp-> setText(qry.value(3).toString());
            ui->txt_sp-> setText(qry.value(4).toString());
            ui->txt_disc-> setText(qry.value(5).toString());
            ui->txt_isold-> setText(qry.value(6).toString());
            ui->txt_iperc-> setText(qry.value(7).toString());
        }
        windClose(); //everything is ok=> we close the connection with the database
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }
}
