#include "networkhelper.h"
#include "qdebug.h"

#include <QProcess>
#include <QString>

NetworkHelper::NetworkHelper()
{

}

int NetworkHelper::Ping(QString ip)
{
  QProcess exc;


  QString cmdstr = "ping " + ip + " -n 1\n"; //ping 192.168.15.90  -n 2 -w 4000
  while ( true )
  {
    exc.start("cmd", QStringList() << "/c" << cmdstr);
    exc.waitForStarted();
    exc.waitForFinished(); //等待ping完成
    QString outstr = QString::fromLocal8Bit(exc.readAllStandardOutput());
    qDebug() << outstr;
    //返回不等于-1，说明ping结果包含"往返行程的估计时间"字段，则说明ping成功，网络可达;等于-1，表示没有此字段，说明ping不通
    QString test = "ms";
    int flag = outstr.indexOf( test );
    if ( ( -1 != flag ) )
    {
      int start_num = flag - 1;
      while ( true )
      {
        if ( outstr.mid( start_num - 1, 1 ) == "<" || outstr.mid( start_num - 1, 1 ) == "=" )
        {
          break;
        }
        start_num --;
      }
      QString time = outstr.mid( start_num, flag - start_num );
      return time.toInt();
    }
    else
    {
      return 0;
    }
  }
}
