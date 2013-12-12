#ifndef UPLOADER_H
#define UPLOADER_H

#include <QThread>
#include <QTimer>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QUrl>

class Uploader : public QThread
{
    Q_OBJECT
public:
    explicit Uploader(QObject *parent = 0);

    QString clipboardName;
    void run();
    QNetworkAccessManager *uploadman;
    QString uploadedName;

private:
    void uploadNext();
    void connectSignals();
    QUrl setupURL();

    QTimer *timPostpone;
    QTimer *timClean;
    QNetworkReply *_netRep;
    bool isUploading;
    bool shouldClean;

signals:
    void updateTrayIconProgress( int val );
    void updateClipBoard( QString newUrlPath );
    void showMessage();

public slots:
    void doUpload();
    void doCleaning();

    void dataSent();
    void dataError(QNetworkReply::NetworkError);
    void SetProgress(qint64,qint64);

};

#endif // UPLOADER_H
