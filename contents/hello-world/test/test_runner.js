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

const lang = process.env.CHALLENGE_LANGUAGE !== undefined ? process.env.CHALLENGE_LANGUAGE : "ja";

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
      it(lang === "ja" ? testcase.description : testcase.description_en, async () => {
        const [input_raw, input_arr] = await testUtil.getInput(testcase.input); // テストケースの入力値

        // 受験者のプログラムを実行
        const result = await app.codecheck(input_arr);
        if (!(result.code === 0)) {
          testUtil.printMessageOnAbnormalEnd(input_raw, result);
          const message = lang === "ja" ? "ステータスコードが正常(0)ではありません" : "Exit status should be 0.";
          expect(result.code).to.equal(0, message);
        }
        // answer.txtの存在確認
        if (settings.isFileOutput) {
          try {
            fs.statSync("answer.txt");
          } catch(err) { 
            testUtil.printMessageOnAbnormalEnd(input_raw, result);
            const message = lang === "ja" ? "answer.txtがありません" : "answer.txt is not found.";
            expect(0).not.to.equal(0, message);
          }
        }

        const [stdout_raw, stdout_arr] = await testUtil.getStdout(result); // 受験者の標準出力
        const [output_user_raw, output_user_arr] = await testUtil.getOutput(stdout_raw, stdout_arr); // 受験者の出力値

        if (settings.isSpecial === false) {
          const [output_expected_raw, output_expected_arr] = await testUtil.getExpected(testcase.output); // 正解の出力値

          let message_summary = testUtil.getSummaryString(input_raw, output_user_raw, output_expected_raw, stdout_raw);

          // データ長が正しいことを確認
          let message_length = "";
          message_length += (lang === "ja" ? "出力すべきデータの個数が違います\n" : "The number of outputs is wrong\n");
          message_length += (lang === "ja" ? "期待された個数: " : "Expected number: ") + `${output_expected_arr.length}\n`;
          message_length += (lang === "ja" ? "あなたの個数: " : "Participant's number: ") + `${output_user_arr.length}\n`;
          message_length += message_summary;
          expect(output_expected_arr.length).to.equal(output_user_arr.length, message_length);

          // それぞれのデータが正しいことを確認
          for (let i = 0; i < output_expected_arr.length; i++){
            if (!(output_expected_arr[i] === output_user_arr[i])) {
              let message_wrong = "";
              let ordinal_indicator = "th";
              if ((i+1) % 10 == 1) ordinal_indicator = "st";
              if ((i+1) % 10 == 2) ordinal_indicator = "nd";
              if ((i+1) % 10 == 3) ordinal_indicator = "rd";
              message_wrong += `${i+1}` + (lang === "ja" ? "番目のデータが違います。\n" : ordinal_indicator+" data is wrong\n");
              message_wrong += (lang === "ja" ? "期待された答え: " : "Expected data: ") + `${testUtil.clip(output_expected_arr[i], settings.maxCharacters)}\n`;
              message_wrong += (lang === "ja" ? "あなたの答え: " : "Participant's data: ") + `${testUtil.clip(output_user_arr[i], settings.maxCharacters)} \n`;
              message_wrong += message_summary;

              expect(0).to.be.equal(1, message_wrong);
            }
          }
        } else {
          try {
            fs.statSync("./test/judge");
          } catch(err) { 

            const message = lang === "ja" ? "judgeがありません。管理者に問い合わせてください。" : "No judge found. Please contact the administrator.";
            expect(0).not.to.equal(0, "");
          }

          if (!settings.isFileOutput) fs.writeFileSync("answer.txt", output_user_raw);

          try {
            const { stdout, stderr } = await execPromise(`./test/judge ./test/${testcase.input} ./test/${testcase.output} answer.txt`);
          } catch(error) {
            const message_summary = "\n"+testUtil.getSummaryString(input_raw, output_user_raw, ""/*本当の答えはないので指定しない*/, stdout_raw);
            expect(error.code).to.not.equal(1, (lang === "ja" ? "最小値が違います" : "Min is wrong")+message_summary);
            expect(error.code).to.not.equal(2, (lang === "ja" ? "最大値が違います" : "Max is wrong")+message_summary);
            expect(error.code).to.not.equal(3, (lang === "ja" ? "連結した文字列が違います" : "Concatenated string is wrong")+message_summary);
            expect(0).to.not.equal(0, (lang === "ja" ? "ジャッジが異常終了しました" : "Judge exited abnormally")+message_summary);
          }
        }
      });
    });
  });
}


module.exports = TestRunner;
