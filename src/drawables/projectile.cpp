#include "../config.hpp"

Projectile::Projectile(ProjectileConfig* config, Vec2 position_in, Vec2 velocity_in){
  model = &(config->model);
  texture = &(config->texture);
  program = &(config->program);
  velocity_.set(velocity_in.x, velocity_in.y);
  position_.set(position_in.x, position_in.y);
  animation_ = 0.0;
  timeFlew = 0.0;
}

void Projectile::draw(float dt) {
  timeFlew += dt;
  timeSinceAnimation += dt;
  if (timeFlew < 1.0) {
    position_ += velocity_ * dt;

    if (timeSinceAnimation > 0.2){
      animate();
      timeSinceAnimation = 0.0;
    }
  }

  glBindVertexArray(model->vao);
  glBindBuffer(GL_ARRAY_BUFFER, model->vbo);

  glUniform2f(program->uniform("position"), position_.x, position_.y);
  glUniform1i(program->uniform("animation"), animation_);

  glEnableVertexAttribArray(0);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glDrawArrays(GL_TRIANGLES, 0, model->verticesCount);
  glDisableVertexAttribArray(0);
}

void Projectile::animate(){
  animation_ = (float) (int(animation_ + 1) % 5);
}

