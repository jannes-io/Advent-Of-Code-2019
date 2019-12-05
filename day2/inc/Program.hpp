#pragma once

#include <vector>

struct Opcode {
    int instruction;
    int modes[3];

    Opcode(int n)
    {
        int opcode[5] = {};
        size_t i = 5;
        while (n > 0)
        {
            int digit = n % 10;
            n /= 10;
            opcode[--i] = digit;
        }

        this->modes[2] = opcode[0];
        this->modes[1] = opcode[1];
        this->modes[0] = opcode[2];
        this->instruction = opcode[3] * 10 + opcode[4];
    }
};

struct Program {
    std::vector<int> initial;
    std::vector<int> state;
    int input;

    Program(const std::vector<int> &p)
        : initial(p), state(p) {}

    int run();
    int getArg(const Opcode &opcode, size_t pointer, size_t argc);
    void reset();
};

int Program::run()
{
    auto &p = this->state;
    size_t i = 0;

    while (p[i] != 99)
    {
        const auto oc = Opcode(p[i]);
        switch (oc.instruction) {
            case 1: p[p[i + 3]] = getArg(oc, i, 1) + getArg(oc, i, 2)         ; i += 4; break; // Add
            case 2: p[p[i + 3]] = getArg(oc, i, 1) * getArg(oc, i, 2)         ; i += 4; break; // Mul
            case 3: p[p[i + 1]] = this->input                                 ; i += 2; break; // In
            case 4: printf("%d\n", getArg(oc, i, 1))                          ; i += 2; break; // Out
            case 5: if (getArg(oc, i, 1) != 0) i = getArg(oc, i, 2); else       i += 3; break; // Jit
            case 6: if (getArg(oc, i, 1) == 0) i = getArg(oc, i, 2); else       i += 3; break; // Jif
            case 7: p[p[i + 3]] = getArg(oc, i, 1) < getArg(oc, i, 2) ? 1 : 0 ; i += 4; break; // <
            case 8: p[p[i + 3]] = getArg(oc, i, 1) == getArg(oc, i, 2) ? 1 : 0; i += 4; break; // eq
            default: printf("Invalid opcode! %d\n", p[i]);exit(1)                     ; break; // ERR
        }
    }
    return p[0];
}

int Program::getArg(const Opcode &opcode, size_t pointer, size_t argc)
{
    auto &p = this->state;
    return opcode.modes[argc - 1] == 0
        ? p[p[pointer + argc]]
        : p[pointer + argc];
}

void Program::reset()
{
    this->state = this->initial;
}
