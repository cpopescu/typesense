#!/bin/bash

CONFIG=${1}

# Need to build this first - for some reason interacts w/ the rest:
bazel build ${CONFIG} @sentencepiece || exit 1

# This takes close to forever and is prone to fail:
bazel build ${CONFIG} //:onnxruntime_lib //:onnxruntime || exit 1

jobs=$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
echo "Starting with ${jobs} parallelism"
num_tries=10
targets="//:search //:typesense-server //:benchmark //:typesense-test"
ok=0
# Try several times:
for i in $(seq ${num_tries}); do
    bazel build ${CONFIG} --jobs=${jobs} ${targets}
    if [[ "${?}" -eq "0" ]]; then
        echo "==========> BUILT OK"
        ok=1
        exit 0
    fi
    kill -9 $(pidof cc1plus)
    if [[ "${jobs}" -gt "2" ]]; then
        jobs=$(( ${jobs} / 2 ))
        echo "Reducing to ${jobs} parallelism"
        # and we continue
    fi
done
if [[ -z ${ok} ]]; then
    echo "ERROR building"
    exit 1
fi
exit 0
