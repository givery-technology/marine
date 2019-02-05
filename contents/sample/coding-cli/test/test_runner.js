"use strict";

const expect = require("chai").expect;
const codecheck = require("codecheck");
const settings = require("./settings.json");
const app = codecheck.consoleApp(process.env.APP_COMMAND).consoleOut(false).storeStdMax(2000000);
const fs = require("fs");
const exec = require("child_process").exec;
const util = require("util");
const execPromise = util.promisify(require("child_process").exec);
const TestUtil = require("./test_utilities.js");
const testUtil = new TestUtil(settings);


const TestRunner = function(testcases) {
    let app = null;
    describe("", () => {
        before (() => {
            return 0;
        });
        beforeEach("", () => {
            app = codecheck.consoleApp(process.env.APP_COMMAND).consoleOut(false).storeStdMax(2000000);
            try {
                fs.statSync("answer.txt");
                fs.unlinkSync("answer.txt");
            } catch(err) { }
        });
        afterEach("", () => {
            if (app) {
                app.kill();
            }
            app = null;
        });

        testcases.forEach( testcase => {
            it(testcase.description, async () => {
                const [input_raw, input_arr] = await testUtil.getInput(testcase.input); // テストケースの入力値

                // 受験者のプログラムを実行
                const result = await app.codecheck(input_arr);
                if (!(result.code === 0)) {
                    testUtil.printMessageOnAbnormalEnd(input_raw, result);
                    expect(result.code).to.equal(0, "ステータスコードが正常(0)ではありません");
                }

                const [stdout_raw, stdout_arr] = await testUtil.getStdout(result); // 受験者の標準出力
                const [output_user_raw, output_user_arr] = await testUtil.getOutput(stdout_raw, stdout_arr); // 受験者の出力値

                const [output_expected_raw, output_expected_arr] = await testUtil.getExpected(testcase.output); // 正解の出力値

                let message_summary = testUtil.getSummaryString(input_raw, output_user_raw, output_expected_raw, stdout_raw);

                // データ長が正しいことを確認
                let message_length = "";
                message_length += "出力すべきデータの個数が違います\n";
                message_length += `期待された個数: ${output_expected_arr.length}\n`;
                message_length += `あなたの個数: ${output_user_arr.length}\n`;
                message_length += message_summary;
                expect(output_expected_arr.length).to.equal(output_user_arr.length, message_length);

                // それぞれのデータが正しいことを確認
                for (let i = 0; i < output_expected_arr.length; i++){
                    if (!(output_expected_arr[i] === output_user_arr[i])) {
                        let message_wrong = "";
                        message_wrong += `${i+1}番目のデータが違います。\n`;
                        message_wrong += `期待された答え: ${testUtil.clip(output_expected_arr[i], settings.maxCharacters)}\n`;
                        message_wrong += `あなたの答え: ${testUtil.clip(output_user_arr[i], settings.maxCharacters)}\n`;
                        message_wrong += message_summary;

                        expect(0).to.be.equal(1, message_wrong);
                    }
                }
            });
        });
    });
}


module.exports = TestRunner;
