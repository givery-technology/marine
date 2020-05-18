package track.util;

import java.util.*;

public final class Assert {
    /**
     * Asserts two objects are equal. If they are not, an AssertionError is thrown.
     * @param message
     * @param expected
     * @param actual
     */
    public static void assertEquals(Message message, Object expected, Object actual) {
        if (!Objects.equals(expected, actual)) {
            throw new AssertionError(String.format("%s\n### %s\n%s\n### %s\n%s",
                    message.get(),
                    EXPECTED.get(),
                    expected.toString(),
                    ACTUAL.get(),
                    actual.toString()
            ));
        }
    }

    /**
     * Asserts two objects are equal. If they are not, an AssertionError is thrown.
     * @param targetName
     * @param expected
     * @param actual
     */
    public static void assertEquals(String targetName, Object expected, Object actual) {
        assertEquals(EQUALS_ERROR.args(targetName), expected, actual);
    }

    /**
     * Asserts two doubles are equal to within a positive delta. If they are not, an AssertionError is thrown.
     * @param message
     * @param expected
     * @param actual
     * @param delta
     */
    public static void assertEquals(Message message, double expected, double actual, double delta) {
        assert delta >= 0;
        double actualDelta = expected > actual ? expected - actual : actual - expected;
        if (actualDelta > delta) {
            throw new AssertionError(String.format("%s\n### %s\n%s\n### %s\n%s",
                    message.get(),
                    EXPECTED.get(),
                    expected,
                    ACTUAL.get(),
                    actual
            ));
        }
    }

    public static void assertEquals(String targetName, double expected, double actual, double delta) {
        assertEquals(EQUALS_ERROR.args(targetName), expected, actual, delta);
    }

    /**
     * Asserts the acutal string contains the given substring. If it does not, an AssertionError is thrown.
     * @param message
     * @param substr
     * @param actual
     */
    public static void assertStringContains(Message message, String substr, String actual) {
        assert substr != null;
        if (actual == null || !actual.contains(substr)) {
            throw new AssertionError(String.format("%s\n### %s\n%s",
                    message.get(),
                    ACTUAL.get(),
                    actual.toString()
            ));
        }
    }

    /**
     * Asserts the acutal string contains the given substring. If it does not, an AssertionError is thrown.
     * @param targetName
     * @param substr
     * @param actual
     */
    public static void assertStringContains(String targetName, String substr, String actual) {
        assertStringContains(STRING_CONTAINS_ERROR.args(targetName, substr), substr, actual);
    }

    /**
     * Fails test case
     * @param message
     */
    public static void fail(Message message) {
        throw new AssertionError(message.get());
    }

    /**
     * Fails test case
     * @param message
     */
    public static void fail(String message) {
        throw new AssertionError(message);
    }

    private Assert() {}

    public static final Message EXPECTED = new Message("期待される値", "Expected");
    public static final Message ACTUAL = new Message("実際の値", "Actual");

    public static final Message EQUALS_ERROR = new Message("%sの値が違います", "Different value: %s");
    public static final Message STRING_CONTAINS_ERROR = new Message("%sに'%s'が含まれていません", "%s does not contain '%s'");
}
