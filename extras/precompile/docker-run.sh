#!/bin/bash
set -euo pipefail
IFS=$'\n\t'
docker run -it -v ${PWD}/../../:/Arduino_open62541 open62541_precompile_lib
