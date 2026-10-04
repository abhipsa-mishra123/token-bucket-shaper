Token-Bucket Network Bandwidth Shaper & Traffic Policier

1. Project Overview

This project implements a Token-Bucket based network bandwidth shaper and traffic policier using C++ on Linux.

The system controls network packet traffic based on the number of available tokens in a token bucket. Packets are allowed when enough tokens are available. If there are not enough tokens, the packets are dropped.

The project also records traffic statistics and stores packet processing information in a log file.

2. Objectives

- Implement the Token-Bucket algorithm.
- Control packet traffic using available tokens.
- Allow or drop packets according to bucket capacity.
- Support configurable bucket capacity and refill rate.
- Collect packet traffic statistics.
- Calculate allowed and dropped packet percentages.
- Calculate average packet size.
- Store traffic information in a log file.
- Use Linux system programming concepts.
- Test normal, burst, and large packet traffic.

3. Technologies Used

- C++
- Linux
- GCC / G++
- Linux system calls
- Token-Bucket algorithm
- File handling
- Object-Oriented Programming

4. Project Structure

token-bucket-shaper/
├── bin/
├── docs/
├── src/
│   ├── main.cpp
│   ├── packet.h
│   ├── statistics.cpp
│   ├── statistics.h
│   ├── system_info.cpp
│   ├── token_bucket.cpp
│   ├── token_bucket.h
│   ├── traffic_policier.cpp
│   └── traffic_policier.h
├── tests/
│   └── traffic_test.cpp
├── traffic.log
└── README.md

5. Main Components

Token Bucket

The token bucket controls how much traffic can pass through the system.

Traffic Policier

The traffic policier checks whether a packet can be allowed based on the available tokens.

Statistics

The statistics module calculates:

- Total packets
- Allowed packets
- Dropped packets
- Total bytes
- Allowed bytes
- Dropped bytes
- Allow percentage
- Drop percentage
- Average packet size

Linux System Information

The system information module displays:

- Process ID
- User ID
- Operating System
- Current working directory

Traffic Logging

Packet processing information is stored in:

traffic.log

6. Compilation

Open a Linux terminal and enter the project directory:

cd ~/token-bucket-shaper

Compile the main program:

g++ src/main.cpp src/token_bucket.cpp src/statistics.cpp src/traffic_policier.cpp src/system_info.cpp -o bin/traffic_policier

7. Running the Program

Run:

./bin/traffic_policier

The program asks for:

- Bucket capacity
- Token refill rate
- Number of packets
- Packet size
- Packet arrival time

8. Running Tests

Compile the test program:

g++ tests/traffic_test.cpp src/token_bucket.cpp src/statistics.cpp src/traffic_policier.cpp -o bin/traffic_test

Run:

./bin/traffic_test

The test program contains:

- Normal traffic test
- Burst traffic test
- Large packet test

9. Logging

After running the main program, traffic information is stored in:

traffic.log

To view the log:

cat traffic.log

10. Sample Test Results

Normal Traffic

- Total packets: 5
- Allowed packets: 5
- Dropped packets: 0
- Allow percentage: 100%

Burst Traffic

- Total packets: 5
- Allowed packets: 2
- Dropped packets: 3
- Allow percentage: 40%
- Drop percentage: 60%

Large Packets

- Total packets: 4
- Allowed packets: 2
- Dropped packets: 2
- Allow percentage: 50%
- Drop percentage: 50%

11. Linux Features

The project uses Linux system programming functionality such as:

- "getpid()" to obtain the process ID.
- "getuid()" to obtain the user ID.
- "getcwd()" to obtain the current working directory.

12. Input Validation

The program validates user input such as:

- Bucket capacity must be greater than zero.
- Refill rate must be greater than zero.
- Packet count must be within the allowed range.
- Packet size must be greater than zero.
- Packet arrival time must not be negative.
- Packet arrival times must be in non-decreasing order.

13. Conclusion

The project demonstrates a C++ implementation of a Token-Bucket based network bandwidth shaper and traffic policier on Linux.

It combines traffic control, packet processing, statistics, logging, input validation, testing, and Linux system programming concepts in a single project.
