# Testing Documentation

## Token-Bucket Network Bandwidth Shaper & Traffic Policier

## Test 1 — Normal Traffic

```text
Packets       : 5
Allowed      : 5
Dropped      : 0
Total Bytes  : 500
Allowed Bytes: 500
Dropped Bytes: 0
```

Result:

```text
PASS
```

## Test 2 — Burst Traffic

```text
Packets       : 5
Allowed      : 2
Dropped      : 3
Total Bytes  : 1000
Allowed Bytes: 400
Dropped Bytes: 600
```

Result:

```text
PASS
```

## Test 3 — Large Packets

```text
Packets       : 4
Allowed      : 2
Dropped      : 2
Total Bytes  : 1900
Allowed Bytes: 500
Dropped Bytes: 1400
```

Result:

```text
PASS
```

## Testing Summary

```text
+------------------+--------+
| Test             | Result |
+------------------+--------+
| Normal Traffic   | PASS   |
| Burst Traffic    | PASS   |
| Large Packets    | PASS   |
+------------------+--------+
```
