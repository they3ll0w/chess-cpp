#include "player.h"

Player::Player(TeamColor tc, Board *b, bool t): team{tc}, b{b}, t{t} {}

Player::~Player() {}

bool Player::getTurn() {
    return t;
}

TeamColor Player::getTeam() {
    return team;
}

void Player::setTeam(TeamColor tc) {
    team = tc;
}

void Player::setTurn(bool theTurn) {
    t = theTurn;
}
