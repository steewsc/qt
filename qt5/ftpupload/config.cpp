#include "config.h"
QString Config::hostName = "";
QString Config::hostUsername = "";
QString Config::hostPassword = "";
QString Config::hostURL = "";
QString Config::imageFormat;

Config::Config(QObject *parent) :
    QObject(parent)
{
}
