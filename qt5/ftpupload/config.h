#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>

class Config : public QObject
{
    Q_OBJECT
public:
    explicit Config(QObject *parent = 0);

    static QString hostName;
    static QString hostUsername;
    static QString hostPassword;
    static QString hostURL;
    static QString imageFormat;
signals:

public slots:

};

#endif // CONFIG_H
