#include <QReadWriteLock>

#ifndef HANDLEFFMPEG_H
#define HANDLEFFMPEG_H
#include <unistd.h>
extern "C"
{
#include <libavformat/avformat.h>
#include <libavutil/mathematics.h>
#include <libavutil/time.h>
#include <libavutil/opt.h>
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
    bool CreateOutPutCode(const char* outputname,AVCodecContext* incodecCnt,AVFormatContext *&outCnt);

    void SaveVideo();
    void StartStream();
    bool OpenFile(string FileName , AVInputFormat* fmt =0,AVDictionary** option = 0 );
    bool OpenStream(AVDictionary** option = 0 );
    bool GetVeidoStream();
    bool CheckInformation();
    bool CopyInformation();
    bool StaticOutFile();
    bool StaticLiveStream();
    bool StaticOpenCodec();
    int nextPTS();
    int nextDTS();
    bool EnCodeVidoe(AVPacket &pkt  );
    int  ChangeTimeBase(AVPacket* pak,AVRational TargetTime ,AVRational Sourcetimebase , AVRounding rnd = (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));          //
    AVOutputFormat* OutFotmat ;                         //输入format
    AVFormatContext* ifcon , *ofcon, *ofmt_ctx ;        //context输入输出上下文
     AVFrame* inputFrame;
    AVPacket packet;                                     //包
    AVStream *i_video_stream;
    AVStream *o_video_stream, *o_live_stream;
    AVCodec* InputCodec;
    const char* InputName ,*OutPutName,*OutPutWays;
    string SavePath;
    int partK;
    int videoindex;
    bool IsStart;
    bool HasInditial;
    bool NewSaveFile;
    AVCodecContext* video_enc_ctx = NULL;
    void test();
};

#endif // HANDLEFFMPEG_H
