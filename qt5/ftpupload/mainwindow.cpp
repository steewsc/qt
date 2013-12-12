#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>

#include "config.h"
#include "imageholder.h"
#include "uploader.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Config::imageFormat = "jpg";
    Config::hostName = "ftp://HOST.com";
    Config::hostUsername = "USERNAME";
    Config::hostPassword = "PASSWORD";
    Config::hostURL = "http://cdn.HOST.com/";

    Uploader* upl = new Uploader(this);
    upl->run();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnBrowse_clicked(){
    QString selfilter = tr("JPEG (*.jpg *.jpeg)");
    QString s = QFileDialog::getOpenFileName(
                    this,
                    tr("Select the image"),
                    "/home",
                    tr("All files (*.*);;JPEG (*.jpg *.jpeg);;PNG (*.png)" ),
                    &selfilter
                );
    ui->txtNewImg->setText(s);
}

void MainWindow::on_btnInsertImg_clicked(){
    qDebug() << "insertImg => " << ui->txtNewImg->text();
    ImageHolder::insertImg( QPixmap( ui->txtNewImg->text(), QString("jpg").toLatin1() ) );
}

