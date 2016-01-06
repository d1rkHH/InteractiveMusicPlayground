#include "effectprocessor.h"
#include "effect.h"
#include <QtTest/QtTest>

class IMPUnitTests : public QObject
{
    Q_OBJECT

public:
    EffectProcessor* e;
private slots:
    //Left upper quadrant
    void effectStrength1();
    void effectStrength2();
    void effectStrength3();
    void effectStrength4();
    void effectStrength5();
    //Left lower quadrant
    void effectStrength6();
    void effectStrength7();
    void effectStrength8();
    void effectStrength9();
    void effectStrength10();
    void init();
    void cleanup();

};

void IMPUnitTests::init(){
    e = new EffectProcessor();
    e->setHeight(480);
    e->setWidth(640);
    double ratio = 640.0/480.0;
    e->setRatio(ratio);
}

//Left upper quadrant
void IMPUnitTests::effectStrength1(){
    e->setChipCenter(Point(50,480));
    float f = e->calculateEffectStrength(Point(0,640));
    QCOMPARE(f, 1.0f);
}

void IMPUnitTests::effectStrength2(){
    e->setChipCenter(Point(100,440));
    float f = e->calculateEffectStrength(Point(0,640));
    QCOMPARE(f, 0.0f);
}

void IMPUnitTests::effectStrength3(){
    e->setChipCenter(Point(10,400));
    float f = e->calculateEffectStrength(Point(0,640));
    QCOMPARE(f, 0.0f);
}

void IMPUnitTests::effectStrength4(){
    e->setChipCenter(Point(10,380));
    float f = e->calculateEffectStrength(Point(0,640));
    QCOMPARE(f, 0.0f);
}

void IMPUnitTests::effectStrength5(){
    e->setChipCenter(Point(100,370));
    float f = e->calculateEffectStrength(Point(0,640));
    QCOMPARE(f, 0.0f);
}

void IMPUnitTests::effectStrength6(){
    e->setChipCenter(Point(300,340));
    float f = e->calculateEffectStrength(Point(0,640));
    QCOMPARE(f, 1.0f);
}

void IMPUnitTests::effectStrength7(){
    e->setChipCenter(Point(300, 300));
    float f = e->calculateEffectStrength(Point(0,640));
    QCOMPARE(f, 0.0f);
}

void IMPUnitTests::effectStrength8(){
    e->setChipCenter(Point(280, 280));
    float f = e->calculateEffectStrength(Point(0,640));
    QCOMPARE(f, 0.5f);
}

void IMPUnitTests::effectStrength9(){
    e->setChipCenter(Point(250, 250));
    float f = e->calculateEffectStrength(Point(0,640));
    QCOMPARE(f, 0.0f);
}

void IMPUnitTests::effectStrength10(){
    e->setChipCenter(Point(240,240));
    float f = e->calculateEffectStrength(Point(0,640));
    QCOMPARE(f, 0.0f);
}



void IMPUnitTests::cleanup(){
    delete e;
    e = 0;
}


QTEST_MAIN(IMPUnitTests)
#include "impunittests.moc"
