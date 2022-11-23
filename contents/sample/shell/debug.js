"use strict";

const codecheck = require("codecheck");
const app = codecheck.consoleApp(process.env.APP_COMMAND);
const challenge_language = typeof process.env.CHALLENGE_LANGUAGE === "undefined" ? "ja" : process.env.CHALLENGE_LANGUAGE;

const { execSync } = require('child_process')

const n = process.argv[2];

execSync('bash ./test/before_init.sh');
execSync(`bash ~/tmp/test/basic/initialize.sh`);

if (n == 3) {
  if (challenge_language === "ja") {
    console.log(`\u001b[32mStep ${n}: b.txt の内容\u001b[0m`);
  } else {
    console.log(`\u001b[32mStep ${n}: Contents of b.txt\u001b[0m`);
  }
  execSync('bash ~/tmp/src/script3.sh 2100-01-01');
  try {
    const output = execSync('cat ./b.txt').toString();
    console.log(output);
  } catch (e) {
    // do nothing
  }

  execSync('bash ~/tmp/test/recover.sh');
  return;
}

if (challenge_language === "ja") {
  console.log(`\u001b[32mStep ${n}: script${n}.sh の実行結果\u001b[0m`);
} else {
  console.log(`\u001b[32mStep ${n}: Execution result of script${n}\u001b[0m`);
}
try {
  const output = execSync(`bash ~/tmp/src/script${n}.sh`).toString();
  console.log(output);
} catch (e) {
  // do nothing
}

execSync('bash ~/tmp/test/recover.sh');
