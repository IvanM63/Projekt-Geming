#pragma once

class Enemy {
public:
    Enemy();
    Enemy(int health, int damage);
    void attack();
    void takeDamage(int damage);
    int getHealth() const;
    bool isDead() const;
private:
    int health_;
    int damage_;
};
