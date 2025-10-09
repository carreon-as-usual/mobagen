#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
  if(!path.empty())
  {
  return path[0];
  }
  Point2D catPos = world->getCat();
  auto neighbors = world->neighbors(catPos);
  for(auto neighbor : neighbors)
  {
    if(world->isValidPosition(neighbor) && !world->getContent(neighbor))
    {
      return neighbor;
    }
  }
}
