#include "service.h"

Service::Service(QObject *parent) : QObject(parent)
{
    server = new MaiaXmlRpcServer(8765,this);
    server->addMethod("examples.SaveFile",this,"SaveFile");
    server->addMethod("examples.CreateFile", this, "CreateFile");
    test.start();
}



string Service::SaveFile(){
    mutex.lock();
    if (! test.StopFFmpeg())
        return "false";
    cansave = true;
    mutex.unlock();
    return "OK";
}


bool Service::CreateFile(string FileName){
    mutex.lock();
     if(!test.SaveFile(FileName))
             return false;
     test.MoveOn();
     cansave = false;
      mutex.unlock();
      return true;
}
