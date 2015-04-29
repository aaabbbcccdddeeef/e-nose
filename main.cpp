#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#include <signal.h>
#include <error.h>

#include <QApplication>
#include <QTextCodec>
#include <QDebug>
#include "mainwindow.h"
#include "myinputpanelcontext.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MyInputPanelContext *ic = new MyInputPanelContext;
    app.setInputContext(ic);

    MainWindow mainwindow;
    mainwindow.showFullScreen();
    return app.exec();
}

