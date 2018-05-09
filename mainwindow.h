#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "PandocInterface.h"
#include "LatexDiffInferface.h"
#include "configwindow.h"
#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void selectSource();
    void generatePandoc();
    void generateLatexDiff();
    void outputPandoc();
    void openBib();
    void openCSL();
    void selectPrevious();
    void outputLatexdiff();
    void openUserSettings();
    //void openSettings();

//signals:
  //  void updateSettings();

private:
    PandocInterface pandocInterface;
    LatexDiffInterface latexdiffInterface;
    QString pandocLocation;
    QString latexdiffLocation;
    Ui::MainWindow *ui;
    void createMenus();
    QSettings qs;

};

#endif // MAINWINDOW_H
