#include "Agent.h"
#include <unordered_set>
#include <queue>
#include <algorithm>
#include "World.h"
using namespace std;

namespace {
  bool getPosition(Point2D check, World* world, std::unordered_map<Point2D, bool> visited, const std::unordered_set<Point2D>& frontierSet) {
    return !(visited.contains(check) || frontierSet.contains(check) || check == world->getCat() || world->getContent(check));
  }

  std::vector<Point2D> getVisitableNeighbors(World* world, const Point2D& current, const std::unordered_map<Point2D, bool>& visited,
                                                    const std::unordered_set<Point2D>& frontierSet) {
    auto outNeighbors = vector<Point2D>();
    auto preCheckNeighbors = world->neighbors(current);
    for(Point2D neighbor : preCheckNeighbors)
    {
      if(world->isValidPosition(neighbor) && getPosition(neighbor, world, visited, frontierSet))
      {
        outNeighbors.push_back(neighbor);
      }
    }
    return outNeighbors;
  }
  struct Point2DPrioritized {
    Point2D point;
    int priority;

    Point2DPrioritized(Point2D point, int priority): point(point), priority(priority) {}

    // the < and > are reversed because we will give higher priority to the ones with less value
    bool operator<(const Point2DPrioritized &other) const {
      return priority > other.priority;
    }
  };
}
std::vector<Point2D> Agent::generatePath(World* world) {
  unordered_map<Point2D, Point2D> cameFrom = unordered_map<Point2D, Point2D>();  // to build the flowfield and build the path
  priority_queue<Point2DPrioritized> frontier = priority_queue<Point2DPrioritized>();                   // to store next ones to visit
  unordered_set<Point2D> frontierSet = unordered_set<Point2D>();        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited = unordered_map<Point2D, bool>();      // use .at() to get data, if the element dont exist [] will give you wrong results
  // bootstrap state
  auto catPos = world->getCat();
  frontier.emplace(catPos, 0);
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  std::vector<int> closestWall = {abs(catPos.x + world->getWorldSideSize() / 2), abs(catPos.x - world->getWorldSideSize() / 2),
                                  abs(catPos.y + world->getWorldSideSize() / 2), abs(catPos.y - world->getWorldSideSize() / 2)};

  int smallestIndex = 0;
  int smallestVal = closestWall[0];
  for(int i = 0; i < closestWall.size(); i++)
  {
    if(closestWall[i] < smallestVal)
    {
      smallestVal = closestWall[i];
      smallestIndex = i;
    }
  }
  Point2D goalWall = catPos;
  switch (smallestIndex) {
    case 0:
      goalWall = Point2D(-world->getWorldSideSize() / 2, catPos.y);
      break;
    case 1:
      goalWall = Point2D(world->getWorldSideSize() / 2, catPos.y);
      break;
    case 2:
      goalWall = Point2D(catPos.x, -world->getWorldSideSize() / 2);
      break;
    case 3:
      goalWall = Point2D(catPos.x, world->getWorldSideSize() / 2);
      break;
    default:
      break;
  }
  while (!frontier.empty()) {
    // get the current from frontier
    // remove the current from frontierset
    // mark current as visited
    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    // iterate over the neighs:
    // for every neighbor set the cameFrom
    // enqueue the neighbors to frontier and frontierset
    // do this up to find a visitable border and break the loop
    Point2D const current = frontier.top().point;
    frontierSet.erase(current);
    frontier.pop();
    visited[current] = true;
    vector<Point2D> const neighbors = getVisitableNeighbors(world, current, visited, frontierSet);
    for (Point2D const neighbor : neighbors) {
      cameFrom[neighbor] = current;
      // Check if the neighbor is a border
      if(world->catWinsOnSpace(neighbor))
      {
        borderExit = neighbor;
        frontier = priority_queue<Point2DPrioritized>();
        break;
      }
      int distFromExit = abs(neighbor.x - goalWall.x) + abs(neighbor.y - goalWall.y);
      // Add neighbor to checking list
      frontier.emplace(neighbor, distFromExit);
      frontierSet.insert(neighbor);
    }
  }

  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  if(borderExit == Point2D::INFINITE)
  {
    return {};
  }
  std::vector<Point2D> path = { borderExit };
  Point2D current = borderExit;
  while(!world->catCanMoveToPosition(current))
  {
    current = cameFrom.at(current);
    path.push_back(current);
  }
  return path;
}