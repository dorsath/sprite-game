#include "config.hpp"

Timeout::Timeout(float timeLimit){
  timePassed_ = 0.0;
  setTimeLimit(timeLimit);
}

void Timeout::tick(float dt){
  timePassed_ += dt;
}

bool Timeout::ready(){
  return timePassed_ > timeLimit_;
}

void Timeout::reset(){
  timePassed_ = 0.0;
}

void Timeout::setTimeLimit(float timeLimit){
  timeLimit_ = timeLimit;
}

Timeout::Timeout(){
  timeLimit_ = 1.0;
}
