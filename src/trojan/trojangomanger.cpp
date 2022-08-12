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

    Start(ToGoString(this->configPath));
    this->started = true;
}

void TrojanGoManger::Disconnet(){
    Stop();
    this->started = false;
    this->quit();
}

void TrojanGoManger::parseShareLink(QString shareLink, QString outPutPath){
    ParseShareLinkToJsonFile(ToGoString(shareLink), ToGoString(outPutPath));
}

GoString TrojanGoManger::ToGoString(QString str){
    return {str.toUtf8(), str.size()};
}
