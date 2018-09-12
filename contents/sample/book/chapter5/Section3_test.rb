require "./main.rb"

def doTest(index, a, b)
  answer = b == 0 ? 0 : a / b
  users = divide(a, b)
  ret = answer == users ? "ok" : "not ok"
  print("#{ret} #{index} divide(#{a}, #{b})の返り値は#{users}でした。期待される値は #{answer} です。 \n")
  rescue  => ex
    print("not ok #{index} メソッド divide(#{a}, #{b}) の実行に失敗しました。実装を見直してください。\n")
end

doTest(1, 5, 3);
doTest(2, 1, 0);
doTest(3, 0, 1);
