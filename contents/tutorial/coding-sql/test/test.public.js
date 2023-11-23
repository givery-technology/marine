const dblib = require('track-db-test-library');
const runner = new dblib.TestRunner(process.env.CHALLENGE_LANGUAGE, 'test/test.public.yml');
runner.runAll();
