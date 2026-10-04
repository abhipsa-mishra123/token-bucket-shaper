#include "token_bucket.h"

TokenBucket::TokenBucket(int cap, int rate) {
    capacity = cap;
    tokens = cap;
    refillRate = rate;
}

void TokenBucket::addTokens(int amount) {
    tokens += amount;

    if (tokens > capacity) {
        tokens = capacity;
    }
}

bool TokenBucket::allowPacket(int packetSize) {
    if (packetSize <= tokens) {
        tokens -= packetSize;
        return true;
    }

    return false;
}
int TokenBucket::getTokens()
{
    return tokens;
}
void TokenBucket::refill(double currentTime)
{
    static double lastTime = 0.0;

    double elapsedTime = currentTime - lastTime;

    if (elapsedTime > 0)
    {
        int newTokens = static_cast<int>(elapsedTime * refillRate);

        addTokens(newTokens);

        lastTime = currentTime;
    }
}