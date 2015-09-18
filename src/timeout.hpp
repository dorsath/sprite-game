#ifndef TIMEOUT_HPP
#define TIMEOUT_HPP

class Timeout {
  public:
    Timeout(float timeLimit);
    Timeout();
    void setTimeLimit(float timeLimit);
    void tick(float dt);
    bool ready();
    void reset();

  private:
    float timePassed_;
    float timeLimit_;

};

#endif
