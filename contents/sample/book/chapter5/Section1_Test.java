public class Test {

  private static void doTest(int index, String name) {
    try {
      String answer = "Hello " + name;
      String users = Main.hello(name);
      String ret = answer.equals(users) ? "ok " : "not ok ";
      System.out.println(ret + index + " 引数が「" + name + "」の場合の返り値が「" + answer + "」であること");
    } catch (Exception e) {
      System.out.println("not ok " + index + " メソッドの実行に失敗しました: " + e.toString());
      e.printStackTrace();
    }
  }
  public static void main(String[] args) {
    doTest(1, "World");
    doTest(2, "Taro");
  }
}
