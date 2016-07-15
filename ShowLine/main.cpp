#include <QCoreApplication>

#include<stdio.h>
#include <iostream>
#include <QtDebug>
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
#include <libavutil/audio_fifo.h>
#include <libswresample/swresample.h>
#include <libavcodec/avcodec.h>
#include <libavfilter/avfiltergraph.h>
#include <libavfilter/avcodec.h>
#include <libavfilter/buffersink.h>
#include <libavfilter/buffersrc.h>
#include <libavutil/avutil.h>
#include <libavutil/opt.h>
#include <libavutil/pixdesc.h>
#ifdef __cplusplus
};
#endif
#endif

using namespace std;
#define ERRORMSG "fd "
string InputName = "rtsp://admin:admin@192.168.3.78:554/cam/realmonitor?channel=1&subtype=0", OutputName="rtmp://0.0.0.0/myapp/test1";
AVFormatContext *Input_formatCnt, *Output_formatCnt;

AVFrame *Input_Frame, *Output_Frame;
AVBitStreamFilterContext* aacbsfc;

AVStream *Input_Video_Stream, *Input_Audio_Stream,\
         *Output_Video_Stream, *OutPut_Audio_Stream;
int VideoIndex, AudioIndex;
AVCodec* InputCodec;
AVRational time_base_q = { 1, AV_TIME_BASE };
 int bufsize;
 char* buf ;
int64_t begintime;
int64_t LastPackTime;
AVRational av_time_base_q;
AVFilterContext *buffersrc_ctx =NULL, *buffersink_ctx =NULL;
void printTime();
bool InintEnCodecAACMsg(AVFormatContext *&pFormatCtx, AVStream *&fmt, AVStream *& infmt)
{



    pFormatCtx->oformat->audio_codec = AV_CODEC_ID_AAC;
    AVCodec* AACCodec = NULL;
    AVCodecContext* AACCodecCnt, *srcCodectx;
    srcCodectx = infmt->codec;
    AACCodec = avcodec_find_encoder(AV_CODEC_ID_AAC);
    if (!AACCodec)
        return false;
    fmt = avformat_new_stream(pFormatCtx, AACCodec);
    fmt->id = pFormatCtx->nb_streams -1;
    AACCodecCnt = fmt->codec;
    AACCodecCnt->codec_id = AV_CODEC_ID_AAC;
    AACCodecCnt->codec_type = AVMEDIA_TYPE_AUDIO ;
    AACCodecCnt->profile = FF_PROFILE_AAC_MAIN;
    AACCodecCnt->block_align = 0;
    AACCodecCnt->bit_rate = 128000;
    AACCodecCnt->channels = 1  ;
    AACCodecCnt->sample_rate =  16000;//Input_Audio_Stream->codec->sample_rate;
    AACCodecCnt->sample_fmt = AV_SAMPLE_FMT_S16;
    AACCodecCnt->channel_layout = AV_CH_LAYOUT_MONO;;
   // AACCodecCnt->strict_std_compliance = FF_COMPLIANCE_EXPERIMENTAL;

    fmt->time_base = {1,AACCodecCnt->sample_rate};



    fmt->codec->codec_tag = 0;

    //Format wants global header,outputStream.flags : Place global headers in extradata instead of every keyframe.H264输出时候必要
    if( pFormatCtx->oformat->flags |= AVFMT_GLOBALHEADER)
        fmt->codec->flags |= CODEC_FLAG_GLOBAL_HEADER ;
    if (avcodec_open2(AACCodecCnt, AACCodec, NULL) < 0)
    {
        qDebug() <<   QString("InintEnCodecAACMsg, can not open the codec ");
        return false;
    }

    return true;
}


//打开输入端,保证只运行一次
bool OpenInputStream()
{


    AVDictionary *avdic =NULL;

    av_dict_set(&avdic,"rtsp_transport", "tcp", 0);
    av_dict_set(&avdic,"stimeout","1000000",0);
    av_dict_set(&avdic, "max_delay","50000",0);
    av_dict_set(&avdic,"fflags","nobuffer",0);
  //  av_dict_set(&avdic,"allowed_media_types","video",0);
    int ret = avformat_open_input(&Input_formatCnt,InputName.c_str() , NULL, &avdic) ;
    if ( ret < 0 )
    {
        char error[128];
                            const char *errbuf_ptr = error;
                             av_strerror(ret, error, sizeof(error));
                             errbuf_ptr = strerror(AVUNERROR(ret));
                            qDebug()<< QString(errbuf_ptr);
                qDebug() <<   QString("InitOutPutMsg, can not write header  ") + QString(OutputName.c_str()) ;
        qDebug() <<  QString("OpenInputStream, can not open avformat input ") + QString(InputName.c_str());
        return false ;
    }

    if ((avformat_find_stream_info(Input_formatCnt , 0)) < 0 )
    {    //avformat_open_input只是打开头文件，读取流是该函数
        qDebug() <<   QString("OpenInputStream, there is no information in that open ");
        return false;
    }

    av_dump_format(Input_formatCnt, 0, InputName.c_str(), 0);           //输出format的信息

    return true;
}

//查找视频流
bool FindInputVideoStream()
{
    for( int i=0; i < Input_formatCnt->nb_streams; ++i )
    {
        if( Input_formatCnt->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO){
            Input_Video_Stream =  Input_formatCnt->streams[i];
            VideoIndex = i;
            return true;
        }
    }
    return false;
}

bool FindInputAudioStream()
{
    for( int i=0; i < Input_formatCnt->nb_streams; ++i )
    {
        if( Input_formatCnt->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO){
            Input_Audio_Stream =  Input_formatCnt->streams[i];
            AudioIndex = i;
            return true;
        }
    }
    return false;
}


bool FindInputAVStream()
{
    if(FindInputVideoStream() && FindInputAudioStream())
    {

        return true;
    }
    return false;

}
//以下为输出端, 编码器信息
bool InitOutputStream(AVFormatContext *&outputCnt, AVStream *&outputStream, AVStream *&inputStream)
{

    //根据编码器复制输入端的视频流信息
    outputStream = avformat_new_stream(outputCnt, inputStream->codec->codec);
    if ( !outputStream )
    {
        qDebug() << ERRORMSG + QString("InitOutPutMsg, failed allocating output stream ");
        return false ;
    }

    if (avcodec_copy_context(outputStream->codec, inputStream->codec) < 0 )
    {
       qDebug() << ERRORMSG + QString("InitOutPutMsg, failed to copy context from input to output stream codec context ");
       return false;
    }

    outputStream->codec->codec_tag = 0;

    //Format wants global header,outputStream.flags : Place global headers in extradata instead of every keyframe.H264输出时候必要
    if( outputCnt->oformat->flags |= AVFMT_GLOBALHEADER)
        outputStream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;
    return true;
}





//公用初始化输出，无论直播还是保存
bool InitOutMsg(AVFormatContext* &Out_formatCnt,const string &name, AVStream *&out_videoStream,  AVStream *&out_audioStream)
{

    if(Input_Video_Stream)
    {
        if ( !InitOutputStream(Out_formatCnt, out_videoStream, Input_Video_Stream) )
            return false;
    }

    if (Input_Audio_Stream)
    {

            if( !InintEnCodecAACMsg(Out_formatCnt, out_audioStream,Input_Audio_Stream) )
                return false ;


    }

    av_dump_format(Out_formatCnt, 0, name.c_str(), 1);
    if( avio_open(&Out_formatCnt->pb, name.c_str(), AVIO_FLAG_WRITE) < 0)
    {
        qDebug() << ERRORMSG + QString("InitOutPutMsg, can not open avio  ") + QString(name.c_str()) ;
        return false;
    }

    int ret = avformat_write_header(Out_formatCnt, NULL) ;

    //写文件头（对于某些没有文件头的封装格式，不需要此函数。比如说MPEG2TS）
    if(  ret < 0)
    {
        cout<< ret<<endl;
        qDebug() << QString("InitOutPutMsg, can not write header  ") + QString(name.c_str()) ;
        return false;
    }
    return true;
}




bool InitOutputInformation()
{
    //初始化输出码流的AVFormatContext。
    avformat_alloc_output_context2(&Output_formatCnt, 0, "flv", OutputName.c_str());

    if( !Output_formatCnt )
    {
        qDebug() << ERRORMSG + QString("InitOutputInformation, can not create output context File name ") + QString(OutputName.c_str()) ;
        return false;
    }
   if( !InitOutMsg(Output_formatCnt, OutputName, Output_Video_Stream, OutPut_Audio_Stream) )
       return false;
//    if (!InitoutputTest())
//        return false;
   return true;
}




void InitAudiotest(){
     AVCodec* AACCodec = NULL;
    avformat_alloc_output_context2(&Output_formatCnt, NULL, "flv", OutputName.c_str());
    OutPut_Audio_Stream = avformat_new_stream(Output_formatCnt, AACCodec);
    AACCodec = avcodec_find_encoder(AV_CODEC_ID_AAC);
    if (!AACCodec)
        return ;
    AVCodecContext* AACCodecCnt = OutPut_Audio_Stream->codec;
    AACCodecCnt->codec_id = AV_CODEC_ID_AAC ;
    AACCodecCnt->bit_rate = 64000;//Input_Audio_Stream->codec->bit_rate;
    AACCodecCnt->sample_fmt = AV_SAMPLE_FMT_S16;

    AACCodecCnt->codec_type = AVMEDIA_TYPE_AUDIO;

    AACCodecCnt->sample_rate =Input_Audio_Stream->codec->sample_rate;
    AACCodecCnt->channel_layout = AV_CH_LAYOUT_STEREO;
    AACCodecCnt->channels = 2;
    AACCodecCnt->time_base = {1, AACCodecCnt->sample_rate};
    if (Output_formatCnt->oformat->flags & AVFMT_GLOBALHEADER)
        AACCodecCnt->flags |= CODEC_FLAG_GLOBAL_HEADER;

    if (avcodec_open2(AACCodecCnt,AACCodec,NULL ) < 0){
        cout<< "dfdsf"<<endl;
        return ;
    }

     av_dump_format(Output_formatCnt, 0, OutputName.c_str(), 1);
    if (avio_open(&Output_formatCnt->pb, OutputName.c_str(), AVIO_FLAG_READ_WRITE) < 0)
    {
        cout<<"false"<<endl;
        return ;
    }

    int ret = avformat_write_header(Output_formatCnt, NULL) ;

    //写文件头（对于某些没有文件头的封装格式，不需要此函数。比如说MPEG2TS）
    if(  ret < 0)
    {
        cout<< ret<<endl;
        qDebug() << QString("InitOutPutMsg, can not write header  ") + QString(OutputName.c_str()) ;
        return ;
    }
    av_dump_format(Output_formatCnt, 0, OutputName.c_str(), 1);

    cout<< OutPut_Audio_Stream->time_base.den << " "<< OutPut_Audio_Stream->codec->time_base.den<<endl;
    cout<< ret<<endl;
}




bool TurnToAAC(AVFrame* &filt_frame)
{
    AVPacket test;
    test.size = 0;
    test.data = NULL;
    av_init_packet(&test) ;
    int gotpacket;

   int audioret =  avcodec_encode_audio2(OutPut_Audio_Stream->codec, &test, filt_frame, &gotpacket);


   if (gotpacket == 1 && audioret >=0)
   {

       test.pts = av_rescale_q( test.pts, OutPut_Audio_Stream->codec->time_base, OutPut_Audio_Stream->time_base);

       test.dts = test.pts;
       test.duration = av_rescale_q(test.duration, OutPut_Audio_Stream->codec->time_base, OutPut_Audio_Stream->time_base) ;
       cout<<test.pts<<" "<<test.duration<<endl;
       test.pos = -1;
       test.flags |= AV_PKT_FLAG_KEY;
       test.stream_index = AudioIndex;
       av_write_frame(Output_formatCnt, &test);
       cout<<"finsh Codec"<<endl;
   }
   else
       cout<<"Error"<<endl;

}
//}
void printTime(){
    int64_t nowtime = av_gettime();
   // cout<< "Now is "<< nowtime - begintime<<endl;
    begintime = av_gettime();
}

//转码为AAC
bool OtherToAAC(AVPacket*& pkt, AVFrame* &decoded_frame)
{


    decoded_frame = avcodec_alloc_frame();
    int got_frame;
   static int64_t startTime;

    int len = avcodec_decode_audio4(Input_Audio_Stream->codec, decoded_frame, &got_frame, pkt);
     av_free_packet(pkt);
    if (len < 0)
    {

        cout<<"error0"<<endl;
        return false;
    }

    if (got_frame)
    {

                    AVFrame* frame = decoded_frame;
                    AVFrame *filt_frame = nullptr;
                    frame->pts = frame->pkt_pts;

        if (av_buffersrc_add_frame_flags(buffersrc_ctx, frame, AV_BUFFERSRC_FLAG_PUSH) < 0) {
                            av_log(NULL, AV_LOG_ERROR, "Error while feeding the audio filtergraph\n");
                            av_frame_free(&frame);
                            return false;
                        }
                        frame->pts = AV_NOPTS_VALUE;

                        /* pull filtered audio from the filtergraph */
                        filt_frame = av_frame_alloc();
                        while (1) {
                            int ret = av_buffersink_get_frame_flags(buffersink_ctx, filt_frame, AV_BUFFERSINK_FLAG_NO_REQUEST);
                            if(ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
                                break;
                            if(ret < 0)
                            {
                                av_frame_free(&frame);
                                av_frame_free(&filt_frame);
                                break;
                            }

                            int64_t frame_pts = AV_NOPTS_VALUE;
                            if (filt_frame->pts != AV_NOPTS_VALUE) {
                                startTime = (startTime == AV_NOPTS_VALUE) ? 0 : startTime;


                                filt_frame->pts = frame_pts =
                                    av_rescale_q(filt_frame->pts, buffersink_ctx->inputs[0]->time_base,    OutPut_Audio_Stream->codec->time_base);
//                                        - av_rescale_q(startTime, av_time_base_q,    OutPut_Audio_Stream->codec->time_base);


                            }

                            av_frame_free(&frame);
                            TurnToAAC(filt_frame);
                            av_frame_free(&filt_frame);
                        }
                    }


}
void ChageTimeBase(AVPacket *pak, AVRational Sourcetimebase, AVRational TargetTime, AVRounding rnd =(AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX))
{
    pak->pts = av_rescale_q_rnd(pak->pts, Sourcetimebase, TargetTime,rnd );
    pak->dts = av_rescale_q_rnd(pak->dts, Sourcetimebase, TargetTime,rnd );
    pak->duration = av_rescale_q(pak->duration,Sourcetimebase, TargetTime) ;
    pak->pos = -1;
}


int initFilters()
      {

              char args[512];
              int ret=0;
              AVCodecContext* decoderContext = Input_Audio_Stream->codec;
              AVFilter *abuffersrc  = avfilter_get_by_name("abuffer");
              AVFilter *abuffersink = avfilter_get_by_name("abuffersink");
              AVFilterInOut *outputs = avfilter_inout_alloc();
              AVFilterInOut *inputs  = avfilter_inout_alloc();
              static const enum AVSampleFormat out_sample_fmts[] = { AV_SAMPLE_FMT_S16, AV_SAMPLE_FMT_NONE };
              static const int64_t out_channel_layouts[] = { AV_CH_LAYOUT_MONO, -1 };
              static const int out_sample_rates[] = {decoderContext->sample_rate , -1 };
              AVRational time_base = Input_Audio_Stream->codec->time_base;
              AVFilterGraph * filter_graph = avfilter_graph_alloc();

              /* buffer audio source: the decoded frames from the decoder will be inserted here. */

              if (!decoderContext->channel_layout)
                  decoderContext->channel_layout = av_get_default_channel_layout(decoderContext->channels);



            snprintf(args, sizeof(args),
                  "time_base=%d/%d:sample_rate=%d:sample_fmt=%s:channel_layout=0x%"PRIx64,
                  time_base.num, time_base.den, decoderContext->sample_rate,
                  av_get_sample_fmt_name(decoderContext->sample_fmt), decoderContext->channel_layout);
              ret = avfilter_graph_create_filter(&buffersrc_ctx, abuffersrc, "in",
                  args, NULL, filter_graph);
              if (ret < 0) {
                  av_log(NULL, AV_LOG_ERROR, "Cannot create audio buffer source\n");
                  return ret;
              }

              /* buffer audio sink: to terminate the filter chain. */
              ret = avfilter_graph_create_filter(&buffersink_ctx, abuffersink, "out",
                  NULL, NULL, filter_graph);
              if (ret < 0) {
                  av_log(NULL, AV_LOG_ERROR, "Cannot create audio buffer sink\n");
                  return ret;
              }

              ret = av_opt_set_bin(buffersink_ctx, "sample_fmts",(uint8_t*)&OutPut_Audio_Stream->codec->sample_fmt, sizeof(OutPut_Audio_Stream->codec->sample_fmt),
                  AV_OPT_SEARCH_CHILDREN);
              if (ret < 0) {
                  av_log(NULL, AV_LOG_ERROR, "Cannot set output sample format\n");
                  return ret;
              }

              ret = av_opt_set_bin(buffersink_ctx, "channel_layouts", (uint8_t*)&OutPut_Audio_Stream->codec->channel_layout, sizeof(OutPut_Audio_Stream->codec->channel_layout),
                  AV_OPT_SEARCH_CHILDREN);
              if (ret < 0) {
                  av_log(NULL, AV_LOG_ERROR, "Cannot set output channel layout\n");
                  return ret;
              }

              ret = av_opt_set_bin(buffersink_ctx, "sample_rates",(uint8_t*)& OutPut_Audio_Stream->codec->sample_rate, sizeof(OutPut_Audio_Stream->codec->sample_rate),
                  AV_OPT_SEARCH_CHILDREN);
              if (ret < 0) {
                  av_log(NULL, AV_LOG_ERROR, "Cannot set output sample rate\n");
                  return ret;
              }

              /* Endpoints for the filter graph. */
              outputs->name       = av_strdup("in");
              outputs->filter_ctx = buffersrc_ctx;
              outputs->pad_idx    = 0;
              outputs->next       = NULL;

              inputs->name       = av_strdup("out");
              inputs->filter_ctx = buffersink_ctx;
              inputs->pad_idx    = 0;
              inputs->next       = NULL;
              if (!outputs->name || !inputs->name)
                 {
                     ret = AVERROR(ENOMEM);
                     return ret;
                 }

              if ((ret = avfilter_graph_parse_ptr(filter_graph, "anull",
                  &inputs, &outputs, nullptr)) < 0)
                  return ret;

              if ((ret = avfilter_graph_config(filter_graph, NULL)) < 0)
                  return ret;

              av_buffersink_set_frame_size(buffersink_ctx, 1024);
          return 0;
      }

int main(int argc, char* argv[])
{
    av_register_all();                                    //初始化注册所有要用的编码器解码器等
    avformat_network_init();                              //初始化网络流
    avfilter_register_all();

    if( !OpenInputStream() )
        return 3;
    if( !FindInputAVStream() )
        return 5;
    InputCodec = avcodec_find_decoder(Input_Audio_Stream->codec->codec_id) ;

    if (!InputCodec)
    Input_Audio_Stream->codec->codec = InputCodec;
    //打开解码器
    if(avcodec_open2(Input_Audio_Stream->codec, InputCodec, 0) < 0)
        return 1;
   if (!InitOutputInformation())
       return -3;
   if (initFilters() < 0)
       return -4;
   AVPacket* pkt;
   //AVFrame* decoded_frame  =NULL;

   av_time_base_q.num = 1;
   av_time_base_q.den = AV_TIME_BASE;
   int64_t start_time = av_gettime();
    int k =0;
    cout<<OutPut_Audio_Stream->time_base.den<<" "<<Input_Audio_Stream->time_base.den<<endl;
   const int output_frame_size = OutPut_Audio_Stream->codec->frame_size;
    while(1)
    {

//        if(pkt->stream_index==VideoIndex){
//            AVRational time_base=Input_formatCnt->streams[VideoIndex]->time_base;
//            int64_t pts_time = av_rescale_q(pkt->pts, time_base, time_base_q);
//            int64_t now_time = av_gettime() - start_time;
//            if (pts_time > now_time)
//                av_usleep(pts_time - now_time);

//         }
//        else {
//            AVRational time_base=Input_formatCnt->streams[AudioIndex]->time_base;
//            int64_t pts_time = av_rescale_q(pkt->pts, time_base, time_base_q);
//            int64_t now_time = av_gettime() - start_time;
//            if (pts_time > now_time)
//                av_usleep(pts_time - now_time);
//        }

    AVFrame* decoded_frame;
        pkt = new AVPacket;
        av_init_packet(pkt) ;
        pkt->size = 0;
        pkt->data = NULL;
        int ret = av_read_frame(Input_formatCnt, pkt);
        if (ret < 0)
        {
             break;
        }
        if (pkt->size <= 0)
            continue ;
        if (pkt->stream_index != AudioIndex)
        {
            ChageTimeBase(pkt,Input_Video_Stream->time_base, Output_Video_Stream->time_base);
            av_write_frame(Output_formatCnt, pkt);
         av_free_packet(pkt);
            continue ;
         }
        OtherToAAC( pkt,  decoded_frame);
       // ChageTimeBase(pkt,Input_Video_Stream->time_base,av_time_base_q );


        }
       // av_free_packet(pkt);



}

