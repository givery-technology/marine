import static org.junit.jupiter.api.Assertions.fail;

public class Util {
  private static long TIMEOUT = 5_000;

  public static void runApp(int x, int y) {
    AppThread th = new AppThread(x, y);
    try {
      th.start();
      th.join(TIMEOUT);
    } catch (InterruptedException e) {
      fail("Timeout " + TIMEOUT + "ms");
    }
  }

  private static class AppThread extends Thread {
    private final int x;
    private final int y;

    AppThread(int x, int y) {
      this.x = x;
      this.y = y;
    }

    public void run() {
      System.out.print(App.add(x, y));
    }
  }
}
