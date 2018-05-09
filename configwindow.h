#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QDialog>
#include <QStringList>

namespace Ui {
class configwindow;
}

class configwindow : public QDialog
{
    Q_OBJECT

public:
    explicit configwindow(QWidget *parent = 0);
    ~configwindow();
    QMap<QString,QString> sendData();
    void init(QString, QString);

private slots:
    void accept();



private:
    Ui::configwindow *ui;

};

#endif // CONFIGWINDOW_H
