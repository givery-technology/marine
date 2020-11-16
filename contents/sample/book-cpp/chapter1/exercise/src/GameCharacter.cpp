#include "GameCharacter.h"
#include <iostream>

GameCharacter::GameCharacter(int health, int power)
    : m_health(health <= 0 ? 1 : health), m_power(power <= 0 ? 1 : power) {}

void GameCharacter::decreaseHealth(int health) {
  m_health -= health;
  if (m_health < 0) {
    m_health = 0;
  }
}

void GameCharacter::show() { std::cout << "(" << m_health << "," << m_power << ")" << std::endl; }

