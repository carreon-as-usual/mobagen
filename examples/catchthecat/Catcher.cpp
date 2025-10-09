#include "Catcher.h"
#include "World.h"

static const int NEIGHBOR_COUNT = 5;

Point2D Catcher::Move(World* world) {
  std::vector<Point2D> path = generatePath(world);
  if(!path.empty())
  {
  return path[0];
  }
  auto catPos = world->getCat();
  auto neighbors = world->neighbors(catPos);
  int chosenIndex = 0;
  if(catPos.x < 0)
  {
    if(catPos.y < 0)
    {
      chosenIndex = 5;
    } else if(catPos.y == 0)
    {
      chosenIndex = 2;
    } else {
      chosenIndex = 0;
    }
  } else {
    if(catPos.y < 0)
    {
      chosenIndex = 4;
    } else if(catPos.y == 0)
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
