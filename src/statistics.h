#ifndef STATISTICS_H
#define STATISTICS_H

class Statistics
{
public:
    int totalPackets;
    int allowedPackets;
    int droppedPackets;

    int totalBytes;
    int allowedBytes;
    int droppedBytes;

    Statistics();

    void show();
};

#endif