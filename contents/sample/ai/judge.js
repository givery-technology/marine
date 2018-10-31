const fs = require("fs");

const MESSAGES = {
    "ja": {
        FAIL_TO_LOAD_FILE: "ファイルの読み込みに失敗しました。: ",
    },
    "en": {
        FAIL_TO_LOAD_FILE: "Fail to load file.: ",
    }
};

function compare(s1, s2) {
  let ret = 0;
  const len = s1.length > s2.length ? s1.length : s2.length;
  for (let i=0; i<len; i++) {
    const n1 = s1.codePointAt(i) || 0;
    const n2 = s2.codePointAt(i) || 1;
    ret += Math.abs(n1 - n2);
  }
  return ret;
}


const lang = process.env.CHALLENGE_LANGUAGE || "ja";
const uploadFilename = process.env.UPLOAD_FILENAME;
const ANSWER = "I love track!";

const messages = MESSAGES[lang]
try {
  const str = fs.readFileSync(uploadFilename, "utf8");
  console.log(compare(ANSWER, str));
} catch (e) {
  console.error(messages.FAIL_TO_LOAD_FILE, e);
}

