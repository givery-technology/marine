import logging
try:
  from main import divide
except ImportError as e:
  print("not ok 1 メソッド divide が見つかりません。メソッド名を見直してください。")
  exit(0)
except Exception as e:
  print("not ok 1 メソッド divide の読み込みに失敗しました。実装を見直してください。")
  logging.exception(e)
  exit(0)


def doTest(index, a, b):
  try:
    answer = 0 if (b == 0) else a // b
    result = divide(a, b)

    if answer == result:
      print("ok {} メソッド divide({}, {}) の返り値は {} でした。正解!".format(index, a, b, result))
    else:
      print("not ok {} メソッド divide({}, {}) の返り値は {} でした。期待される値は {} です。".format(index, a, b, result, answer))

  except Exception as e:
    print("not ok {} メソッド divide({}, {}) の実行に失敗しました。実装を見直してください。".format(index, a, b))
    logging.exception(e)

if __name__ == "__main__":
  doTest(1, 5, 3)
  doTest(2, 1, 0)
  doTest(3, 0, 1)
