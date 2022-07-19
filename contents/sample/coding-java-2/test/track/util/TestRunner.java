package track.util;

import java.io.File;
import java.io.PrintStream;
import java.lang.reflect.*;
import java.util.*;
import java.util.stream.*;

public class TestRunner {
    public static void main(String... args) throws Exception {
        List<Testcase> testcases = listTestcases(new File(args[0]));
        System.out.println("1.." + testcases.size());
        Object instance = "";
        int i = 0;
        for (Testcase testcase : testcases) {
            i++;
            if (!instance.getClass().equals(testcase.clazz)) {
                instance = testcase.clazz.getDeclaredConstructor().newInstance();
            }
            Test annotation = testcase.method.getAnnotation(Test.class);
            try {
                PrintStream stdout = System.out;
                PrintStream stderr = System.err;
                try {
                    testcase.method.invoke(instance);
                } finally {
                    System.setOut(stdout);
                    System.setErr(stderr);
                }
                System.out.println("ok " + i + " " + toString(annotation));
            } catch (InvocationTargetException e) {
                Throwable e2 = e.getTargetException();
                System.out.println("not ok " + i + " " + toString(annotation));
                if (AssertionError.class.equals(e2.getClass())) {
                    System.out.println(e2.getLocalizedMessage());
                } else {
                    e2.printStackTrace(System.out);
                }
            }
        }
    }

    private static final String CHALLENGE_LANG = System.getenv().getOrDefault("CHALLENGE_LANGUAGE", "ja").toLowerCase();
    private static String toString(Test annotation) {
        String ja = annotation.ja();
        String en = annotation.en();
        Stream<String> s;
        switch (CHALLENGE_LANG) {
            case "en":
                s = Stream.of(en, ja);
                break;
            case "ja":
            default:
                s = Stream.of(ja, en);
                break;
        }
        return s.filter(l -> l != null && !l.isEmpty()).findFirst().orElse("");
    }

    private static List<Class<?>> findClasses(File directory, File rootDirectory) throws Exception {
        assert directory.exists();
        List<Class<?>> classes = new ArrayList<>();
        for (File file : directory.listFiles()) {
            if (file.isDirectory()) {
                classes.addAll(findClasses(file, rootDirectory));
            } else if (file.getName().endsWith(".class")) {
                String path = rootDirectory.toPath()
                        .relativize(file.toPath())
                        .toString();
                String className = Stream.of(
                        path.substring(0, path.length() - ".class".length()).split("[\\\\/]")
                )
                        .filter(s -> !".".equals(s))
                        .collect(Collectors.joining("."));
                Class<?> clazz = Class.forName(className);
                if ((clazz.getModifiers() & Modifier.PUBLIC) > 0) {
                    classes.add(clazz);
                }
            }
        }
        return classes;
    }

    private static List<Testcase> listTestcases(File rootDirectory) throws Exception {
        List<Testcase> testcases = new ArrayList<>();

        List<Class<?>> classes = findClasses(rootDirectory, rootDirectory);
        for (Class<?> clazz: classes) {
            for (Method m : clazz.getDeclaredMethods()) {
                if (m.getAnnotation(Test.class) != null && (m.getModifiers() & Modifier.PUBLIC) > 0) {
                    testcases.add(new Testcase(clazz, m));
                }
            }
        }
        return testcases;
    }

    private static class Testcase {
        private final Class<?> clazz;
        private final Method method;

        public Testcase(Class<?> clazz, Method method) {
            this.clazz = clazz;
            this.method = method;
        }
    }
}
