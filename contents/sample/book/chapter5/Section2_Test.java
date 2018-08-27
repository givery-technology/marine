public class Test {

  private static void doTest(int index, int a, int b) {
    try {
      int answer = b == 0 ? 0 : a / b;
      int users = Main.divide(a, b);
      String ret = answer == users ? "ok " : "not ok ";
      System.out.println(ret + index + " 引数が、" + a + ", " + b + "の場合の返り値が、" + answer + "であること");
    } catch (Exception e) {
      // 例外キャッチ時に次の行を差し込まないとテストの実行に失敗しているにも関わらずクリアとなってしまう。
      // System.out.println("not ok " + index + " メソッドの実行に失敗しました: " + e.toString());
      e.printStackTrace();
    }
  }

  public static void main(String[] args) {
    doTest(1, 5, 3);
    doTest(2, 1, 0);
    doTest(3, 0, 1);
  }
}
