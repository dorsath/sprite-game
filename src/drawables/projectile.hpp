#ifndef DRAWABLES_PROJECTILE_HPP
#define DRAWABLES_PROJECTILE_HPP

struct ProjectileConfig{
  Program program;
  Model model;
  Texture texture;
};


class Projectile {
  public:
    Program* program;
    Model* model;
    Texture* texture;
    float direction_;

    Projectile(ProjectileConfig* config, Vec2 position_in, Vec2 velocity_in);

    void draw(float dt);


  private:
    Vec2 velocity_;
    Vec2 position_;


};


#endif




