FROM debian:stable-slim

RUN apt-get update && \
    apt-get install -y git build-essential gcc-arm-none-eabi cmake bash wget python3 && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

CMD ["/bin/bash", "-c", "cd /Arduino_open62541; ./extras/precompile/precompile.sh; exit"]
