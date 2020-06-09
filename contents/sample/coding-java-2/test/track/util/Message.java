package track.util;

import java.util.*;

public final class Message {
    private static final String CHALLENGE_LANG = System.getenv().getOrDefault("CHALLENGE_LANGUAGE", "ja").toLowerCase();

    private final String ja;
    private final String en;
    private final List<Object> args;

    public Message(String ja, String en) {
        this.ja = ja;
        this.en = en;
        this.args = null;
    }

    public Message(String ja, String en, List<Object> args) {
        this.ja = ja;
        this.en = en;
        this.args = new ArrayList<>(args);
    }

    public Message args(Object... args) {
        List<Object> newArgs = new ArrayList<>();
        if (this.args != null) {
            newArgs.addAll(this.args);
        }
        if (args != null) {
            newArgs.addAll(Arrays.asList(args));
        }
        return new Message(ja, en, newArgs);
    }

    public String get() {
        String message;
        Locale locale;
        switch (CHALLENGE_LANG) {
            case "en":
                message = en;
                locale = Locale.ENGLISH;
                break;
            case "ja":
            default:
                message = ja;
                locale = Locale.JAPANESE;
                break;
        }
        if (this.args == null || this.args.isEmpty()) {
            return message;
        } else {
            return String.format(locale, message, this.args.toArray());
        }
    }

    public String get(Object... args) {
        return this.args(args).get();
    }
}
