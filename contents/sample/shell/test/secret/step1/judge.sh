# exit code >= 2 -> wrong answer

set -e -o pipefail

cat ~/tmp/result_stdout #; rm result_stdout
echo "#### 標準エラー出力:"
cat ~/tmp/result_stderr #; rm result_stderr
echo "#### 採点出力:"

cat <<EOF >> ~/tmp/ans.txt
Hello Shell
EOF

# diff があった場合、異常終了する
sh ~/tmp/test/check_diff_stdout.sh
