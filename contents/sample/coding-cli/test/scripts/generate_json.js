"use strict";

const fs = require('fs');
var exec = require('child_process').exec;
exec('ls ../in/basic/*.in ../in/secret/*.in', function(err, stdout, stderr) {
  if (err) { console.log(err); } 
  let files = stdout.split('\n');
  let basic = [];
  let secret = [];
  files.forEach(t => {
    if (t === "") return;
    const input_file_name = t.replace(/\.\.\//g, "");
    const output_file_name_sub = input_file_name.replace(/in$/g, "out");
    const output_file_name = output_file_name_sub.replace(/in\//g, "out\/");
    const desc_file_name = input_file_name.replace(/in$/g, "desc");
    const desc_en_file_name = input_file_name.replace(/in$/g, "desc_en");

    let description_ja = fs.readFileSync("../"+desc_file_name   , 'utf8');
    let description_en = fs.readFileSync("../"+desc_en_file_name   , 'utf8');

    if (input_file_name.indexOf("secret") != -1) {
      secret.push({"input":input_file_name, "output":output_file_name, "description":description_ja, "description_en":description_en});
    } else {
      basic.push({"input":input_file_name, "output":output_file_name, "description":description_ja, "description_en":description_en});
    }
  });

  fs.writeFileSync('../basic_testcases.json', JSON.stringify(basic, null, '   '));
  fs.writeFileSync('../secret_testcases.json', JSON.stringify(secret, null, '   '));
});
