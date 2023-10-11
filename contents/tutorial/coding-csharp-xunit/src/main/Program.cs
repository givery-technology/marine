using System;

class Program
{
    static void Main(string[] args)
    {
        int x = int.Parse(args[0]);
        int y = int.Parse(args[1]);
        Console.WriteLine(App.Add(x, y));
    }
}
