#
# Copyright (c) Flyover Games, LLC
#

SHELL := /usr/bin/env bash

__default__: help

help:
	@echo done $@

GYP ?= gyp
gyp:
	$(GYP) --depth=. -f xcode -DOS=ios --generator-output=./node-sdl2_net-ios node-sdl2_net.gyp
	$(GYP) --depth=. -f xcode -DOS=osx --generator-output=./node-sdl2_net-osx node-sdl2_net.gyp
