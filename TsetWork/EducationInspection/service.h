#ifndef SERVICE_H
#define SERVICE_H
#include "ffmpegthread.h"
#include "handleffmpeg.h"
#include <QObject>
#include "maiaXmlRpcServer.h"
#include <string>
using namespace std;

class Service : public QObject
{
    Q_OBJECT
public:
    explicit Service(QObject *parent = 0);

private slots:
    QString SaveFile() ;
    bool CreateFile(QString FileName);
    QString callState(int i);
    QVariant birne(int x);
    void nix();
    QDateTime plusOneYear(QDateTime sometime);

public slots:
private :
    Service(const Service& );

    MaiaXmlRpcServer *server;
     FFmpegThread test;
     bool cansave = false;
     QMutex mutex;
};

#endif // SERVICE_H
