#include <iostream>
#include <fstream>
#include "packet.h"
#include "token_bucket.h"
#include "statistics.h"
#include "traffic_policier.h"
#include <fcntl.h>
#include <unistd.h>
#include <string>

void showSystemInfo();

using namespace std;

int main()
{
    showSystemInfo();

    int capacity;
    int refillRate;

    cout << endl;
    cout << "===== TOKEN BUCKET TRAFFIC POLICIER ====="
         << endl;

    // Bucket configuration
    cout << "Enter bucket capacity: ";
    cin >> capacity;

    if (cin.fail() || capacity <= 0)
    {
        cout << "Error: Bucket capacity must be greater than 0."
             << endl;
        return 1;
    }

    cout << "Enter refill rate (tokens/second): ";
    cin >> refillRate;

    if (cin.fail() || refillRate <= 0)
    {
        cout << "Error: Refill rate must be greater than 0."
             << endl;
        return 1;
    }

    TokenBucket bucket(capacity, refillRate);
    Statistics stats;
    TrafficPolicier policier;

    // Create log file
    ofstream logFile("traffic.log");

    if (!logFile)
    {
        cout << "Error: Could not create traffic.log"
             << endl;
        return 1;
    }

    logFile << "===== TOKEN BUCKET TRAFFIC LOG ====="
            << endl;

    logFile << "Bucket Capacity: "
            << capacity << endl;

    logFile << "Refill Rate: "
            << refillRate
            << " tokens/second" << endl;

    logFile << endl;

    int numberOfPackets;

    cout << "Enter number of packets: ";
    cin >> numberOfPackets;

    if (cin.fail() ||
        numberOfPackets <= 0 ||
        numberOfPackets > 100)
    {
        cout << "Error: Number of packets must be between 1 and 100."
             << endl;
        return 1;
    }

    Packet packets[100];

    // Packet input
    for (int i = 0; i < numberOfPackets; i++)
    {
        packets[i].id = i + 1;

        cout << endl;

        cout << "Enter packet "
             << packets[i].id
             << " size: ";

        cin >> packets[i].size;

        if (cin.fail() || packets[i].size <= 0)
        {
            cout << "Error: Packet size must be greater than 0."
                 << endl;
            return 1;
        }

        cout << "Enter packet "
             << packets[i].id
             << " arrival time: ";

        cin >> packets[i].arrivalTime;

        if (cin.fail() || packets[i].arrivalTime < 0)
        {
            cout << "Error: Arrival time cannot be negative."
                 << endl;
            return 1;
        }

        if (i > 0 &&
            packets[i].arrivalTime <
            packets[i - 1].arrivalTime)
        {
            cout << "Error: Arrival time must be in increasing order."
                 << endl;
            return 1;
        }
    }

    cout << endl;
    cout << "========== PACKET PROCESSING =========="
         << endl;

    logFile << "========== PACKET PROCESSING =========="
            << endl;

    // Process packets
    for (int i = 0; i < numberOfPackets; i++)
    {
        bucket.refill(packets[i].arrivalTime);

        int availableTokens = bucket.getTokens();

        cout << "Packet "
             << packets[i].id
             << " | Size: "
             << packets[i].size
             << " | Arrival Time: "
             << packets[i].arrivalTime
             << " | Tokens Available: "
             << availableTokens;

        logFile << "Packet "
                << packets[i].id
                << " | Size: "
                << packets[i].size
                << " | Arrival Time: "
                << packets[i].arrivalTime
                << " | Tokens Available: "
                << availableTokens;

        stats.totalPackets++;
        stats.totalBytes += packets[i].size;

        if (policier.checkPacket(
                packets[i].size,
                bucket.getTokens())
            && bucket.allowPacket(packets[i].size))
        {
            cout << " | ALLOWED" << endl;
            logFile << " | ALLOWED" << endl;

            stats.allowedPackets++;
            stats.allowedBytes += packets[i].size;
        }
        else
        {
            cout << " | DROPPED" << endl;
            logFile << " | DROPPED" << endl;

            stats.droppedPackets++;
            stats.droppedBytes += packets[i].size;
        }
    }

    cout << endl;

    stats.show();

    // Write report to log
    logFile << endl;

    logFile << "========== TRAFFIC REPORT =========="
            << endl;

    logFile << "Total Packets: "
            << stats.totalPackets << endl;

    logFile << "Allowed Packets: "
            << stats.allowedPackets << endl;

    logFile << "Dropped Packets: "
            << stats.droppedPackets << endl;

    logFile << "Total Bytes: "
            << stats.totalBytes << endl;

    logFile << "Allowed Bytes: "
            << stats.allowedBytes << endl;

    logFile << "Dropped Bytes: "
            << stats.droppedBytes << endl;

    if (stats.totalPackets > 0)
    {
        double allowPercentage =
            (stats.allowedPackets * 100.0)
            / stats.totalPackets;

        double dropPercentage =
            (stats.droppedPackets * 100.0)
            / stats.totalPackets;

        logFile << "Allow Percentage: "
                << allowPercentage
                << "%" << endl;

        logFile << "Drop Percentage: "
                << dropPercentage
                << "%" << endl;
    }

    logFile << "===================================="
            << endl;

    logFile.close();

    cout << endl;

    cout << "Traffic log saved to: traffic.log"
         << endl;

    int driverFd = open("/dev/traffic_policier", O_WRONLY);

    if (driverFd >= 0)
    {
        string driverMessage =
            "Total Packets: " + to_string(stats.totalPackets) +
            ", Allowed Packets: " + to_string(stats.allowedPackets) +
            ", Dropped Packets: " + to_string(stats.droppedPackets) +
            ", Total Bytes: " + to_string(stats.totalBytes);

        write(driverFd, driverMessage.c_str(), driverMessage.size());

        close(driverFd);

        cout << "Statistics sent to Linux device driver." << endl;
    }
    else
    {
        cout << "Linux device driver is not currently loaded." << endl;
    }     

    return 0;
}