import org.junit.jupiter.api.Timeout;
import org.junit.jupiter.api.Test;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.CoreMatchers.is;

@Timeout(5)
public class AppTest {
  @Test
  public void test_2_3() {
    int[] input = {2, 3};
    __testOutput(input, 5);
  }

  @Test
  public void test_15_8() {
    int[] input = {15, 8};
    __testOutput(input, 23);
  }

  @Test
  public void test_65_94() {
    int[] input = {65, 94};
    __testOutput(input, 159);
  }

  private void __testOutput(int[] input, int expected) {
    int x = input[0];
    int y = input[1];
    int result = Util.runApp(x, y);

    assertThat(result, is(expected));
  }
}
