The user-space C++ application is designed to communicate with /dev/traffic_policier when the driver is loaded. In the current WSL2 environment, the driver could not be compiled and loaded because matching kernel build headers are unavailable.
# System Architecture

## Token-Bucket Network Bandwidth Shaper & Traffic Policier

### 1. Overall Architecture

```text
              USER / PACKET INPUT
                       |
                       v
                  +---------+
                  | main.cpp|
                  +---------+
                       |
                       v
              +----------------+
              |  Token Bucket  |
              +----------------+
                       |
                       v
              +-------------------+
              | Traffic Policier  |
              +-------------------+
                  /           \
                 /             \
                v               v
           +---------+     +---------+
           | ALLOWED |     | DROPPED |
           +---------+     +---------+
                \               /
                 \             /
                  v           v
                 +-------------+
                 | Statistics  |
                 +-------------+
                       |
              +--------+--------+
              |                 |
              v                 v
       +-------------+   +----------------+
       | traffic.log |   | Device Driver  |
       +-------------+   +----------------+
                              |
                              v
                       +-------------+
                       | Linux Kernel|
                       +-------------+
```

### 2. Project Components

```text
+----------------------------------+
|          Token Bucket            |
|                                  |
| Capacity                         |
| Tokens                           |
| Refill Rate                      |
+----------------------------------+

+----------------------------------+
|       Traffic Policier           |
|                                  |
| Packet Check                     |
| Allow / Drop                     |
+----------------------------------+

+----------------------------------+
|          Statistics              |
|                                  |
| Total Packets                    |
| Allowed Packets                  |
| Dropped Packets                  |
| Total Bytes                      |
| Allowed Bytes                    |
| Dropped Bytes                    |
| Allow Percentage                 |
| Drop Percentage                  |
+----------------------------------+

+----------------------------------+
|       Linux Device Driver        |
|                                  |
| traffic_driver.c                 |
| /dev/traffic_policier            |
+----------------------------------+
```

### 3. File Architecture

```text
token-bucket-shaper/
│
├── src/
│   ├── main.cpp
│   ├── packet.h
│   ├── token_bucket.cpp
│   ├── token_bucket.h
│   ├── traffic_policier.cpp
│   ├── traffic_policier.h
│   ├── statistics.cpp
│   ├── statistics.h
│   └── system_info.cpp
│
├── driver/
│   ├── traffic_driver.c
│   └── Makefile
│
├── tests/
│   └── traffic_test.cpp
│
├── bin/
│
├── docs/
│   └── architecture.md
│
├── README.md
└── .gitignore
```

### 4. Data Flow

```text
Packet
  |
  v
Arrival Time
  |
  v
Token Refill
  |
  v
Available Tokens
  |
  v
Traffic Policier
  |
  +--------+
  |        |
  v        v
ALLOW    DROP
  |        |
  +---+----+
      |
      v
  Statistics
      |
      v
 Traffic Log
```

### 5. Linux Architecture

```text
+-----------------------------+
|       C++ Application       |
|          main.cpp           |
+--------------+--------------+
               |
               | write()
               v
+-----------------------------+
|   /dev/traffic_policier     |
+--------------+--------------+
               |
               v
+-----------------------------+
|    Linux Character Driver   |
|     traffic_driver.c        |
+--------------+--------------+
               |
               v
+-----------------------------+
|        Linux Kernel         |
+-----------------------------+
```

### 6. Testing

```text
TEST 1 → Normal Traffic
TEST 2 → Burst Traffic
TEST 3 → Large Packets
```

### 7. Technologies

```text
Language       → C / C++
Operating      → Linux / WSL2
Editor         → VS Code
Compiler       → g++
Version Control→ Git / GitHub
Driver         → Linux Character Device Driver
Algorithm      → Token Bucket
```

### 8. Architecture Status

```text
C++ Application       ✓
Token Bucket          ✓
Traffic Policier      ✓
Statistics            ✓
Testing               ✓
Linux System Calls   ✓
GitHub Repository     ✓
Device Driver Source  ✓
Driver Runtime        WSL2 limitation
```

