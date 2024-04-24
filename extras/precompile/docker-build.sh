#!/bin/bash
set -euo pipefail
IFS=$'\n\t'
docker build --pull --tag open62541_precompile_lib .
