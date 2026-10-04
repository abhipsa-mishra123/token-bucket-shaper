# Execution Instructions

## Environment

```text
Operating System : Linux / WSL2 Ubuntu
Language         : C++
Compiler         : g++
Editor           : VS Code
Version Control  : Git
Repository       : GitHub
```

## Project Directory

```bash
cd ~/token-bucket-shaper
```

## Compile Main Application

```bash
g++ src/main.cpp src/token_bucket.cpp src/statistics.cpp src/traffic_policier.cpp src/system_info.cpp -o bin/traffic_policier
```

## Run Main Application

```bash
./bin/traffic_policier
```

## Compile Tests

```bash
g++ tests/traffic_test.cpp src/token_bucket.cpp src/statistics.cpp src/traffic_policier.cpp -o bin/traffic_test
```

## Run Tests

```bash
./bin/traffic_test
```

## Linux Device Driver

Driver source:

```text
driver/traffic_driver.c
```

Driver build file:

```text
driver/Makefile
```

Device:

```text
/dev/traffic_policier
```

The C++ application attempts to communicate with the device driver when the driver is loaded.

The current WSL2 environment does not provide matching kernel build headers, so the driver cannot currently be compiled and loaded in this environment.

## GitHub

```bash
git status
git add .
git commit -m "Update project documentation"
git push
```
