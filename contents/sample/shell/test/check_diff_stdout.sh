# 受験者の標準出力と、期待される標準出力を比較し、正誤判定とログ出力を行う。

if [ $1 = 'pre-sort' ]; then
# 出力する順番は不問
  sort ~/tmp/result_stdout -o ~/tmp/result_stdout_sorted
  sort ~/tmp/ans.txt -o ~/tmp/ans_sorted.txt
  diff ~/tmp/result_stdout_sorted ~/tmp/ans_sorted.txt > ~/tmp/diff.txt
else
  diff ~/tmp/result_stdout ~/tmp/ans.txt > ~/tmp/diff.txt
fi

if [ -s ~/tmp/diff.txt ]; then
  echo ""
  echo "期待される標準出力が異なります。"
  echo "##### 期待される標準出力"
  cat ~/tmp/ans.txt
  echo ""
  echo "##### あなたの標準出力"
  cat ~/tmp/result_stdout
  exit 100
fi
