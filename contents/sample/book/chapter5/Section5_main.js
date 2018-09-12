"use strict";

function add(a, b) {
  // ここに関数を実装してください。
}

// 以下は編集しないでください。
document.addEventListener("DOMContentLoaded", function(event) {
  $("#calc").click(function() {
    const a = parseInt($("#num1").val() || 0, 10);
    const b = parseInt($("#num2").val() || 0, 10);
    $("#result").val(add(a, b));
  });
});