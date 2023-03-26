using Xunit;

public class AppTest
{
	[Fact]
	public void test_2_3()
	{
		int[] input = new int[2] {2, 3};
		__testOutput(input, 5);
	}

	[Fact]
	public void test_15_8()
	{
		int[] input = new int[2] {15, 8};
		__testOutput(input, 23);
	}

	[Fact]
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

		Assert.Equal(expected, result);
	}
}
