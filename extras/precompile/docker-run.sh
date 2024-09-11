#!/bin/bash
set -euo pipefail
IFS=$'\n\t'
docker run -it -v ${PWD}/../../:/Arduino_OPC_UA open62541_precompile_lib
