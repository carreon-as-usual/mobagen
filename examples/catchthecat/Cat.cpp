#include "Cat.h"
#include "World.h"
#include <stdexcept>

static const int NEIGHBOR_COUNT = 5;

Point2D Cat::Move(World* world) {
  auto pos = world->getCat();
  auto path = generatePath(world);
  if(!path.empty()) {
    return path.at(path.size() - 1);
  }
  auto neighbors = world->neighbors(pos);
  int chosenIndex = 0;
  if(pos.x < 0)
  {
    if(pos.y < 0)
    {
      chosenIndex = 5;
    } else if(pos.y == 0)
    {
      chosenIndex = 2;
    } else {
      chosenIndex = 0;
    }
  } else {
    if(pos.y < 0)
    {
      chosenIndex = 4;
    } else if(pos.y == 0)
    {
      chosenIndex = 3;
    } else {
      chosenIndex = 1;
    }
  }
  int exitLoop = 0;
  while(exitLoop < NEIGHBOR_COUNT + 1)
  {
    if(world->catcherCanMoveToPosition(neighbors[chosenIndex]) && !world->getContent(neighbors[chosenIndex]))
    {
      return neighbors[chosenIndex];
    }
    chosenIndex++;
    exitLoop++;
    if(chosenIndex > NEIGHBOR_COUNT)
    {
      chosenIndex = 0;
    }
  }
}
