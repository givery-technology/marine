const codecheck = require("codecheck");

const language = process.env.CHALLENGE_LANGUAGE || "ja";
 
const settings = require("./settings.json");
settings.language = language;

const tests = 
[
    {
        "initialize": "secret/step1/initialize.sh",
        "judge": "secret/step1/judge.sh",
        "script": "script1.sh",
        "testcases": [
          {
            "input": "null",
            "output": "null",
            "description": "[基本実装] Step1: Hello Shell を標準出力に出力させることができる",
            "description_en": "[TODO] TODO"
          }
        ]
    },
    {
        "initialize": "secret/step2/initialize.sh",
        "judge": "secret/step2/judge.sh",
        "script": "script2.sh",
        "testcases": [
          {
            "input": "null",
            "output": "null",
            "description": "[基本実装] Step2: ファイル内の特定の行を抽出して出力することができる",
            "description_en": "[TODO] TODO"
          }
        ]
    },
    {
        "initialize": "secret/step3/initialize.sh",
        "judge": "secret/step3/judge.sh",
        "script": "script3.sh",
        "testcases": [
          {
            "input": "null",
            "output": "null",
            "description": "[基本実装] ファイルをコピーすることができる",
            "description_en": "[TODO] TODO"
          }
        ]
    },
]
{
    for (test of tests) {
        const testRunner = codecheck.testRunner(settings, `chmod 755 ./test/before_init.sh; bash ./test/before_init.sh; chmod 755 ~/tmp/test/${test.initialize}; bash ~/tmp/test/${test.initialize}; chmod 755 ~/tmp/test/recover.sh ~/tmp/src/${test.script} ~/tmp/test/${test.judge}; bash ~/tmp/src/${test.script} > ~/tmp/result_stdout 2> ~/tmp/result_stderr; bash ~/tmp/test/recover.sh; bash ~/tmp/test/${test.judge}`);
        testRunner.runAll(test.testcases);
    }
}
