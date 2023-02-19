import static org.junit.jupiter.api.Assertions.fail;

public class Util {
    private static long TIMEOUT = 5_000;

    public static void runApp(String[] args) {
        AppThread th = new AppThread(args);
        try {
            th.start();
            th.join(TIMEOUT);
        } catch (InterruptedException e) {
            fail("Timeout " + TIMEOUT + "ms");
        }
    }

    private static class AppThread extends Thread {
        private final String[] args;

        AppThread(String[] args) {
            this.args = args;
        }

        public void run() {
            Main.main(args);
        }
    }
}
