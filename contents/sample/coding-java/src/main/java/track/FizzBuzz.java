package track;

public class FizzBuzz {
  public static String fizzbuzz(int n) {
    // BEGIN_CHALLENGE
    if (n % 15 == 0) return "fizzbuzz";
    if (n % 5 == 0) return "buzz";
    if (n % 3 == 0) return "fizz";
    // END_CHALLENGE
    return Integer.toString(n);
  }
}
