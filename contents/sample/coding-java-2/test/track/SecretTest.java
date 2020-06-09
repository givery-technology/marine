package track;

import track.util.Test;
import static track.util.Assert.assertEquals;

public class SecretTest {

  private String fizzbuzz(int n) {
    if (n % 15 == 0) return "fizzbuzz";
    if (n % 5 == 0) return "buzz";
    if (n % 3 == 0) return "fizz";
    return Integer.toString(n);
  }

  @Test(ja = "[基本実装] n = 1 ～ 100 のすべてで正しく計算できる")
  public void test1to100() {
    for (int i=1; i<=100; i++) {
      assertEquals("n = " + i, this.fizzbuzz(i), FizzBuzz.fizzbuzz(i));
    }
  }

}
