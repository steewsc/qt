#include "uploader.h"
#include <QFile>
#include <QDebug>

#include "config.h"
#include "imageholder.h"

Uploader::Uploader(QObject *parent) : QThread(parent){
    this->uploadedName = "";
    this->uploadman = new QNetworkAccessManager(this);
    this->isUploading = false;
    this->shouldClean = false;
}

void Uploader::run(){
    this->timPostpone = new QTimer(this);
    this->timPostpone->setSingleShot(false);
    connect( this->timPostpone, SIGNAL( timeout() ), this, SLOT( doUpload() ) );
    this->timPostpone->start(500);

    this->timClean = new QTimer(this);
    this->timClean->setSingleShot(false);
    connect( this->timClean, SIGNAL( timeout() ), this, SLOT( doCleaning() ) );
    this->timClean->start(5000);
}

void Uploader::doUpload(){
    if( ImageHolder::getImageCount() > 0 ){
        timPostpone->stop();
        uploadNext();
    }
}

void Uploader::doCleaning(){
    if( !this->isUploading && ImageHolder::getImageCount() == 0 && this->shouldClean ){
        if( this->_netRep != NULL ){
            this->shouldClean = false;
            this->_netRep->deleteLater();
            ImageHolder::imageCleaning();
        }
    }
}

void Uploader::dataError(QNetworkReply::NetworkError){
    QNetworkReply::NetworkError networkError = this->_netRep->error();
    qDebug() << "ERROR: " << networkError;
    this->isUploading = false;
    timPostpone->start(500);
}

void Uploader::dataSent(){
    this->clipboardName = QString( Config::hostURL + this->uploadedName );
    qDebug() << "DATA SENT to the server. Download link: " << this->clipboardName;
    ImageHolder::removeImg();
    this->isUploading = false;
    timPostpone->start(500);
}

void Uploader::SetProgress(qint64 _all, qint64 _readed){
    this->isUploading = true;
    qDebug() << "Progress: " << _all << " of " << _readed;
}

void Uploader::uploadNext(){
    this->isUploading = true;
    this->shouldClean = true;
    this->uploadedName = ImageHolder::getCryptedNameWithFormat();
    QNetworkRequest upload( this->setupURL() );
    this->_netRep = this->uploadman->put( upload, ImageHolder::getBytesForUpload() );
    this->connectSignals();
}

QUrl Uploader::setupURL(){
    QUrl uploadurl( Config::hostName + "/" + this->uploadedName );
    uploadurl.setUserName( Config::hostUsername );
    uploadurl.setPassword( Config::hostPassword );
    uploadurl.setPort(21);
    return uploadurl;
}

void Uploader::connectSignals(){
    connect(this->_netRep, SIGNAL( finished() ), this, SLOT( dataSent() ) );
    connect(this->_netRep, SIGNAL( uploadProgress( qint64,qint64 ) ), this, SLOT( SetProgress( qint64,qint64 ) ) );
    connect(this->_netRep, SIGNAL( error( QNetworkReply::NetworkError ) ), this, SLOT( dataError( QNetworkReply::NetworkError ) ) );
}
