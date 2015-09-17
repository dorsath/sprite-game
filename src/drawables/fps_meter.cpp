#include "../config.hpp"

FPSMeter::FPSMeter(){
  fpsCounter_ = new Text("spf:       ", -1, -1);
}

void FPSMeter::draw(float dt){
  nFrames++;

  lastTime += dt;
  if (lastTime > 0.2){
    sprintf(text, "spf: %.4f", lastTime / float(nFrames));
    input_text.assign(text);
    fpsCounter_->setText(input_text);

    nFrames = 0;
    lastTime = 0.0;
  }

  fpsCounter_->draw(dt);
}

void FPSMeter::setup(){
  fpsCounter_->setup();
  lastTime = 0;
}

