#include "configwindow.h"
#include "ui_configwindow.h"

configwindow::configwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::configwindow)
{
    ui->setupUi(this);

}

void configwindow::init(QString pandoc, QString latexdiff){
    if(!pandoc.isEmpty()){
        ui->txtPandoc->setText(pandoc);
    }

    if(!latexdiff.isEmpty()){
        ui->txtDiff->setText(latexdiff);
    }
}

void configwindow::accept(){


    this->close();


}

QMap<QString, QString> configwindow::sendData(){
    //QSettings sample;
    //return sample;
    QMap<QString, QString> uData;

    uData["pandoc"] = ui->txtPandoc->text();
    uData["latexdiff"] = ui->txtDiff->text();

    return uData;
}



configwindow::~configwindow()
{
    delete ui;
}
