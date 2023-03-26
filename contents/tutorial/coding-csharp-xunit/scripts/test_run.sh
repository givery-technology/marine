#!/usr/bin/bash
cd /root/src/src/test
dotnet test --logger:xunit;

source /root/src/scripts/install.sh  # metatest実行と同じファイル内でinstallしないと 「metatest: not found」 が出力される
metatest do echo then expand xunit /root/src/src/test/TestResults/TestResults.xml;
