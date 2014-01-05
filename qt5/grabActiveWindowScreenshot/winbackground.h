#ifndef WINBACKGROUND_H
#define WINBACKGROUND_H

#include <QWidget>
#include <QPixmap>

namespace Ui {
class WinBackground;
}

class WinBackground : public QWidget
{
    Q_OBJECT

public:
    explicit WinBackground(QWidget *parent = 0);
    ~WinBackground();
#ifdef Q_OS_WIN
        void grabActiveWindowWin();
#endif
#ifdef Q_OS_UNIX
        void grabActiveWindowX11();
#endif

public slots:
    void grabActiveWindow();

signals:
    void qpixTaken(QPixmap result);

private:
    Ui::WinBackground *ui;
};

#endif // WINBACKGROUND_H
