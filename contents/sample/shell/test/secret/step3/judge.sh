# exit code >= 2 -> wrong answer

cat ~/tmp/result_stdout
echo "#### 標準エラー出力:"
cat ~/tmp/result_stderr
echo "#### 採点出力:"

cat <<EOF >> ~/tmp/ans.txt
secret hogehoge
secret hugahuga
secret ho ge
EOF

sh ~/tmp/test/check_diff_file.sh a.txt ~/tmp/ans.txt && sh ~/tmp/test/check_diff_file.sh b.txt ~/tmp/ans.txt
