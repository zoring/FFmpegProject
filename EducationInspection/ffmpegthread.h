#ifndef FFMPEGTHREAD_H
#define FFMPEGTHREAD_H
#include <qthread.h>
#include "handleffmpeg.h"
#include <string>
using namespace std;
class FFmpegThread : public QThread
{
    Q_OBJECT
public:
    FFmpegThread();
    bool SaveFile(string FileName);
    bool StopFFmpeg();
    static HandleFfmpeg test;
    void MoveOn();
protected :
    void run();




};

#endif // FFMPEGTHREAD_H
