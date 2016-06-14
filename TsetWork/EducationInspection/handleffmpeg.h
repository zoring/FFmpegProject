#include <QReadWriteLock>

#ifndef HANDLEFFMPEG_H
#define HANDLEFFMPEG_H
#include <unistd.h>
extern "C"
{
#include <libavformat/avformat.h>
#include <libavutil/mathematics.h>
#include <libavutil/time.h>
};

#include <string>
using namespace std;
class HandleFfmpeg
{

public:
    HandleFfmpeg(string FileName);
    bool CloseStream();         //關閉流，在這刪除資源
    bool SaveVdieoPath(string FileName);        //外部保存名字
    bool Start();
    bool Stop();
    void MoveOn();
   // QReadWriteLock lock;
 //
private:
    void SaveVideo();
    void StartStream();
    bool OpenFile(string FileName , AVInputFormat* fmt =0,AVDictionary** option = 0 );
    bool OpenStream(AVDictionary** option = 0 );
    bool GetVeidoStream();
    bool CheckInformation();
    bool CopyInformation();
    bool StaticOutFile();
    bool StaticLiveStream();
    int  ChangeTimeBase(AVPacket* pak,AVRational TargetTime ,AVRational Sourcetimebase , AVRounding rnd = (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));          //
    AVOutputFormat* OutFotmat ;                         //输入format
    AVFormatContext* ifcon , *ofcon, *ofmt_ctx ;        //context输入输出上下文

    AVPacket packet;                                     //包
    AVStream *i_video_stream;
    AVStream *o_video_stream, *o_live_stream;
    const char* InputName ,*OutPutName,*OutPutWays;
    string SavePath;
    int partK;
    int videoindex;
    bool IsStart;
    bool HasInditial;
    bool NewSaveFile;
};

#endif // HANDLEFFMPEG_H
