#ifndef NETWORKHELPER_H
#define NETWORKHELPER_H

#include <QThread>


class NetworkHelper
{
public:
    NetworkHelper();
    static int Ping(QString ip);
};





#endif // NETWORKHELPER_H
