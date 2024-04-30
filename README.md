:floppy_disk: `Arduino_open62541`
=================================
[![Compile Examples](https://github.com/bcmi-labs/Arduino_open62541/workflows/Compile%20Examples/badge.svg)](https://github.com/bcmi-labs/Arduino_open62541/actions?workflow=Compile+Examples)
[![Arduino Lint](https://github.com/bcmi-labs/Arduino_open62541/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/bcmi-labs/Arduino_open62541/actions/workflows/arduino-lint.yml)
[![Sync Labels status](https://github.com/bcmi-labs/Arduino_open62541/actions/workflows/sync-labels.yml/badge.svg)](https://github.com/bcmi-labs/Arduino_open62541/actions/workflows/sync-labels.yml)

This library provides an implementation of [OPC/UA](https://en.wikipedia.org/wiki/OPC_Unified_Architecture) by porting the Fraunhofer [`open62541`](https://github.com/open62541/open62541) for the Arduino [Opta](https://www.arduino.cc/pro/hardware-arduino-opta/) `microPLC` family.

### How-to-`opcua-client-gui`
```bash
cd /tmp
git clone https://github.com/FreeOpcUa/opcua-client-gui && cd opcua-client-gui
python3 -m pip install --upgrade pyopenssl
python3 -m pip install --upgrade .
```
