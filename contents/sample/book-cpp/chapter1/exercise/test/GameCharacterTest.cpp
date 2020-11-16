#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include "GameCharacter.h"

class GameCharacterTest : public testing::Test {
public:
  GameCharacterTest() : m_sample(10, 20) {}

protected:
  void checkType_health() { testing::StaticAssertTypeEq<int, decltype(m_sample.m_health)>(); }

  void checkType_power() { testing::StaticAssertTypeEq<int, decltype(m_sample.m_power)>(); }

  void checkReturnType_decreaseHealth() { testing::StaticAssertTypeEq<void, decltype(m_sample.decreaseHealth(1))>(); }

  void checkReturnType_show() { testing::StaticAssertTypeEq<void, decltype(m_sample.show())>(); }

  int readHealth(const GameCharacter &target) const { return target.m_health; }
  int readPower(const GameCharacter &target) const { return target.m_power; }

  void writeHealth(GameCharacter &target, int health) const { target.m_health = health; }
  void writePower(GameCharacter &target, int power) const { target.m_power = power; }

private:
  GameCharacter m_sample;
};

// memo : 型チェックはコンパル時チェック
TEST_F(GameCharacterTest, m_healthメンバ変数の型) { checkType_health(); }
TEST_F(GameCharacterTest, m_powerメンバ変数の型) { checkType_power(); }
TEST_F(GameCharacterTest, decreaseHealthメンバ関数の返り値の型) { checkReturnType_decreaseHealth(); }
TEST_F(GameCharacterTest, showメンバ関数の返り値の型) { checkReturnType_show(); }

TEST_F(GameCharacterTest, コンストラクタ_正常系) {
  {
    const GameCharacter sample(10, 20);
    EXPECT_EQ(readHealth(sample), 10);
    EXPECT_EQ(readPower(sample), 20);
  }
  {
    const GameCharacter sample(1, 100);
    EXPECT_EQ(readHealth(sample), 1);
    EXPECT_EQ(readPower(sample), 100);
  }
  {
    const GameCharacter sample(100, 1);
    EXPECT_EQ(readHealth(sample), 100);
    EXPECT_EQ(readPower(sample), 1);
  }
}

TEST_F(GameCharacterTest, コンストラクタ_非正常系) {
  {
    const GameCharacter sample(0, 10);
    EXPECT_EQ(readHealth(sample), 1);
    EXPECT_EQ(readPower(sample), 10);
  }
  {
    const GameCharacter sample(10, 0);
    EXPECT_EQ(readHealth(sample), 10);
    EXPECT_EQ(readPower(sample), 1);
  }
  {
    const GameCharacter sample(0, 0);
    EXPECT_EQ(readHealth(sample), 1);
    EXPECT_EQ(readPower(sample), 1);
  }
}

TEST_F(GameCharacterTest, メソッドの実装_decreaseHealth_正常系) {
  GameCharacter sample(10, 10);
  writeHealth(sample, 10);
  writePower(sample, 10);
  sample.decreaseHealth(1);
  EXPECT_EQ(readHealth(sample), 9);
  EXPECT_EQ(readPower(sample), 10);
}

TEST_F(GameCharacterTest, メソッドの実装_decreaseHealth_非正常系) {
  GameCharacter sample(10, 10);
  writeHealth(sample, 0);
  writePower(sample, 10);
  sample.decreaseHealth(1);
  EXPECT_EQ(readHealth(sample), 0);
  EXPECT_EQ(readPower(sample), 10);
}

TEST_F(GameCharacterTest, メソッドの実装_show) {
  GameCharacter sample(13, 26);
  const auto expectedOutput = "(13,26)\n";

  testing::internal::CaptureStdout();
  sample.show();
  const auto actualOutput = testing::internal::GetCapturedStdout().c_str();

  EXPECT_STREQ(actualOutput, expectedOutput);
}

