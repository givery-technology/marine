// NUnit
// 標準出力がされない

using NUnit.Framework;
// using System;

public class AppTest
{
    [Test]
    public void test_2_3()
    {
        int[] input = new int[2] {2, 3};
        __testOutput(input, 5);
    }

    [Test]
    public void test_15_8()
    {
        int[] input = new int[2] {15, 8};
        __testOutput(input, 23);
    }

    [Test]
    public void test_65_94()
    {
        int[] input = new int[2] {65, 94};
        __testOutput(input, 159);
    }

    private void __testOutput(int[] input, int expected)
    {
        int x = input[0];
        int y = input[1];
        int result = Util.RunApp(x, y);

        Assert.AreEqual(expected, result);

        if (TestContext.CurrentContext.Result.Outcome.Status == NUnit.Framework.Interfaces.TestStatus.Failed)
        {
            TestContext.WriteLine("Test failed.");
            // Console.WriteLine("Test failed.");
        }
        else
        {
            TestContext.WriteLine("Test succeeded.");
            // Console.WriteLine("Test succeeded.");
        }
    }
}
