#include "Cat.h"
#include "World.h"
#include <stdexcept>

static const int NEIGHBOR_COUNT = 5;

Point2D Cat::Move(World* world) {
  auto pos = world->getCat();
  auto path = generatePath(world);
  if(path.empty())
  {
    auto rand = Random::Range(0, NEIGHBOR_COUNT);
    Point2D movePos = pos;
    int count = 0;
    while(!world->catCanMoveToPosition(movePos)) {
      switch (rand) {
        case 0:
          movePos = World::NE(pos);
          break;
        case 1:
          movePos = World::NW(pos);
          break;
        case 2:
          movePos = World::E(pos);
          break;
        case 3:
          movePos = World::W(pos);
          break;
        case 4:
          movePos = World::SW(pos);
          break;
        case 5:
          movePos = World::SE(pos);
          break;
        default:
          movePos = pos;
          break;
      }
      rand++;
      if(rand > NEIGHBOR_COUNT)
      {
        rand = 0;
      }
      count++;
      if(count > NEIGHBOR_COUNT + 1)
      {
        return pos;
      }
    }
    return movePos;
  }
  return path.at(path.size() - 1);
}
