#include "ffmpegthread.h"
#include <iostream>
FFmpegThread::FFmpegThread()
{


}

bool FFmpegThread::StopFFmpeg(){
   if(!test.Stop() )
        {cout<< "FFmpeg Stop false" <<endl;
          return false;}
   return true;

}

void FFmpegThread::run(){
  if (! test.Start()) {
      cout<< "FFmpeg start false" <<endl;

  }

}


bool FFmpegThread::SaveFile(string FileName){
    if(!test.SaveVdieoPath(FileName))
    {
        cout<<"FFmpegThread::SaveFile false"<<endl;
        return false;
    }
    return true;
}


void FFmpegThread::MoveOn(){
  test.MoveOn();
}
