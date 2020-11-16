apk add --no-cache cmake
wget -qO- https://github.com/google/googletest/archive/release-1.8.1.tar.gz | tar xvz
mkdir googletest-release-1.8.1/build
cd googletest-release-1.8.1/build
cmake ..
make
cd ../..
mv googletest-release-1.8.1/build/googlemock/*.a /usr/local/lib
mv googletest-release-1.8.1/build/googlemock/gtest/*.a /usr/local/lib
mv googletest-release-1.8.1/googlemock/include/gmock /usr/local/include
mv googletest-release-1.8.1/googletest/include/gtest /usr/local/include
mv initialize/tap.h /usr/local/include
rm -rf googletest-release-1.8.1

