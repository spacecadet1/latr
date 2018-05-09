#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <string>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnLatexSouorce,SIGNAL(clicked(bool)),
            this, SLOT(selectSource()));

    connect(ui->btnGeneratePandoc,SIGNAL(clicked(bool)),
            this, SLOT(generatePandoc()));

    connect(ui->btnGenerateDiff, SIGNAL(clicked(bool)),
            this,SLOT(generateLatexDiff()));

    connect(ui->btnOutputPandoc, SIGNAL(clicked(bool)),
            this,SLOT(outputPandoc()));

    connect(ui->btnBib, SIGNAL(clicked(bool)),
            this, SLOT(openBib()));

    connect(ui->btnCSL, SIGNAL(clicked(bool)),
            this, SLOT(openCSL()));

    connect(ui->btnGeneratePandoc, SIGNAL(clicked(bool)),
            this, SLOT(generatePandoc()));


    connect(ui->btnPrevious, SIGNAL(clicked(bool)),
            this, SLOT(selectPrevious()));

    connect(ui->btnDiffOutput, SIGNAL(clicked(bool)),
            this, SLOT(outputLatexdiff())

            );

    connect(ui->btnGenerateDiff,SIGNAL(clicked(bool)),
            this, SLOT(generateLatexDiff()));


    connect(ui->actionSettings, SIGNAL(triggered(bool)),
            this,SLOT(openUserSettings()));
    //connect(prefAction, &QAction::triggered, this, )

    //check settings
    if(qs.value("pandoc").toString().isEmpty() &&
            qs.value("latexdiff").toString().isEmpty()){
        qDebug("we need to set something");
        configwindow cw;
        cw.exec();
        QMap<QString, QString> qm = cw.sendData();
        qs.setValue("pandoc", qm["pandoc"]);
        qs.setValue("latexdiff", qm["latexdiff"]);
    }

    if(qs.value("lastpath").toString().isEmpty()){
        qs.setValue("lastpath", QDir::homePath());
    }

    //qs.clear();

    //setup pandoc and latexdiff locations (consider using QSettings)

    //this->pandocLocation = "/usr/local/bin/";
    //this->latexdiffLocation = "/Library/TeX/texbin/";

    this->pandocLocation = qs.value("pandoc").toString();
    this->latexdiffLocation = qs.value("latexdiff").toString();
}

void MainWindow::selectSource(){

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Select LaTex source", qs.value("lastpath").toString(),
                                                    "Tex (*.tex)");

    if (!fileName.isEmpty()){
        //QFile file(fileName);
       //qDebug()<<fileName;
       ui->sourceLabel->setText(fileName);

       //save the last folder location
       QString lastPath = QFileInfo(fileName).absolutePath();
       qs.setValue("lastpath", lastPath);

       QByteArray ba = fileName.toLocal8Bit();
       const char *fileStr = ba.data();

       //std::string fileNameString = fileName.toStdString();


       pandocInterface.setSource(fileStr);
       latexdiffInterface.setSource(fileStr);


    }

}

void MainWindow::outputPandoc(){
    QString fileName = QFileDialog::getSaveFileName(this, "Save output", qs.value("lastpath").toString(), "*.docx");

    if(!fileName.isEmpty()){
        //QFile file(fileName);

        ui->lblOutputPandoc->setText(fileName);

        //save the last folder location
        QString lastPath = QFileInfo(fileName).absolutePath();
        qs.setValue("lastpath", lastPath);

        QByteArray ba = fileName.toLocal8Bit();
        const char *fileChar = ba.data();

        pandocInterface.setOutput(fileChar);
        latexdiffInterface.setOutput(fileChar);
    }
    else{
        return;
    }
}

void MainWindow::openBib(){
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Select bib file", qs.value("lastpath").toString(),
                                                    "Bib (*.bib)");

    if(!fileName.isEmpty()){

        ui->lblBib->setText(fileName);

        //save the last folder location
        QString lastPath = QFileInfo(fileName).absolutePath();
        qs.setValue("lastpath", lastPath);

        QByteArray ba = fileName.toLocal8Bit();
        const char *fileChar = ba.data();

        pandocInterface.setBib(fileChar);
    }
}

void MainWindow::openCSL(){
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Select csl style file", qs.value("lastpath").toString(),
                                                    "Csl (*.csl)");

    if(!fileName.isEmpty()){
        ui->lblCSL->setText(fileName);

        //save the last folder location
        QString lastPath = QFileInfo(fileName).absolutePath();
        qs.setValue("lastpath", lastPath);

        QByteArray ba = fileName.toLocal8Bit();
        const char *fileChar = ba.data();

        pandocInterface.setStyleLocation(fileChar);

    }
}

void MainWindow::generatePandoc(){

    QByteArray ba = this->pandocLocation.toLocal8Bit();
    const char * locChar = ba.data();

    pandocInterface.executePandoc(locChar);

    QMessageBox alertMsg;
    alertMsg.setText("Pandoc Conversion Completed.");
    alertMsg.setModal(true);
    alertMsg.exec();

}

void MainWindow::selectPrevious(){
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Select previous LaTex file", qs.value("lastpath").toString(),
                                                    "Tex (*.tex)");

    if(!fileName.isEmpty()){
        ui->lblPrevious->setText(fileName);

        //save the last folder location
        QString lastPath = QFileInfo(fileName).absolutePath();
        qs.setValue("lastpath", lastPath);

        QByteArray ba = fileName.toLocal8Bit();
        const char * prevChar = ba.data();

        latexdiffInterface.setPrevious(prevChar);

    }
}

void MainWindow::outputLatexdiff(){

    QString fileName = QFileDialog::getSaveFileName(this, "Save output", qs.value("lastpath").toString(), "*.tex");

    if(!fileName.isEmpty()){
        ui->lblOutputDiff->setText(fileName);

        //save the last folder location
        QString lastPath = QFileInfo(fileName).absolutePath();
        qs.setValue("lastpath", lastPath);

        QByteArray ba = fileName.toLocal8Bit();
        const char * diffChar = ba.data();

        latexdiffInterface.setOutput(diffChar);

    }

}

void MainWindow::generateLatexDiff(){

    QByteArray ba = this->latexdiffLocation.toLocal8Bit();
    const char * locChar = ba.data();

    latexdiffInterface.executeLatexDiff(locChar);

    QMessageBox alertMsg;
    alertMsg.setText("Diff Generation Completed.");
    alertMsg.setModal(true);
    alertMsg.exec();
}

void MainWindow::openUserSettings(){
    configwindow cw;
    cw.init(qs.value("pandoc").toString(), qs.value("latexdiff").toString());
    cw.exec();
    QMap<QString, QString> qm = cw.sendData();
    qs.setValue("pandoc", qm["pandoc"]);
    qs.setValue("latexdiff", qm["latexdiff"]);
}

void MainWindow::createMenus(){

}

MainWindow::~MainWindow()
{
    delete ui;
}
