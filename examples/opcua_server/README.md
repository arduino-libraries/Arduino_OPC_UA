:floppy_disk: `opcua_server.ino`
================================

### How-to-build Modbus MD02 demo
```bash
arduino-cli compile --fqbn arduino:mbed_opta:opta examples/opcua_server -v --build-property compiler.cpp.extra_flags="-DUSE_MODBUS_SENSOR_MD02=1"
```
