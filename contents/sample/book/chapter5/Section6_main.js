"use strict";

function add(a, b) {
  // EXERCISE_BEGIN_EDIT
  // ここに関数を実装してください。
  // EXERCISE_END_EDIT
}

// 以下は編集しないでください。
document.addEventListener("DOMContentLoaded", function(event) {
  $("#calc").click(function() {
    const a = $("#num1").val();
    const b = $("#num2").val();
    $("#result").val(add(a, b));
  });
});