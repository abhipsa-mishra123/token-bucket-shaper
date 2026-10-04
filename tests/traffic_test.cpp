#include <iostream>
#include "../src/packet.h"
#include "../src/token_bucket.h"
#include "../src/statistics.h"
#include "../src/traffic_policier.h"

using namespace std;

void runTest(
    const string& testName,
    Packet packets[],
    int numberOfPackets,
    int capacity,
    int refillRate)
{
    cout << endl;
    cout << "========================================" << endl;
    cout << testName << endl;
    cout << "========================================" << endl;

    TokenBucket bucket(capacity, refillRate);
    Statistics stats;
    TrafficPolicier policier;

    for (int i = 0; i < numberOfPackets; i++)
    {
        bucket.refill(packets[i].arrivalTime);

        cout << "Packet " << packets[i].id
             << " | Size: " << packets[i].size
             << " | Tokens: " << bucket.getTokens();

        stats.totalPackets++;
        stats.totalBytes += packets[i].size;

        if (policier.checkPacket(
                packets[i].size,
                bucket.getTokens())
            && bucket.allowPacket(packets[i].size))
        {
            cout << " | ALLOWED" << endl;

            stats.allowedPackets++;
            stats.allowedBytes += packets[i].size;
        }
        else
        {
            cout << " | DROPPED" << endl;

            stats.droppedPackets++;
            stats.droppedBytes += packets[i].size;
        }
    }

    stats.show();
}

int main()
{
    int capacity = 500;
    int refillRate = 100;

    // Test 1: Normal traffic
    Packet normalTraffic[] =
    {
        {1, 100, 0.0},
        {2, 100, 1.0},
        {3, 100, 2.0},
        {4, 100, 3.0},
        {5, 100, 4.0}
    };

    runTest(
        "TEST 1: NORMAL TRAFFIC",
        normalTraffic,
        5,
        capacity,
        refillRate
    );

    // Test 2: Burst traffic
    Packet burstTraffic[] =
    {
        {1, 200, 0.0},
        {2, 200, 0.1},
        {3, 200, 0.2},
        {4, 200, 0.3},
        {5, 200, 0.4}
    };

    runTest(
        "TEST 2: BURST TRAFFIC",
        burstTraffic,
        5,
        capacity,
        refillRate
    );

    // Test 3: Large packets
    Packet largePackets[] =
    {
        {1, 400, 0.0},
        {2, 600, 1.0},
        {3, 800, 2.0},
        {4, 100, 3.0}
    };

    runTest(
        "TEST 3: LARGE PACKETS",
        largePackets,
        4,
        capacity,
        refillRate
    );

    return 0;
}