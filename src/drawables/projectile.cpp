#include "../config.hpp"

Projectile::Projectile(ProjectileConfig* config, Vec2 position_in, Vec2 velocity_in){
  model = &(config->model);
  texture = &(config->texture);
  program = &(config->program);
  velocity_.set(velocity_in.x, velocity_in.y);
  position_.set(position_in.x, position_in.y);
  std::cout << position_in.y << "\n";
}

void Projectile::draw(float dt) {
  position_ += velocity_ * dt;
  glBindVertexArray(model->vao);
  glBindBuffer(GL_ARRAY_BUFFER, model->vbo);

  glUniform2f(program->uniform("position"), position_.x, position_.y);

  glEnableVertexAttribArray(0);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glDrawArrays(GL_TRIANGLES, 0, model->verticesCount);
  glDisableVertexAttribArray(0);
}

