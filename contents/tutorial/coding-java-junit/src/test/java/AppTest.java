import org.junit.jupiter.api.Timeout;
import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.io.PrintStream;
import java.io.ByteArrayOutputStream;

import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.charset.StandardCharsets;
import java.util.List;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.CoreMatchers.is;

@Timeout(5)
public class AppTest {
  @Test
  public void test_2_3() throws IOException {
    __testOutput("src/test/resources/in/public/01.in", "src/test/resources/out/public/01.out");
  }
  @Test
  public void test_15_8() throws IOException {
    __testOutput("src/test/resources/in/public/02.in", "src/test/resources/out/public/02.out");
  }
  @Test
  public void test_65_94() throws IOException {
    __testOutput("src/test/resources/in/public/03.in", "src/test/resources/out/public/03.out");
  }

  private void __testOutput(String input, String expected) throws IOException {
    PrintStream origin = System.out;
    try {
      ByteArrayOutputStream bos = new ByteArrayOutputStream();
      System.setOut(new PrintStream(bos, true, "utf-8"));
      String[] args = Files.readString(Paths.get(input), StandardCharsets.UTF_8).trim().split(" ");
      int x = Integer.parseInt(args[0]);
      int y = Integer.parseInt(args[1]);
      Util.runApp(x, y);
      String result = new String(bos.toByteArray(), "utf-8").trim();

      List<String> expectedContent = Files.readAllLines(Paths.get(expected));
      String output = String.join("\n",expectedContent).trim();

      assertThat(result, is(output));
    } finally {
      System.setOut(origin);
    }
  }
}
