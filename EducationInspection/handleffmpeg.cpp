#include "handleffmpeg.h"
#include <fstream>
#include <iostream>
using namespace std ;
HandleFfmpeg::HandleFfmpeg(string FileName) :IsStart(false),partK(1), HasInditial(false), NewSaveFile(false)
{
    av_register_all();                                    //初始化注册所有要用的编码器解码器等
    avformat_network_init();                              //初始化网络流
    InputName = "rtsp://192.168.2.12/1" ;                //媒体流输入端
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
    if ( avformat_open_input(&ifcon,InputName , fmt , option) < 0 )
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

    if ((avformat_find_stream_info(ifcon , option)) < 0 ) {
        printf ("There is no information in that open") ;
        return false;
    }
    return true;
}

/*查找该格式文件中是否有视频流，如果有將它賦值給i_video_stream，找不到直接返回false*/
bool HandleFfmpeg::GetVeidoStream(){
  
    //查找视频流的Index
    for (int i =0 ; i < ifcon->nb_streams ; i++){
        if ( ifcon->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO ){
       
            i_video_stream = ifcon->streams[i] ;
            return true ;
        }
    }
    return false ;
}


bool HandleFfmpeg::CheckInformation(){
    av_dump_format(ifcon, 0, InputName, 0);                              //该函数的作用就是检查下初始化过程中设置的参数是否符合规范
    avformat_alloc_output_context2(&ofcon ,NULL ,NULL, SavePath.c_str()) ;       //新建输入端
    if (!ofcon) {
        printf( "Could not create output context\n");
       return false;
    }
    return true;
}

bool HandleFfmpeg::CopyInformation(){
    o_video_stream = avformat_new_stream(ofcon, i_video_stream->codec->codec);
            if (!o_video_stream) {
                printf( "Failed allocating output stream\n");
            return false ;
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

/*开始推流*/
void HandleFfmpeg::StartStream(){

    if (!StaticOutFile()) return ;

    int last_pts = 0;
    int last_dts = 0;
    int64_t pts, dts;

     IsStart = true ;
     int i =0;
     bool saveit = true;
     while(1) {
    i++;

        av_init_packet(&packet) ;
        packet.size = 0 ;
        packet.data = NULL ;
        if (av_read_frame(ifcon, &packet) < 0) {
            break;
        }

     dts = packet.dts ;
     packet.dts += last_dts ;
    packet.stream_index = 0 ;
     if( NewSaveFile  && IsStart)
    {
     NewSaveFile = false;
     saveit = true;
     StaticOutFile() ;
    }
    if (NewSaveFile && saveit)
    {
        saveit = false;
        SaveVideo();

    }
    if (!NewSaveFile )
       { AVStream *st = ofcon->streams[1];
       if ( !(st->priv_pts))
        cout<<"donnes has it"<<endl;
           av_interleaved_write_frame(ofcon, &packet);}
    }

 avformat_close_input(&ifcon);


}
