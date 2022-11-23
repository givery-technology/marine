# exit code >= 2 -> wrong answer

set -e -o pipefail

cat ~/tmp/result_stdout #; rm result_stdout
echo "#### 標準エラー出力:"
cat ~/tmp/result_stderr #; rm result_stderr
echo "#### 採点出力:"

cat <<EOF >> ~/tmp/ans.txt
secret hogehoge
EOF

# pre-sort で出力順不同にできる
sh ~/tmp/test/check_diff_stdout.sh pre-sort
