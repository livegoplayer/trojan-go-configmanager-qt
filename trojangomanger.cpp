#include "trojangomanger.h"
#include "qdebug.h"
#include "trojan-go-start.h"

void TrojanGoManger::run() {
    Start();
//    qDebug() << QThread::currentThread();
}

void TrojanGoManger::Disconnet(){
    Stop();
}
