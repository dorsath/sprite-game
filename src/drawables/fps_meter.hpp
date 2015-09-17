#ifndef FPS_METER_HPP
#define FPS_METER_HPP

class FPSMeter: public Drawable {
  public:
    void draw(float dt);
    void setup();
    FPSMeter();

  private:
    Text* fpsCounter_;
    int nFrames;
    char text[11];
    std::string input_text;
    double lastTime;
};

#endif


