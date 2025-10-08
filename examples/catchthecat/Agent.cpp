#include "Agent.h"
#include <unordered_set>
#include <queue>
#include "World.h"
using namespace std;

static std::vector<Point2D> getVisitableNeighbors(World* world, const Point2D& current, const std::unordered_map<Point2D, bool> visited) {
  auto outNeighbors = vector<Point2D>();
  if (world->isValidPosition(Point2D(current.x - 1, current.y - 1)) && !visited.at(World::NW(current))) {
    outNeighbors.push_back(World::NW(current));
  }
  if (world->isValidPosition(Point2D(current.x - 1, current.y)) && !visited.at(World::W(current))) {
    outNeighbors.push_back(World::W(current));
  }
  if (world->isValidPosition(Point2D(current.x - 1, current.y + 1)) && !visited.at(World::SW(current))) {
    outNeighbors.push_back(World::SW(current));
  }
  if (world->isValidPosition(Point2D(current.x + 1, current.y + 1)) && !visited.at(World::SE(current))) {
    outNeighbors.push_back(World::SE(current));
  }
  if (world->isValidPosition(Point2D(current.x + 1, current.y)) && !visited.at(World::E(current))) {
    outNeighbors.push_back(World::E(current));
  }
  if (world->isValidPosition(Point2D(current.x + 1, current.y - 1)) && !visited.at(World::NE(current))) {
    outNeighbors.push_back(World::NE(current));
  }
  return outNeighbors;
}

std::vector<Point2D> Agent::generatePath(World* world) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  queue<Point2D> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  auto catPos = world->getCat();
  frontier.push(catPos);
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  while (!frontier.empty()) {
    // get the current from frontier
    // remove the current from frontierset
    // mark current as visited
    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    // iterate over the neighs:
    // for every neighbor set the cameFrom
    // enqueue the neighbors to frontier and frontierset
    // do this up to find a visitable border and break the loop
    Point2D const current = frontier.front();
    frontier.pop();
    visited[current] = true;
    vector<Point2D> const neighbors = getVisitableNeighbors(world, current, visited);
    for (Point2D const neighbor : neighbors) {
      cameFrom.at(neighbor) = current;
      frontier.push(neighbor);
      frontierSet.insert(neighbor);
    }
  }

  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  return vector<Point2D>();
}