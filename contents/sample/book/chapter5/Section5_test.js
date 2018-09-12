"use strict";

var assert = chai.assert;

describe("関数add", function() {

  it("addが定義されている", function() {
    assert.equal(typeof add, "function");
  });

  it("add(1, 1)の実行結果は2", function() {
    const result = add(1, 1);
    assert.equal(result, 2);
  });

  it("add(2, 3)の実行結果は5", function() {
    const result = add(2, 3);
    assert.equal(result, 5);
  });
});
