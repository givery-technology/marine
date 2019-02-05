package track;

import org.junit.Test;
import static org.junit.Assert.*;

public class BasicTest {

  @Test
  public void test1() {
    assertEquals("1", FizzBuzz.fizzbuzz(1));
  }

  @Test
  public void test3() {
    assertEquals("fizz", FizzBuzz.fizzbuzz(3));
  }

  @Test
  public void test5() {
    assertEquals("buzz", FizzBuzz.fizzbuzz(5));
  }

  @Test
  public void test10() {
    assertEquals("buzz", FizzBuzz.fizzbuzz(10));
  }

  @Test
  public void test15() {
    assertEquals("fizzbuzz", FizzBuzz.fizzbuzz(15));
  }
}