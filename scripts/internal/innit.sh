#!/bin/bash

if [ ! -d "out/release" ]; then
    mkdir -p "out/release"
fi

if [ ! -d "out/debug" ]; then
    mkdir -p "out/debug"
fi