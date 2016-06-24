#include "service.h"
#include <QVariant>
Service::Service(QObject *parent) : QObject(parent)
{
    server = new MaiaXmlRpcServer(8082, this);
    server->addMethod("examples.birne", this, "birne");
    server->addMethod("examples.nix", this, "nix");
    server->addMethod("examples.plusOneYear", this, "plusOneYear");
    server->addMethod("examples.SaveFile",this,"SaveFile");
    server->addMethod("examples.CreateFile", this, "CreateFile");
    server->addMethod("examples.getStateName", this, "callState");

        test.start();
}



QString Service::SaveFile(){

    mutex.lock();
    if (! test.StopFFmpeg())
        return "false";
    cansave = true;
    mutex.unlock();
    return "OK";




}


bool Service::CreateFile(QString FileName){
    mutex.lock();
     if(!test.SaveFile(FileName.toStdString()))
             return false;
     test.MoveOn();
     cansave = false;
      mutex.unlock();
      return true;
}


QString Service::callState(int i) {
    if(i < 42)
        return "Banane";
    else
        return "Orange";
}

QVariant Service::birne(int x) {
    if(x < 0)
        return QVariant::fromValue(MaiaFault(7, "Birne is doof"));
    else
        return "Tolle Birne";
}

void Service::nix() {
    qDebug() << "i got called";
}

QDateTime Service::plusOneYear(QDateTime sometime) {
    return sometime.addYears(1);
}
