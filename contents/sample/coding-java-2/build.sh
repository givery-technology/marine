#!/bin/sh

find . -name "*.class" | xargs rm 2>/dev/null || true
find . -name "*.java" | xargs javac
