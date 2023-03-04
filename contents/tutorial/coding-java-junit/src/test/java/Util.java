import static org.junit.jupiter.api.Assertions.fail;

public class Util {
  private static long TIMEOUT = 5_000;

  public static int runApp(int x, int y) {
    AppThread th = new AppThread(x, y);
    try {
      th.start();
      th.join(TIMEOUT);
    } catch (InterruptedException e) {
      fail("Timeout " + TIMEOUT + "ms");
    }
    return th.getResult();
  }

  private static class AppThread extends Thread {
    private final int x;
    private final int y;
    private int result = -1;

    AppThread(int x, int y) {
      this.x = x;
      this.y = y;
    }

    int getResult() {
      return this.result;
    }

    public void run() {
      this.result = App.add(x, y);
    }
  }
}
