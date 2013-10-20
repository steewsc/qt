#include "imageholder.h"

QHash<QString,QPixmap> ImageHolder::images;
QStringList ImageHolder::imagesList;

ImageHolder::ImageHolder(QObject *parent) : QObject(parent){

}
