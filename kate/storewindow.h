#ifndef STOREWINDOW_H
#define STOREWINDOW_H

#include <QDialog>
#include "mainwindow.h"
namespace Ui
{
class StoreWindow;
}

class StoreWindow : public QDialog
{
    Q_OBJECT

public:

    explicit StoreWindow(QWidget *parent = nullptr);
    ~StoreWindow();

    QSqlDatabase file;
    void windClose();

    bool windOpen();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);


private:
    Ui::StoreWindow *ui;
};

#endif // STOREWINDOW_H
