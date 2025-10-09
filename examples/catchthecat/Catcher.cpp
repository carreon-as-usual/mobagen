#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
  std::vector<Point2D> path = generatePath(world);
  if(!path.empty())
  {
  return path[0];
  }
  Point2D catPos = world->getCat();
  auto neighbors = world->neighbors(catPos);
  std::vector<Point2D> possiblePoints = std::vector<Point2D>();
  for(auto neighbor : neighbors)
  {
    if(world->isValidPosition(neighbor) && !world->getContent(neighbor))
    {
      possiblePoints.push_back(neighbor);
    }
  }
  int chosenNeighbor = Random::Range(0, possiblePoints.size() - 1);
  return possiblePoints[chosenNeighbor];
}
