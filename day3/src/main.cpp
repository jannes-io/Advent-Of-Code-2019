#include "util.hpp"
#include <vector>
#include <cmath>

enum class Direction {
    UP = 'U',
    RIGHT = 'R',
    DOWN = 'D',
    LEFT = 'L'
};

typedef std::pair<int, int> Pos;
typedef std::pair<Direction, int> Move;
typedef std::vector<Pos> Path;

std::vector<Move> parseInput(std::string input)
{
    std::vector<Move> result;

    for (const auto m : split(input, ","))
        result.push_back({ 
            Direction{m.substr(0, 1).c_str()[0]},
            atoi(m.substr(1, m.length() - 1).c_str()) 
        });
    return result;
}

void printPos(const Pos &p)
{
    printf("%d, %d\n", p.first, p.second);
}

Path walkPoints(const Pos &lastPos, const Move &m)
{
    Path result;
    for (int i = 1; i <= m.second; i++) {
        switch (m.first) {
            case Direction::UP:
                result.push_back({ lastPos.first, lastPos.second + i }); break;
            case Direction::RIGHT:
                result.push_back({ lastPos.first + i, lastPos.second }); break;
            case Direction::DOWN:
                result.push_back({ lastPos.first, lastPos.second - i }); break;
            case Direction::LEFT:
                result.push_back({ lastPos.first - i, lastPos.second }); break;
            default: break;
        }
    }
    return result;
}

Path getVisitedLocations(const std::vector<Move> &moves)
{
    Path result = {{0, 0}};
    Pos lastPos;

    for (const auto &m : moves) {
        lastPos = result.back();

        for (const auto p : walkPoints(lastPos, m)) {
            result.push_back(p);
        }
    }

    return result;
}

int findClosestIntersection(const Path &w1, const Path &w2)
{
    auto smallest = INT_MAX;
    for (const Pos &p1 : w1) {
        for (const Pos &p2 : w2) {
            if ((p1.first == 0 && p1.second == 0) || (p2.first == 0 && p2.second == 0))
                continue;

            if (p1.first == p2.first && p1.second == p2.second) {
                const auto d = abs(p1.first) + abs(p1.second);
                if (d < smallest)
                    smallest = d;
            }
        }
    }

    return smallest;
}

int main (int argc, char* argv[])
{
    if (argc < 2) {
        printf("Input file required\n");
        return 1;
    }
    printf("Calculating Day 3!\n");

    const auto input = readFile(argv[1]);
    const auto wire1 = parseInput(input[0]);
    const auto wire2 = parseInput(input[1]);
    const auto closest = findClosestIntersection(
        getVisitedLocations(wire1),
        getVisitedLocations(wire2)
    );
    
    printf("Part 1: %d\n", closest);

    return 0;
}