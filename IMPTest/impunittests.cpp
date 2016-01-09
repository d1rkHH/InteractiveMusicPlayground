#include "effectprocessor.h"
#include "effect.h"
#include <QtTest/QtTest>
#include "imageprocessor.h"
#include "soundcontrol.h"
#include <opencv2/opencv.hpp>

//Unit tests for some methods of the InteractiveMusicPlayground project
class IMPUnitTests : public QObject
{
    Q_OBJECT

private slots:
    void effectStrength();
    void testProcess();

    void init();
    void cleanup();

private:
    EffectProcessor* e;
    SoundControl* s;
    ImageProcessor* p;

};

void IMPUnitTests::init(){
    e = new EffectProcessor();
    e->setHeight(480);
    e->setWidth(640);
    double ratio = 640.0/480.0;
    e->setRatio(ratio);
}

//Used to safely get debug output without crashing the program
//(Because process gets called so often, the program crashes if you put any debug messages in there.
//This way, you can just call the method one time and get a debug output)
void IMPUnitTests::testProcess(){
    s = new SoundControl();
    p = new ImageProcessor(s);
    QCOMPARE(1,1);
}


void IMPUnitTests::effectStrength(){
    e->setChipCenter(Point(50,480));
    float f = e->calculateEffectStrength(Point(0,640));
    QCOMPARE(f, 0.90125f);
}

void IMPUnitTests::cleanup(){
    delete e;
}


QTEST_MAIN(IMPUnitTests)
#include "impunittests.moc"
