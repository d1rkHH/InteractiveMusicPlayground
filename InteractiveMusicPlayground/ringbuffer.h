#ifndef __RINGBUFFER_H
#define __RINGBUFFER_H

#include <vector>

class RingBuffer{

public:
    RingBuffer();
    void write(float sample);
    float readWithDelay(int delay);
    void resize(int size);
private:
    std::vector<float> buffer;
    int writeIndex;
    int size;
};
#endif
