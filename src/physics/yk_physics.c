#include "yk/math/yk_math_types.h"
#include "yk/rendering/yk_renderer2d.h"
#include "yk_yektor.h"
#include <yk/rendering/yk_color.h>
#include <yk/physics/yk_physics.h>

b1 yk_particle_collision_test(YK_Particle2d *a, YK_Particle2d *b);
void yk_particle_collision_shape_update(YK_Particle2d *particle);
void yk_aabb_update_pos(YK_AABB *out, v2f pos);

YK_Yektor particles;

void yk_physics_innit()
{
  yk_yektor_innit(&particles, 5, sizeof(YK_Particle2d));
}

f4 accumulator = 0.f;
#define fixed_delta (0.01f)
#define half_a_t2 (fixed_delta * fixed_delta * 0.5f)

void yk_particle_integrate(f4 delta)
{
  accumulator += delta;

  while (accumulator > fixed_delta)
  {
    i4 size = particles.size;

    for (i4 i = 0; i < size; i++)
    {
      YK_Particle2d *particle = yk_yektor_get(&particles, i);
      // s = ut + 0.5at^2
      // particle->vel * delta + 0.5f * particle->acc * delta * delta;

      v2f temp = yk_math_vec2f_mul_s(&particle->vel, fixed_delta);
      v2f temp2 = yk_math_vec2f_mul_s(&particle->acc, half_a_t2);
      v2f temp3 = yk_math_vec2f_add(&temp, &temp2);
      temp3.y -= particle->gravity * fixed_delta;

      particle->pos = yk_math_vec2f_add(&particle->pos, &temp3);

      if (particle->collision_shape_type)
      {
        yk_particle_collision_shape_update(particle);
      }
    }

    for (i4 i = 0; i < size; i++)
    {
      YK_Particle2d *particle1 = yk_yektor_get(&particles, i);

      if (!particle1->collision_shape_type)
      {
        continue;
      }
      if (particle1->static_object)
      {
        continue;
      }

      for (i4 j = i + 1; j < size; j++)
      {
        YK_Particle2d *particle2 = yk_yektor_get(&particles, j);
        if (!particle2->collision_shape_type)
        {
          continue;
        }
        if (yk_particle_collision_test(particle1, particle2))
        {
          yk_particle_overlap_resolve(particle1, particle2);
        }
      }
    }

    accumulator -= fixed_delta;
  }
}

b1 yk_physics_aabb_overlap_test(YK_AABB *a, YK_AABB *b)
{
  f4 d1x = b->min.x - a->max.x;
  f4 d1y = b->min.y - a->max.y;
  f4 d2x = a->min.x - b->max.x;
  f4 d2y = a->min.y - b->max.y;

  if (d1x > 0.0f || d1y > 0.0f)
  {
    return false;
  }

  if (d2x > 0.0f || d2y > 0.0f)
  {
    return false;
  }

  return true;
}

void yk_particle_overlap_resolve(YK_Particle2d *a, YK_Particle2d *b)
{
  YK_AABB *aabb1 = &a->collider.collision_shape.aabb;
  YK_AABB *aabb2 = &b->collider.collision_shape.aabb;

  v2f overlap;

  overlap.x = fmin(aabb1->max.x - aabb2->min.x, aabb2->max.x - aabb1->min.x);
  overlap.y = fmin(aabb1->max.y - aabb2->min.y, aabb2->max.y - aabb1->min.y);

  if (overlap.x > 0 && overlap.y > 0)
  {
    // resolve the overlap along the axis with the most overlap
    if (overlap.x < overlap.y)
    {
      if (yk_aabb_get_pos(aabb1).x < yk_aabb_get_pos(aabb2).x)
      {
        a->pos.x -= overlap.x / 2;
        if (!b->static_object)
          b->pos.x += overlap.x / 2;
      }
      else
      {
        a->pos.x += overlap.x / 2;
        if (!b->static_object)

          b->pos.x -= overlap.x / 2;
      }
    }
    else
    {
      if (yk_aabb_get_pos(aabb1).y < yk_aabb_get_pos(aabb2).y)
      {
        a->pos.y -= overlap.y / 2;
        if (!b->static_object)
        {
          b->pos.y += overlap.y / 2;
        }
      }
      else
      {
        a->pos.y += overlap.y / 2;

        if (!b->static_object)
        {
          b->pos.y -= overlap.y / 2;
        }
      }
    }
  }
}

b1 yk_particle_collision_test(YK_Particle2d *a, YK_Particle2d *b)
{
  i4 shape_a = a->collision_shape_type;
  i4 shape_b = b->collision_shape_type;

  if (shape_a == YK_COLLISION_SHAPE_AABB && shape_b == YK_COLLISION_SHAPE_AABB)
  {
    return yk_physics_aabb_overlap_test(&a->collider.collision_shape.aabb, &b->collider.collision_shape.aabb);
  }

  return false;
}

YK_Particle2d *yk_particles_create(v2f pos, f4 damping, f4 mass)
{
  return yk_yektor_push(&particles, &(YK_Particle2d){pos, {0, 0}, {0, 0}, damping, 1.f / mass, YK_COLLISION_SHAPE_NONE, false, false, 0.f});
}

void yk_particle_set_aabb(YK_Particle2d *out, v2f pos, v2f scale)
{
  out->collision_shape_type = YK_COLLISION_SHAPE_AABB;
  out->collider.offset = pos;
  out->collider.collision_shape.aabb = yk_aabb_create(yk_math_vec2f_add(&pos, &out->pos), scale);
}

YK_AABB yk_aabb_create(v2f pos, v2f scale)
{
  YK_AABB out;
  out.min.x = pos.x - scale.x / 2.0f;
  out.min.y = pos.y - scale.y / 2.0f;
  out.max.x = pos.x + scale.x / 2.0f;
  out.max.y = pos.y + scale.y / 2.0f;
  return out;
}

void yk_aabb_update_pos(YK_AABB *out, v2f pos)
{
  v2f scale = yk_aabb_get_scale(out);

  out->min.x = pos.x - scale.x / 2.0f;
  out->min.y = pos.y - scale.y / 2.0f;
  out->max.x = pos.x + scale.x / 2.0f;
  out->max.y = pos.y + scale.y / 2.0f;
}

void yk_particle_collision_shape_update(YK_Particle2d *particle)
{
  switch (particle->collision_shape_type)
  {
  case 1:
    yk_aabb_update_pos(&particle->collider.collision_shape.aabb, yk_math_vec2f_add(&particle->pos, &particle->collider.offset));
    break;

  default:
    printf("Control shouldn't reach here. Particle collision shape update called on particle w/o collision shape");
  }
}

void yk_particle_collison_shape_debug_draw(YK_Renderer2d *ren)
{
  i4 size = particles.size;
  for (i4 i = 0; i < size; i++)
  {
    YK_Particle2d *particle = yk_yektor_get(&particles, i);
    if (!particle->debug_draw)
    {
      continue;
    }
    switch (particle->collision_shape_type)
    {
    case 1:
      YK_AABB *aabb = &particle->collider.collision_shape.aabb;
      v2f pos = yk_aabb_get_pos(aabb);
      v2f scale = yk_aabb_get_scale(aabb);
      yk_renderer2d_render_quad(ren, &(YK_Transform2d){.pos = pos, .scale = scale, .rot_z = 0.f}, &(YK_Color){1, 0, 0, 0.4f});
    }
  }
}

v2f yk_aabb_get_pos(YK_AABB *aabb)
{
  v2f out;
  out.x = (aabb->min.x + aabb->max.x) / 2.f;
  out.y = (aabb->min.y + aabb->max.y) / 2.f;
  return out;
}

v2f yk_aabb_get_scale(YK_AABB *aabb)
{
  v2f out;
  out.x = aabb->max.x - aabb->min.x;
  out.y = aabb->max.y - aabb->min.y;
  return out;
}

// https://gdbooks.gitbooks.io/3dcollisions/content/Chapter3/raycast_aabb.html

b1 yk_physics_aabb_raycast(const YK_AABB *aabb, v2f origin, v2f dir, f4 distance)
{
  f4 divx = 1.0f / dir.x;
  f4 divy = 1.0f / dir.y;

  f4 tmin = (aabb->min.x - origin.x) * divx;
  f4 tmax = (aabb->max.x - origin.x) * divx;
  f4 tymin = (aabb->min.y - origin.y) * divy;
  f4 tymax = (aabb->max.y - origin.y) * divy;

  if ((tmin > tymax) || (tymin > tmax))
  {
    return false;
  }

  if (tymin > tmin)
  {
    tmin = tymin;
  }

  if (tymax < tmax)
  {
    tmax = tymax;
  }

  return (tmin < 1.0f && tmax > 0.0f);
}