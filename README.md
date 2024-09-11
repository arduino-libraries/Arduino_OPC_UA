:floppy_disk: `Arduino_OPC_UA`
==============================
[![Compile Examples](https://github.com/bcmi-labs/Arduino_OPC_UA/workflows/Compile%20Examples/badge.svg)](https://github.com/bcmi-labs/Arduino_OPC_UA/actions?workflow=Compile+Examples)
[![Arduino Lint](https://github.com/bcmi-labs/Arduino_OPC_UA/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/bcmi-labs/Arduino_OPC_UA/actions/workflows/arduino-lint.yml)
[![Sync Labels status](https://github.com/bcmi-labs/Arduino_OPC_UA/actions/workflows/sync-labels.yml/badge.svg)](https://github.com/bcmi-labs/Arduino_OPC_UA/actions/workflows/sync-labels.yml)

This library provides an implementation of [OPC UA](https://en.wikipedia.org/wiki/OPC_Unified_Architecture) by porting the Fraunhofer [`open62541`](https://github.com/open62541/open62541) for the Arduino [Opta](https://www.arduino.cc/pro/hardware-arduino-opta/) `microPLC` family.

Furthermore, the library supports automatic detection, configuration and exposure of up to two Arduino Opta Expansion Boards (i.e. Digital Expansion w/ mechanical relays [`D1608E`](https://store.arduino.cc/products/opta-ext-d1608e), Digital Expansion w/ solid-state relays [`D1608S`](https://store.arduino.cc/products/opta-ext-d1608e), Analog Expansion [`A0602`](https://store.arduino.cc/products/opta-ext-a0602)) via OPC UA.

### How-to-OPC UA
* Compile and upload [`examples/opta_opcua_server`](examples/opta_opcua_server/opta_opcua_server.ino)
```bash
arduino-cli compile --fqbn arduino:mbed_opta:opta -v examples/opta_opcua_server -u -p /dev/ttyACM0
```
* Connect Arduino Opta Ethernet port with a [DHCP](https://en.wikipedia.org/wiki/Dynamic_Host_Configuration_Protocol)-enabled router, switch, etc.
* Open a serial monitor
```bash
$ cat /dev/ttyACM0 
[2024-06-21 02:30:19.000 (UTC+0000)] info/eventloop	Starting the EventLoop
[2024-06-21 02:30:19.000 (UTC+0000)] warn/server	AccessControl: Unconfigured AccessControl. Users have all permissions.
[2024-06-21 02:30:19.000 (UTC+0000)] info/server	AccessControl: Anonymous login is enabled
[2024-06-21 02:30:19.000 (UTC+0000)] warn/server	x509 Certificate Authentication configured, but no encrypting SecurityPolicy. This can leak credentials on the network.
[2024-06-21 02:30:19.000 (UTC+0000)] info/server	Arduino Opta IP: 192.168.8.137
[2024-06-21 02:30:19.000 (UTC+0000)] info/server	Arduino Opta Variant: Arduino Opta WiFi
[2024-06-21 02:30:19.000 (UTC+0000)] info/server	stack: size = 16384 | free = 14936 | used = 1448 | max = 5124
[2024-06-21 02:30:19.000 (UTC+0000)] info/server	o1heap: capacity: 261984 | allocated: 66784 | peak_allocated: 68896
[2024-06-21 02:30:19.000 (UTC+0000)] warn/server	Maximum SecureChannels count not enough for the maximum Sessions count
[2024-06-21 02:30:19.000 (UTC+0000)] info/network	TCP	| Listening on all interfaces
[2024-06-21 02:30:19.000 (UTC+0000)] info/network	TCP 604353888	| Creating listen socket for "127.0.0.1" (with local hostname "192.168.8.137") on port 4840
[2024-06-21 02:30:19.000 (UTC+0000)] info/server	New DiscoveryUrl added: opc.tcp://192.168.8.137:4840
```
* Connect to OPC UA server using IP/port as printed by the Arduino Opta
![image](https://github.com/bcmi-labs/Arduino_OPC_UA/assets/3931733/ac153e79-6648-4808-9c4f-17aaf4305d89)

### How-to-`opcua-client-gui`
```bash
cd /tmp
git clone https://github.com/FreeOpcUa/opcua-client-gui && cd opcua-client-gui
python3 -m pip install --upgrade pyopenssl
python3 -m pip install --upgrade .
```

### How-to-enable detailed heap/stack memory debugging information
* Edit [`variants/OPTA/conf/mbed_app.json`](https://github.com/arduino/ArduinoCore-mbed/blob/main/variants/OPTA/conf/mbed_app.json)
```diff
"target.macros_add": [
  ...
+  "MBED_HEAP_STATS_ENABLED=1",
+  "MBED_STACK_STATS_ENABLED=1",
+  "MBED_MEM_TRACING_ENABLED=1"
```
* Recompile `libmbed.a`
```bash
cd ArduinoCore-mbed
./mbed-os-to-arduino -a -g OPTA:OPTA
```
