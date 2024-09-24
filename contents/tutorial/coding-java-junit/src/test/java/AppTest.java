import org.junit.jupiter.api.Timeout;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.DisplayName;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.CoreMatchers.is;

@Timeout(5)
public class AppTest {
  @Test
  @DisplayName("[基本実装] 入力が 2 と 3 のとき、期待された出力結果が得られる")
  public void test_2_3() {
    int[] input = {2, 3};
    __testOutput(input, 5);
  }

  @Test
  @DisplayName("[基本実装] 入力が 15 と 8 のとき、期待された出力結果が得られる")
  public void test_15_8() {
    int[] input = {15, 8};
    __testOutput(input, 23);
  }

  @Test
  @DisplayName("[基本実装] 入力が 65 と 94 のとき、期待された出力結果が得られる")
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
