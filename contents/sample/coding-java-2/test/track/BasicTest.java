package track;

import track.util.Test;
import static track.util.Assert.*;

public class BasicTest {

  @Test(ja = "[基本実装] n = 1 のとき正しく計算できる")
  public void test1() {
    assertEquals("n = 1", "1", FizzBuzz.fizzbuzz(1));
  }

  @Test(ja = "[基本実装] n = 3 のとき正しく計算できる")
  public void test3() {
    assertEquals("n = 3", "fizz", FizzBuzz.fizzbuzz(3));
  }

  @Test(ja = "[基本実装] n = 5 のとき正しく計算できる")
  public void test5() {
    assertEquals("n = 5", "buzz", FizzBuzz.fizzbuzz(5));
  }

  @Test(ja = "[基本実装] n = 10 のとき正しく計算できる")
  public void test10() {
    assertEquals("n = 10", "buzz", FizzBuzz.fizzbuzz(10));
  }

  @Test(ja = "[基本実装] n = 15 のとき正しく計算できる")
  public void test15() {
    assertEquals("n = 15", "fizzbuzz", FizzBuzz.fizzbuzz(15));
  }
}
