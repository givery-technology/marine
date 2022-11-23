# 受験者の出力したファイルと、期待されるファイルを比較し、正誤判定とログ出力を行う。

if [ ! -e $1 ]; then
  echo "ファイル $1 が存在しません。"
  exit 100
fi

if [ ! -e $2 ]; then
  echo "[judge.shに問題があります] ファイル $2 が存在しません。"
  exit 100
fi

if [ $3 = 'pre-sort' ]; then
# 出力する順番は不問
  sort $1 -o ~/tmp/file.sorted
  sort $2 -o ~/tmp/ans.sorted
  diff ~/tmp/file.sorted ~/tmp/ans.sorted > ~/tmp/diff.txt
else
  diff $1 $2 > ~/tmp/diff.txt
fi

if [ -s ~/tmp/diff.txt ]; then
  echo ""
  echo "##### $1 が期待されたものではありません。"
  echo "##### 期待される $1"
  cat $2
  echo ""
  echo "##### あなたの出力した $1"
  cat $1
  exit 100
fi
