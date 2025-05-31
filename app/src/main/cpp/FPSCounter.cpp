#include "FPSCounter.h"
#include <android/log.h>
#include <chrono>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "FPS", __VA_ARGS__)

FPSCounter::FPSCounter(const char* tag)
        : frameCount(0), startTimeMs(currentTimeMillis()), logTag(tag) {}

void FPSCounter::tick() {
    ++frameCount;
    long long now = currentTimeMillis();
    double elapsedSec = (now - startTimeMs) / 1000.0;

    if (elapsedSec >= 1.0) {
        double fps = frameCount / elapsedSec;
        LOGI("%s: %.2f fps", logTag, fps);
        frameCount = 0;
        startTimeMs = now;
    }
}

long long FPSCounter::currentTimeMillis() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(
            steady_clock::now().time_since_epoch()
    ).count();
}