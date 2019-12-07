#include "util.hpp"
#include "Program.hpp"
#include <algorithm>
#include <assert.h>

int getMaxThrust(Program &p, std::vector<int> vals)
{
    int biggest = 0;
    p.reset();

    do {
        std::vector<Program> ps;
        for (int i = 0; i < 5; i++) {
            auto np = p;
            np.run();
            np.input(vals[i]);

            ps.push_back(np);
        }

        int next = 0;
        bool running = true;
        while (running)
        {
            for (auto &np : ps) {
                np.input(next);
                next = np.output.back();
                if (np.done)
                    running = false;
            }
        }
        if (next > biggest)
            biggest = next;
    } while (std::next_permutation(vals.begin(), vals.end()));
    
    return biggest;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Input file required\n");
        return 1;
    }
    printf("Calculating Day 7\n");

    const auto file = readFile(argv[1]);
    std::vector<int> instructions;
    for (const auto &el : split(file.front(), ","))
        instructions.push_back(atoi(el.c_str()));


    auto program = Program(instructions);
    printf("Part 1: %d\n", getMaxThrust(program, { 0, 1, 2, 3, 4 }));
    printf("Part 2: %d\n", getMaxThrust(program, { 5, 6, 7, 8, 9 }));

    return 0;
}