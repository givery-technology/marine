"use strict";

const fs = require("fs");
const util = require("util");

 const lang = process.env.CHALLENGE_LANGUAGE;

class TestUtilities {
  // 文字列を見やすく省略する
  clip(s, len) {
    let ret = "";
    let lines = 0;
    let omitted = len < s.length;
    for (let i = 0; i < Math.min(len, s.length); i++) {
      if (s[i] === "\n") {
        lines++;
      }
      if (lines > this.settings.maxLines) {
        omitted = true;
        break;
      }
      ret += s[i];
    }
    if (omitted) {
      ret += "...";
    }
    return ret;
  }

  // Wrong Answer時に受験者に表示する文字列を構成する。
  getSummaryString(input, user, expected, user_stdout) {
    let ret = "";
    ret += (lang === "ja" ? "#### 入力: \n" : "#### Input: \n");
    ret += this.clip(input, this.settings.maxCharacters) + "\n";
    ret += "\n";
    ret += (lang === "ja" ? "#### あなたの答え: \n" : "#### Your Output: \n");
    ret += this.clip(user, this.settings.maxCharacters);
    ret += '\n';

    if (this.settings.isSpecial === false) {
      ret += (lang === "ja" ? "#### 期待された答え: \n" : "#### Expected Output: \n");
      ret += this.clip(expected, this.settings.maxCharacters);
      ret += '\n';
    }
    if (this.settings.isFileOutput === true) {
      ret += (lang === "ja" ? "#### あなたの標準出力: \n" : "#### Your standard output: \n");
      ret += this.clip(user_stdout, this.settings.maxCharacters);
      ret += '\n';
    }

    return ret;
  }

  // 文字列を入力して、空白区切りで分解した文字列配列を返す。
  // 空文字列を除外することで、先頭・末尾などの余計な改行にロバストにする
  stringToArray(s) {
    s = s.split(/\s/);
    let ret = [];
    for (let i = 0; i < s.length; i++) {
      if (s[i].length) {
        ret.push(s[i]);
      }
    }
    return ret;
  }

  flatten(arr){
    return arr.reduce( (a, b) => {
      return a.concat(b); 
    });
  }

  // 入力引数の生データ（文字列）と、それを空白区切りで分割した文字列配列を返す
  async getInput(t_input) {
    let input_raw = await util.promisify(fs.readFile)("./test/"+t_input, "utf-8");

    let input_arr = null; // string[]
    if (!this.settings.isFileInput) {
      input_arr = this.stringToArray(input_raw);
    } else {
      input_arr = ["./test/"+t_input];
    }

    return [input_raw, input_arr];
  }

  // 受験者の答えの文字列と、それを空白区切りで分割した文字列配列を返す
  async getOutput(stdout_val, stdout_arr) {
    let userOutput_val = "";
    let userOutput_arr = [];

    if (this.settings.isFileOutput) {
      userOutput_val = await util.promisify(fs.readFile)("answer.txt", "utf-8");
      userOutput_arr = this.stringToArray(userOutput_val);
    } else {
      userOutput_val = stdout_val;
      userOutput_arr = stdout_arr;
    }
    return [userOutput_val, userOutput_arr];
  }

  // 本当の答えの文字列と、それを空白区切りで分割した文字列配列を返す
  async getExpected(t_output) {
    let expectedOutput_val = await util.promisify(fs.readFile)("./test/"+t_output, "utf-8");
    let expectedOutput = this.stringToArray(expectedOutput_val); // string[]
    return [expectedOutput_val, expectedOutput];
    return ["", []];
  }

  // 受験者の標準出力の文字列と、それを空白区切りで分割した文字列配列を返す
  async getStdout(result) {
    let stdout_raw = "";
    for (let i = 0; i < result.stdout.length; i++) {
      stdout_raw += result.stdout[i] + "\n";
    }

    let userOutput = [];
    for (let i = 0; i < result.stdout.length; i++) { // stdoutのi行目
      const ith_line = this.stringToArray(result.stdout[i]);
      for (let s of ith_line) {
        userOutput.push(s);
      }
    }

    return [stdout_raw, userOutput];
  }

  // 受験者のプログラムが異常終了した時に伝えるべき、入力・標準出力・標準エラー出力を表示する。
  printMessageOnAbnormalEnd(input_val, result) {
    console.log(lang === "ja" ? "#### 入力:" : "#### Input");
    console.log(this.clip(input_val, this.settings.maxCharacters));

    if (result.stdout.length != 0) {
      console.log(lang === "ja" ? "#### 標準出力:" : "#### Standard Output");
      let stdout_val = "";
      for (let i = 0; i < result.stdout.length; i++ ){ 
        stdout_val += result.stdout[i] + '\n';
      }
      console.log(this.clip(stdout_val, this.settings.maxCharacters));
    }

    if (result.stderr.length != 0) {
      console.log(lang === "ja" ? "#### 標準エラー出力:" : "#### Standard error output");
      let stderr_val = "";
      for (let i = 0; i < result.stderr.length; i++ ){ 
        stderr_val += result.stderr[i] + '\n';
      }
      console.log(this.clip(stderr_val, this.settings.maxCharacters));
    }
  }

  constructor(settings){
    this.settings = settings;
  }
};

module.exports = TestUtilities;
