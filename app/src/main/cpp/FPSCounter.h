#ifndef FPS_COUNTER_H
#define FPS_COUNTER_H

class FPSCounter {
public:
    explicit FPSCounter(const char* tag = "FPS");
    void tick();

private:
    int frameCount;
    long long startTimeMs;
    const char* logTag;

    long long currentTimeMillis();
};

#endif // FPS_COUNTER_H