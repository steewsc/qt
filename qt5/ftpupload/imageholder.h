#ifndef IMAGEHOLDER_H
#define IMAGEHOLDER_H

#include <QObject>
#include <QHash>
#include <QStringList>
#include <QPixmap>
#include <QDebug>
#include <QByteArray>
#include <QBuffer>
#include <QCryptographicHash>
#include <QNetworkInterface>
#include <QDateTime>

#include "config.h"

class ImageHolder : public QObject
{
    Q_OBJECT
public:
    explicit ImageHolder(QObject *parent = 0);

    static QPixmap getPixmap(QString imgName){
        QPixmap result = QPixmap();
        if( ImageHolder::images.contains(imgName) ){
            result = ImageHolder::images.value(imgName);
        }
        return result;
    }

    static void insertImg( QPixmap newImg ){
        QString imgName = "image_" + QString::number( getImageCount() );
        ImageHolder::imagesList.append( imgName );
        ImageHolder::images.insert( imgName, newImg );
    }

    static void removeImg(){
        if( getImageCount() > 0 ){
            if( ImageHolder::images.contains( ImageHolder::imagesList.at( 0 ) ) ){
                ImageHolder::images.remove( ImageHolder::imagesList.at( 0 ) );
                ImageHolder::imagesList.removeAt( 0 );
            }else{
                ImageHolder::imagesList.removeAt( 0 );
            }
        }else{
            ImageHolder::imageCleaning();
        }
    }

    static void imageCleaning(){
        ImageHolder::images.clear();
        ImageHolder::imagesList.clear();
    }

    static QHash<QString,QPixmap> images;
    static QStringList imagesList;

    static int getImageCount(void){
        return ImageHolder::imagesList.count();
    }

    static QByteArray getBytesForUpload(void){
        QByteArray bytes;
        if( getImageCount() > 0 ){
            QBuffer tmpBuffer(&bytes);
            QPixmap test = ImageHolder::images.value( imagesList.at( 0 ) );
            tmpBuffer.open( QIODevice::WriteOnly );
            test.save( &tmpBuffer, Config::imageFormat.toLatin1() );
        }
        return bytes;
    }

    static QString getCryptedName( QString value ){ return QCryptographicHash::hash( QByteArray::fromRawData( value.toLatin1(), value.length() ), QCryptographicHash::Md5 ).toHex(); }

    static QString getMacAddress(void){
        foreach( QNetworkInterface interface, QNetworkInterface::allInterfaces() ) {
            if (!(interface.flags() & QNetworkInterface::IsLoopBack))
                return interface.hardwareAddress();
        }
        return QString();
    }

    static QString getCryptedNameWithFormat(void){
        QDateTime tt2 = QDateTime::currentDateTime();
        QString newName = getMacAddress() + QString::number( tt2.toMSecsSinceEpoch() );
        return getCryptedName( newName ) + "." + Config::imageFormat;
    }



signals:

public slots:

};

#endif // IMAGEHOLDER_H
