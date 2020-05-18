#!/bin/sh

find . -name "*.java" | xargs javac
java -cp src:test track.util.TestRunner test
