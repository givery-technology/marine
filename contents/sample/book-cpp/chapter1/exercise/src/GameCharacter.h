#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H

class GameCharacter {

  friend class GameCharacterTest;

public:
  GameCharacter(int health, int power);
  void decreaseHealth(int health);
  void show();

private:
  int m_health;
  int m_power;
};

#endif // GAME_CHARACTER_H

