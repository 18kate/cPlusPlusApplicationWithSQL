#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <storewindow.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase file;

    void windClose()
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

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(); //это родитель нового виджета. Если равно 0, то новый виджет будет окном

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
