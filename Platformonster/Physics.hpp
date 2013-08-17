#pragma once
#include "Util.hpp"
#include "Actor.hpp"
#include "Level.hpp"

struct Kinetic
{
    Point position;
    Point velocity;
    Point acceleration;

    Kinetic createAdvancement(float delta_time) const {
        // Proper way of integrating
        // "stolen" from http://www.niksula.hut.fi/~hkankaan/Homepages/gravity.html
        Kinetic temp (*this);
        temp.update(delta_time);
        return temp;
    }

    void update(float delta_time) {
        velocity += acceleration*delta_time / 2.f;
        position += velocity*delta_time;
        velocity += acceleration*delta_time / 2.f;
    }

    void rawMove(Point delta) {
        position += delta;
    }
};

struct Entity {
    Kinetic k;
    // only rectangles supported right now
    Point size;
};

struct AABB {
    float top, left, bot, right;
};

AABB fromEntity(Entity entity) {
    Point hs = entity.size * .5f;
    float top = entity.k.position.y + hs.y;
    float left = entity.k.position.x - hs.x;
    float bot = entity.k.position.y - hs.y;
    float right = entity.k.position.x - hs.x;
    return AABB { top, left, bot, right };
}

Entity collision(Direction dir, Entity entity, bool bounce) {
    Entity temp(entity);
    switch (dir) {
    case Direction::Up:
    case Direction::Down:
        if (bounce) {
            temp.k.acceleration.y *= -1.f;
            temp.k.velocity.y *= -1.f;
        }
        else  {
            temp.k.acceleration.y = 0.f;
            temp.k.velocity.y = 0.f;
        }
        break;
    case Direction::Left:
    case Direction::Right:
        if (bounce) {
            temp.k.acceleration.x *= -1.f;
            temp.k.velocity.x *= -1.f;
        }
        else  {
            temp.k.acceleration.x = 0.f;
            temp.k.velocity.x = 0.f;
        }
        break;
    }
    return temp;
}

Entity solve(Entity const& entity, Level const& level, float delta) {
    auto nextKinetic = entity.k.createAdvancement(delta);
    Entity nextEntity { nextKinetic, entity.size };

    //going-right direction bit
    bool xbit = (entity.k.velocity.x > 0.f);
    bool ybit = (entity.k.velocity.y > 0.f);

    AABB ex(fromEntity(entity));
    AABB n_ex(fromEntity(nextEntity));

    if (xbit) { // check right side
        if (integralPart(ex.right) != integralPart(n_ex.right)) {
            // we have to check every tile that could possibly collide with our shape
            int tileX = integralPart(n_ex.right);
            int tileY = integralPart(n_ex.top);
            if (!(level.isPassable(tileX, tileY)))
                nextEntity = collision(Direction::Right, entity, false);
        }
    }
    // no collisions occured, return unmodified
    return nextEntity;
}

