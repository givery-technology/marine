using System;
using System.Threading;

public class Util
{
    private static int TIMEOUT = 5000;
    public static int RunApp(int x, int y)
    {
        AppThread appThread = new AppThread(x, y);
        Thread th = new Thread(new ThreadStart(appThread.Run));
        try
        {
            th.Start();
            th.Join(TIMEOUT);
        }
        catch (ThreadInterruptedException)
        {
            Console.WriteLine("Timeout " + TIMEOUT + "ms");
        }
        return appThread.GetResult();
    }

    private class AppThread
    {
        private readonly int x;
        private readonly int y;
        private int result = -1;

        public AppThread(int x, int y)
        {
            this.x = x;
            this.y = y;
        }

        public int GetResult()
        {
            return this.result;
        }

        public void Run()
        {
            this.result = App.Add(x, y);
        }
    }
}
