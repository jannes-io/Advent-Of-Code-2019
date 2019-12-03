#include "util.hpp"
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <iterator>

enum class Direction {
    UP = 'U',
    DOWN = 'D',
    RIGHT = 'R',
    LEFT = 'L'
};

struct Pos {
    int x;
    int y;

    Pos operator+(const Pos &other) const 
    {
        return {this->x + other.x, this->y + other.y};
    }

    bool operator<(const Pos &other) const
    {
        if (this->x == other.x) {
            return this->y < other.y;
        }
        return this->x < other.x;
    }

    void printPos() const
    {
        printf("%d, %d\n",this->x, this->y);
    }

    int distanceToOrigin() const
    {
        return abs(this->x) + abs(this->y);
    }
};

struct Move {
    Direction dir;
    int distance;
};

typedef std::set<Pos> Path;

struct WireData {
    Path path;
    std::map<Pos, int> costs;
};

std::vector<Move> parseInput(std::string input)
{
    std::vector<Move> result;

    for (const auto m : split(input, ","))
        result.push_back({ 
            Direction{m.substr(0, 1).c_str()[0]},
            int(atol(m.substr(1, m.length() - 1).c_str()))
        });
    return result;
}

Pos walkPoints(const Pos &lastPos, const Move &m, WireData &wd, int &steps)
{
    Pos p;
    for (int i = 1; i <= m.distance; i++) {
        steps++;
        switch (m.dir) {
            case Direction::UP:    p = { lastPos.x    , lastPos.y + i }; break;
            case Direction::DOWN:  p = { lastPos.x    , lastPos.y - i }; break;
            case Direction::RIGHT: p = { lastPos.x + i, lastPos.y     }; break;
            case Direction::LEFT:  p = { lastPos.x - i, lastPos.y     }; break;
            default: break;
        }
        wd.path.insert(p);
        wd.costs.insert({ p, steps });
    }
    return p;
}

WireData getVisitedLocations(const std::vector<Move> &moves)
{
    WireData result;
    Pos lastPos = { 0, 0 };
    int steps = 0;

    for (const auto &m : moves)
        lastPos = walkPoints(lastPos, m, result, steps);

    return result;
}

int findClosestIntersection(const Path &intersections)
{
    int closest = std::numeric_limits<int>::max();
    for (const auto &i : intersections) {
        const auto distance = i.distanceToOrigin();
        if (distance < closest)
            closest = distance;
    }

    return closest;
}

int findClosestStepCount(const Path &intersections, const WireData &w1, const WireData &w2)
{
    int cheapest = std::numeric_limits<int>::max();
    for (const auto &i : intersections) {
        const auto cost = w1.costs.at(i) + w2.costs.at(i);
        if (cost < cheapest)
            cheapest = cost;
    }
    return cheapest;
}

int main (int argc, char* argv[])
{
    if (argc < 2) {
        printf("Input file required\n");
        return 1;
    }
    printf("Calculating Day 3!\n");

    const auto input = readFile(argv[1]);
    const auto wire1 = getVisitedLocations(parseInput(input[0]));
    const auto wire2 = getVisitedLocations(parseInput(input[1]));

    Path intersections;
    std::set_intersection(
        wire1.path.begin(), wire1.path.end(),
        wire2.path.begin(), wire2.path.end(),
        std::inserter(intersections, intersections.begin()));

    const auto closest = findClosestIntersection(intersections);
    const auto cheapest = findClosestStepCount(intersections, wire1, wire2);
    
    printf("Part 1: %d\n", closest);
    printf("Part 2: %d\n", cheapest);

    return 0;
}