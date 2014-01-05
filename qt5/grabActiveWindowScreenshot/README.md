QT5 Take Screenshot of Active Window
==
Create new instance of WinBackground class,
connect its SIGNAL qpixTaken(QPixmap) with your SLOT
and call:
grabActiveWindow()

Or You may do whatever you want,
the main thing is that QPixmap of captured window is in QPixmap called result,
in grabActiveWindow() method ;-).

