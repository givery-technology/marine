package track;

import org.junit.Test;
import static org.junit.Assert.*;

public class SecretTest {

  private String fizzbuzz(int n) {
    if (n % 15 == 0) return "fizzbuzz";
    if (n % 5 == 0) return "buzz";
    if (n % 3 == 0) return "fizz";
    return Integer.toString(n);
  }

  @Test
  public void test1to100() {
    for (int i=1; i<=100; i++) {
      assertEquals(this.fizzbuzz(i), FizzBuzz.fizzbuzz(i));
    }
  }

}