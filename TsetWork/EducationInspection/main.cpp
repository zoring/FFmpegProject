#include <QCoreApplication>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include "ffmpegthread.h"
#include "handleffmpeg.h"
#include <QtCore>
#include "service.h"

#define __STDC_CONSTANT_MACROS

#ifdef _WIN32
//Windows
extern "C"
{
#include "libavformat/avformat.h"
#include "libavutil/mathematics.h"
#include "libavutil/time.h"
};
#else
//Linux...
#ifdef __cplusplus
extern "C"
{
#endif
#include <libavformat/avformat.h>
#include <libavutil/mathematics.h>
#include <libavutil/time.h>
#ifdef __cplusplus
};
#endif
#endif
using namespace std;
HandleFfmpeg FFmpegThread::test = HandleFfmpeg("/home/zoring/2.mp4");

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    Service x;

    return a.exec();
}
