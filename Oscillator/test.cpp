#include "envelope.h"

#include <QDebug>
#include <QApplication>


int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    Envelope envelope;

    envelope.setSampleRate(1000);
    envelope.setAttackSeconds(0.01);
    envelope.setDecaySeconds(.02);
    envelope.setReleaseSeconds(.1);
    envelope.setSustain_dB(-6);


    envelope.setState(Envelope::ATTACK);

    for(int i = 0; i < 2000; i++){
        qDebug()   << envelope.process(1);
    }
    envelope.setState(Envelope::RELEASE);
    for(int i = 2000; i < 3000; i++){
        qDebug()   << envelope.process(1);
    }

}

