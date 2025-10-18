#!/bin/bash
g++ -I/opt/homebrew/opt/openssl@3/include -o myg server.cpp -L/opt/homebrew/opt/openssl@3/lib -lssl -lcrypto -std=c++17

if [ $? -eq 0 ]; then
    echo "server.cpp compiled"
else
    echo "server.cpp compilation failed"
fi
