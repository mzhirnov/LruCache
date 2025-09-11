#!/usr/bin/env zsh

cmake -S../ -B../../LruCache-build -GXcode \
	-DCMAKE_APPLE_SILICON_PROCESSOR=arm64