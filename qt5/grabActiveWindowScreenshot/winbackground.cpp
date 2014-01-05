#include "winbackground.h"
#include "ui_winbackground.h"
#include <QApplication>
#include <QScreen>
#include <QGuiApplication>
#include <QDesktopWidget>

#ifdef Q_OS_WIN
    #include "windows.h"
    #include "qt_windows.h"
#endif

WinBackground::WinBackground(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WinBackground)
{
    ui->setupUi(this);
}

WinBackground::~WinBackground()
{
    delete ui;
}

void WinBackground::grabActiveWindow(){

    #ifdef Q_OS_WIN
        grabActiveWindowWin();
    #endif

    #ifdef Q_OS_UNIX
        grabActiveWindowX11();
    #endif

}

#ifdef Q_OS_WIN
void WinBackground::grabActiveWindowWin(){
    HWND findWindow = GetForegroundWindow();
    if ( findWindow == NULL ){
        return;
    }
    if ( findWindow == GetDesktopWindow() ){
        return;
    }
    ShowWindow( findWindow, SW_SHOW );
    SetForegroundWindow( findWindow );
    HDC hdcScreen = GetDC( NULL );
    if (!hdcScreen) {
        qDebug() << "::GetDIBits(), failed to GetDC";
    }
    RECT rcWindow;
    GetWindowRect( findWindow, &rcWindow );
    if ( IsZoomed( findWindow ) ){
        if ( QSysInfo::WindowsVersion >= QSysInfo::WV_VISTA ){
          rcWindow.right -= 8;
          rcWindow.left += 8;
          rcWindow.top += 8;
          rcWindow.bottom -= 8;
        }else{
          rcWindow.right += 4;
          rcWindow.left -= 4;
          rcWindow.top += 4;
          rcWindow.bottom -= 4;
        }
    }

    QScreen *scr = QGuiApplication::primaryScreen();
    QPixmap result = QPixmap( scr->grabWindow( QApplication::desktop()->winId() ) );
    result = result.copy(rcWindow.left,rcWindow.top, rcWindow.right-rcWindow.left, rcWindow.bottom-rcWindow.top );

    ReleaseDC( findWindow, hdcScreen );

    emit qpixTaken(result);
    this->deleteLater();
    this->hide();
}
#endif

#ifdef Q_OS_UNIX
void WinBackground::grabActiveWindowX11(){
    /**
	* Will be implemented soon...
	*/
}
#endif
