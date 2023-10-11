#!/usr/bin/bash
cd /root/src/src/test
dotnet test --logger:xunit;
$(npm bin)/metatest do echo then expand xunit /root/src/src/test/TestResults/TestResults.xml;
