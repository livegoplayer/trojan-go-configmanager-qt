#include "src/trojan/trojangomanger.h"
#include "qdebug.h"
#include "src/trojan/trojan-go-start.h"

TrojanGoManger::TrojanGoManger(QString configPath) {
    this->configPath = configPath;
    this->started = false;
}

TrojanGoManger::~TrojanGoManger() {
    this->Disconnet();
}

void TrojanGoManger::run() {
    if (this->started) {
        this->Disconnet();
    }
    char buf[this->configPath.size()];
    for (int i=0;i<configPath.size();i++) {
        buf[i] = this->configPath[i].unicode();
    }
    Start({buf, this->configPath.size()});
    this->started = true;
}

void TrojanGoManger::Disconnet(){
    Stop();
    this->started = false;
    this->quit();
}
