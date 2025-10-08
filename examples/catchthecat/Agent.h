#ifndef AGENT_H
#define AGENT_H
#include "math/Point2D.h"

#include <unordered_map>
#include <vector>

class World;

class Agent {
public:
  explicit Agent() = default;

  virtual Point2D Move(World*) = 0;

  std::vector<Point2D> generatePath(World* world);
};

#endif  // AGENT_H
