#include "traffic_policier.h"

bool TrafficPolicier::checkPacket(int packetSize, int availableTokens) {
    if (packetSize <= availableTokens) {
        return true;
    }

    return false;
}