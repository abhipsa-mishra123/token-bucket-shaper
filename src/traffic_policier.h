#ifndef TRAFFIC_POLICIER_H
#define TRAFFIC_POLICIER_H

class TrafficPolicier {
public:
    bool checkPacket(int packetSize, int availableTokens);
};

#endif