# Project Requirements

## Token-Bucket Network Bandwidth Shaper & Traffic Policier

## 1. Objective

* Control network traffic
* Limit packet transmission
* Manage available bandwidth
* Allow valid packets
* Drop packets when tokens are insufficient
* Collect traffic statistics

## 2. Problem Statement

* Uncontrolled traffic can cause congestion
* Large traffic bursts can overload resources
* A bandwidth control mechanism is required
* Token Bucket is used for traffic control

## 3. Scope

* Packet traffic control
* Token management
* Packet allow/drop decision
* Traffic statistics
* Linux system information
* Linux device driver integration
* Traffic logging
* Testing

## 4. Functional Requirements

* Accept bucket capacity
* Accept token refill rate
* Accept packet size
* Accept packet arrival time
* Refill tokens
* Check available tokens
* Allow packets when sufficient tokens are available
* Drop packets when tokens are insufficient
* Calculate traffic statistics
* Display traffic results
* Send statistics to the Linux device driver when available

## 5. Non-Functional Requirements

* Linux-based
* C/C++ implementation
* Simple command-line interface
* Modular source code
* Reliable packet processing
* Easy testing
* GitHub-based project management

## 6. Main Modules

```text
+----------------------+
|      main.cpp        |
+----------+-----------+
           |
           v
+----------------------+
|    Token Bucket      |
+----------+-----------+
           |
           v
+----------------------+
|  Traffic Policier    |
+----------+-----------+
           |
           v
+----------------------+
|     Statistics       |
+----------+-----------+
           |
           +----------------+
           |                |
           v                v
     traffic.log     Linux Driver
```

## 7. Expected Outcome

* Controlled packet traffic
* Correct allow/drop decisions
* Accurate traffic statistics
* Linux system information
* Linux device driver source
* Tested and documented project
