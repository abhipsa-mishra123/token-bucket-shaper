#include <iostream>
#include <iomanip>
#include "statistics.h"

using namespace std;

Statistics::Statistics()
{
    totalPackets = 0;
    allowedPackets = 0;
    droppedPackets = 0;

    totalBytes = 0;
    allowedBytes = 0;
    droppedBytes = 0;
}

void Statistics::show()
{
    cout << "========== TRAFFIC REPORT =========="
         << endl;

    cout << "Total Packets: "
         << totalPackets << endl;

    cout << "Allowed Packets: "
         << allowedPackets << endl;

    cout << "Dropped Packets: "
         << droppedPackets << endl;

    cout << "Total Bytes: "
         << totalBytes << endl;

    cout << "Allowed Bytes: "
         << allowedBytes << endl;

    cout << "Dropped Bytes: "
         << droppedBytes << endl;

    if (totalPackets > 0)
    {
        double allowPercentage =
            (allowedPackets * 100.0) / totalPackets;

        double dropPercentage =
            (droppedPackets * 100.0) / totalPackets;

        double averagePacketSize =
            static_cast<double>(totalBytes) / totalPackets;

        cout << fixed << setprecision(2);

        cout << "Allow Percentage: "
             << allowPercentage << "%" << endl;

        cout << "Drop Percentage: "
             << dropPercentage << "%" << endl;

        cout << "Average Packet Size: "
             << averagePacketSize << " bytes" << endl;
    }

    cout << "===================================="
         << endl;
}