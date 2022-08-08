#ifndef TROJANGOMANGER_H
#define TROJANGOMANGER_H

#include <QThread>



class TrojanGoManger : public QThread
{
public:
    void Disconnet();
protected:
    void run();
};

#endif // TROJANGOMANGER_H
