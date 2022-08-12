#ifndef TROJANGOMANGER_H
#define TROJANGOMANGER_H

#include <QThread>
#include "src/trojan/trojan-go-start.h"


class TrojanGoManger : public QThread
{
public:
    void Disconnet();
    TrojanGoManger(QString configPath);
    ~TrojanGoManger();
    static GoString ToGoString(QString str);
    static void parseShareLink(QString shareLink, QString outPutPath);
protected:
    void run();
private:
    QString configPath;
    int started;
};

#endif // TROJANGOMANGER_H
