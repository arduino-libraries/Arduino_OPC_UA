:floppy_disk: `Arduino_open62541`
=================================
[![Compile Examples](https://github.com/bcmi-labs/Arduino_open62541/workflows/Compile%20Examples/badge.svg)](https://github.com/bcmi-labs/Arduino_open62541/actions?workflow=Compile+Examples)
[![Arduino Lint](https://github.com/bcmi-labs/Arduino_open62541/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/bcmi-labs/Arduino_open62541/actions/workflows/arduino-lint.yml)
[![Sync Labels status](https://github.com/bcmi-labs/Arduino_open62541/actions/workflows/sync-labels.yml/badge.svg)](https://github.com/bcmi-labs/Arduino_open62541/actions/workflows/sync-labels.yml)

This library provides an implementation of [OPC/UA](https://en.wikipedia.org/wiki/OPC_Unified_Architecture) by porting the Fraunhofer [`open62541`](https://github.com/open62541/open62541) for the Arduino [Opta](https://www.arduino.cc/pro/hardware-arduino-opta/) `microPLC` family.

### How-to-OPC/UA
* Compile and upload [`examples/opcua_server`](examples/opcua_server/opcua_server.ino)
```bash
arduino-cli compile --fqbn arduino:mbed_opta:opta -v examples/opcua_server -u -p /dev/ttyACM0
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
* Connect to OPC/UA server using IP/port as printed by the Arduino Opta
![image](https://github.com/bcmi-labs/Arduino_open62541/assets/3931733/ac153e79-6648-4808-9c4f-17aaf4305d89)

### How-to-`opcua-client-gui`
```bash
cd /tmp
git clone https://github.com/FreeOpcUa/opcua-client-gui && cd opcua-client-gui
python3 -m pip install --upgrade pyopenssl
python3 -m pip install --upgrade .
```
