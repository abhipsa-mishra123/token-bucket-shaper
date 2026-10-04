#ifndef TOKEN_BUCKET_H
#define TOKEN_BUCKET_H

class TokenBucket {
private:
    int capacity;
    int tokens;
    int refillRate;

public:
    TokenBucket(int cap, int rate);

    void addTokens(int amount);
    bool allowPacket(int packetSize);
    int getTokens();
    void refill(double currentTime);
};

#endif