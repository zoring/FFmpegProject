#include "handleffmpeg.h"
#include <fstream>
#include <iostream>
using namespace std ;
HandleFfmpeg::HandleFfmpeg(string FileName) :IsStart(false),partK(1), HasInditial(false), NewSaveFile(false)
{
    av_register_all();                                    //初始化注册所有要用的编码器解码器等
    avformat_network_init();                              //初始化网络流
    InputName = "rtsp://192.168.2.12/1" ;                //媒体流输入端
    OutPutWays = "rtmp://0.0.0.0/myapp/test1" ;
    SavePath = FileName ;
    OutPutName = ""       ;                               //媒体流输出

}



//参数ps包含一切媒体相关的上下文结构，有它就有了一切，本函数如果打开媒体成功，    
//会返回一个AVFormatContext的实例．    
//参数filename是媒体文件名或URL．    
//参数fmt是要打开的媒体格式的操作结构，因为是读，所以是inputFormat．此处可以    
//传入一个调用者定义的inputFormat，对应命令行中的 -f xxx段，如果指定了它，    
//在打开文件中就不会探测文件的实际格式了，以它为准了．    
//参数options是对某种格式的一些操作，是为了在命令行中可以对不同的格式传入    
//特殊的操作参数而建的， 为了了解流程，完全可以无视它．

bool HandleFfmpeg::OpenFile(string FileName, AVInputFormat* fmt ,AVDictionary** option  ){
   AVDictionary *avdic =NULL;
  av_dict_set(&avdic,"rtsp_transport", "tcp", 0);
   av_dict_set(&avdic,"stimeout","1000000",0);
  av_dict_set(&avdic, "max_delay","50000",0);
   av_dict_set(&avdic,"fflags","nobuffer",0);
  av_dict_set(&avdic,"allowed_media_types","video",0);
    //ifcon->flags=AVFMT_FLAG_NOBUFFER;
    if ( avformat_open_input(&ifcon,InputName , fmt , &avdic) < 0 )
        {
        printf(FileName.c_str()) ;
        printf ("Wrong path of open ");
        return false ;
    }

    return true ;
}

bool HandleFfmpeg::SaveVdieoPath(string FileName){
    fstream _file;
    _file.open(FileName,ios::in);
   // if (_file)
     //   return false;
    SavePath = FileName ;
   if (!CheckInformation() )
        return false;
    return true;
}



bool HandleFfmpeg::OpenStream(AVDictionary** option  ){

    if ((avformat_find_stream_info(ifcon , option)) < 0 ) {      //avformat_open_input只是打开头文件，读取流是该函数
        printf ("There is no information in that open") ;
        return false;
    }
    return true;
}

/*查找该格式文件中是否有视频流，如果有將它賦值給i_video_stream，找不到直接返回false*/
bool HandleFfmpeg::GetVeidoStream(){
  
    //查找视频流的Index
    for (int i =0 ; i < ifcon->nb_streams ; i++){
        if ( ifcon->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO ){   //codec为编码器，其中就是根据流的编码器找到视频流
       
            i_video_stream = ifcon->streams[i] ;
            videoindex = i;
            return true ;
        }
    }
    return false ;
}


bool HandleFfmpeg::CheckInformation(){
    av_dump_format(ifcon, 0, InputName, 0);                              //将文件信息相关联
    avformat_alloc_output_context2(&ofcon ,NULL ,NULL, SavePath.c_str()) ;       //新建输入端，最后一个NULL是叫ffmpeg自己寻找该封装格式
    if (!ofcon) {
        printf( "Could not create output context\n");
       return false;
    }
    return true;
}

bool HandleFfmpeg::CopyInformation(){
    o_video_stream = avformat_new_stream(ofcon, i_video_stream->codec->codec);    //复制编码器信息
            if (!o_video_stream) {
                printf( "Failed allocating output stream\n");
            return false ;
            }
    return true;
}


bool HandleFfmpeg::StaticLiveStream(){
    avformat_alloc_output_context2(&ofmt_ctx,NULL, "flv",OutPutWays);
    if(!ofmt_ctx)
    {
        printf("Could not create output context") ;
        return false;
    }
    OutFotmat = ofmt_ctx->oformat;

   o_live_stream = avformat_new_stream(ofmt_ctx,i_video_stream->codec->codec);
   if (!o_live_stream) {
       printf("Failed allocating output stream \n");
       return false ;
   }
   int ret = avcodec_copy_context(o_live_stream->codec, i_video_stream->codec) ;
   if (ret < 0) {
       printf ("Failed to copy context from input to output stream codec context\n");
       return false;
   }
   //以下代码暂时没知道用途
   o_live_stream->codec->codec_tag = 0;
   if(ofmt_ctx->oformat->flags & AVFMT_GLOBALHEADER)
       o_live_stream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;
   av_dump_format(ofmt_ctx,0, OutPutWays, 1);
   if (!(OutFotmat->flags & AVFMT_NOFILE)){
       ret = avio_open(&ofmt_ctx->pb, OutPutWays, AVIO_FLAG_WRITE) ;     //打开ffmpeg输入输出文件
       if (ret < 0){
           printf("Could not open output URL '%s'", OutPutWays) ;
           return false ;
       }
   }
   ret =  avformat_write_header(ofmt_ctx, NULL) ;
   if (ret < 0){
       printf ("Error occurred when opening output URL \n");
       return false;
   }
   return true;
}

void HandleFfmpeg::MoveOn(){

    IsStart = true;
}

bool HandleFfmpeg::Start(){
    if (!HasInditial)
    {
        if (!OpenFile(SavePath) ) return false ;
        if (!OpenStream())      return false ;
        if (!CheckInformation() || !GetVeidoStream()) return false;
        if (!StaticLiveStream()) return false;
        HasInditial = true;
    }
  printf( "HandleFfmpeg::Start\n");
   StartStream();
   return true;
}

bool HandleFfmpeg::Stop(){
 // lock.lockForWrite();
  //  mutex.lock();
    NewSaveFile = true ;
    IsStart = false;
  //  mutex.unlock();
//    lock.unlock();


    return true ;
}

void HandleFfmpeg::SaveVideo(){
    av_write_trailer(ofcon);       //写入输出流文件尾

  avcodec_close(ofcon->streams[0]->codec);
   av_freep(&ofcon->streams[0]->codec);
   av_freep(&ofcon->streams[0]);

  avio_close(ofcon->pb);
   av_free(ofcon);
}
bool HandleFfmpeg::StaticOutFile(){
    o_video_stream =  avformat_new_stream(ofcon,i_video_stream->codec->codec);                      //将流信息输入到输出端
    if (!o_video_stream) {
        printf( "Failed allocating output stream\n");
        return false;
    }
   if( avcodec_copy_context(o_video_stream->codec, i_video_stream->codec) < 0)
        {printf( "Failed to copy context from input to output stream codec context\n");
        return false;
        }
     av_dump_format(ifcon, 0, InputName, 0);                              //该函数的作用就是检查下初始化过程中设置的参数是否符合规范
   if( (avio_open(&ofcon->pb, SavePath.c_str(),AVIO_FLAG_WRITE)) < 0 )
      { printf( "Could not open output URL '%s'", SavePath.c_str());
        return false ;}
    avformat_write_header (ofcon, NULL) ;   //将信息写入头文件
    return true;

}

int HandleFfmpeg::ChangeTimeBase(AVPacket* pak,AVRational Sourcetimebase ,AVRational TargetTime, AVRounding rnd ){
    pak->pts = av_rescale_q_rnd(pak->pts, Sourcetimebase, TargetTime,rnd );
    pak->dts = av_rescale_q_rnd(pak->dts, Sourcetimebase, TargetTime,rnd );
    pak->duration = av_rescale_q(packet.duration,Sourcetimebase, TargetTime) ;
    pak->pos = -1;
}

/*开始推流*/
void HandleFfmpeg::StartStream(){

    if (!StaticOutFile()) return ;

    int64_t pts, dts;
    int dur;
    AVStream *in_stream, *out_stream;
     IsStart = true ;
     int i =0;
     int frame_index = 0;
     bool saveit = true;
     bool FristPacket = true;
    int64_t start_time ;
    int64_t start_timeCoding;
     while(1) {
    i++;

        av_init_packet(&packet) ;
        packet.size = 0 ;
        packet.data = NULL ;
        if (av_read_frame(ifcon, &packet) < 0) {
            break;
        }

        if(packet.size<=0)
            continue;
        // 写入pts 和 dts
        if(packet.pts==AV_NOPTS_VALUE){
            //没有pts的情况
            //Write PTS
            AVRational time_base1= i_video_stream->time_base;
            //Duration between 2 frames (us)
            int64_t calc_duration=(double)AV_TIME_BASE/av_q2d(i_video_stream->r_frame_rate);
            //Parameters
            packet.pts=(double)(frame_index*calc_duration)/(double)(av_q2d(time_base1)*AV_TIME_BASE);  //计算显示时间
            packet.dts=packet.pts;
            packet.duration=(double)calc_duration/(double)(av_q2d(time_base1)*AV_TIME_BASE);       //计算视频结束时间
        }
//       if (packet.stream_index == videoindex)
//       {
//           AVRational time_base = i_video_stream->time_base;
//          AVRational time_base_q = {1,AV_TIME_BASE} ;
//           int64_t pts_time = av_rescale_q(packet.dts, time_base,time_base3);      //计算packet的PTS,将时间从一个timebase调整到另一个timebase
//           int64_t now_time = av_gettime() - start_time;                    //计算现在的时间距离开始的时间
//          if (pts_time > now_time)
//               av_usleep(pts_time - now_time);
//       }
    in_stream = ifcon->streams[packet.stream_index] ;
    out_stream = ofmt_ctx->streams [packet.stream_index] ;
    //复制包信息
    pts = packet.pts;
    dts = packet.dts;
    dur = packet.duration;

    ChangeTimeBase(&packet,in_stream->time_base,out_stream->time_base);
    if (packet.stream_index == videoindex){
        printf ("Send %8d video frames to output URL \n" , frame_index) ;
        frame_index ++;
    }
    int ret = av_write_frame(ofmt_ctx, & packet) ;

    if (ret < 0)
    {
        printf("ERROR muxing packet %d \n", ret);
    }
     if( NewSaveFile  && IsStart)
    {
     NewSaveFile = false;
     saveit = true;
     FristPacket = true;
     StaticOutFile() ;
    }
    if (NewSaveFile && saveit)
    {
        saveit = false;
        SaveVideo();

    }
    if (!NewSaveFile )
       {
        if (FristPacket)
         {start_time = pts ;
            start_timeCoding = dts;
           FristPacket = false ;
        }
       pts -= start_time ;
        dts -= start_timeCoding ;
       packet.pts = pts;
         packet.dts =dts;
          packet.duration =dur;

           ChangeTimeBase(&packet,in_stream->time_base,o_video_stream->time_base ) ;
           av_write_frame(ofcon, &packet);
    }
    av_free_packet(&packet);




    }

 avformat_close_input(&ifcon);


}
