const codecheck = require("codecheck");

const language = process.env.CHALLENGE_LANGUAGE || "ja";
const appCommand = process.env.APP_COMMAND;
 
const settings = require("./settings.json");
settings.language = language;
const testcases = require("./basic_testcases.json");
 
const testRunner = codecheck.testRunner(settings, appCommand);
testRunner.runAll(testcases);
