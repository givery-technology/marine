find . -name '*' -maxdepth 1 | grep -v '^.$' | grep -v './*.yaml' | grep -v 'debug.js' | grep -v 'test' | grep -v 'src' | xargs rm -rf

rm -rf ~/tmp
mkdir ~/tmp
cp -rf * ~/tmp
rm -rf *
