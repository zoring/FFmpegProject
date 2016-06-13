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
 QMutex mutex;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    bool cansave = false;
    string newfilename = "";
    //set codeType UTF-8

    FFmpegThread test;
    test.start();
    char inputchar;
   while(1)
    {
      inputchar = getchar();
        if(inputchar == ' ')
        {
            mutex.lock();
            if (! test.StopFFmpeg())
                return -1;
            cansave = true;
            mutex.unlock();
        }
        else if(inputchar == 'i' && cansave)
        {
            cin>>newfilename ;
           mutex.lock();
            if(!test.SaveFile(newfilename))
                    return -2;
            test.MoveOn();
            cansave = false;
             mutex.unlock();
        }

    }


    return a.exec();
}
