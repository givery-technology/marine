"use strict";

function add(a, b) {
  // ここに関数を実装してください。
}

// 以下は編集しないでください。
document.addEventListener("DOMContentLoaded", function(event) {
  $("#calc").click(function() {
    const a = $("#num1").val();
    const b = $("#num2").val();
    $("#result").val(add(a, b));
  });
});