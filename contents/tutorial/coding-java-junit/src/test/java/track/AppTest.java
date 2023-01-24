package track;

import org.junit.jupiter.api.Timeout;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvFileSource;

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
	@ParameterizedTest
	@CsvFileSource(resources = "/public.testcases.csv")
	void test(String input, String expected) throws IOException {

		PrintStream origin = System.out;
		try {
			ByteArrayOutputStream bos = new ByteArrayOutputStream();
			System.setOut(new PrintStream(bos, true, "utf-8"));
			String[] args = Files.readString(Paths.get(input), StandardCharsets.UTF_8).trim().split(" ");
			Util.runApp(args);
			String result = new String(bos.toByteArray(), "utf-8").trim();

			List<String> expectedContent = Files.readAllLines(Paths.get(expected));
			String output = String.join("\n",expectedContent).trim();

			assertThat(result, is(output));
		} finally {
			System.setOut(origin);
		}
	}
}
