#pragma once

#include <vector>
#include <iostream>
#include <stdint.h>

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
    std::vector<int64_t> initial;
    std::vector<int64_t> state;
    std::vector<int64_t> output;

    size_t  i;
    bool    done;
    int     relativeBase;

    Program(const std::vector<int64_t> &p)
        : initial(p), state(p), i(0), done(false), relativeBase(0) {}

    void run();
    void input(int val);
    int getArg(const Opcode &opcode, size_t pointer, size_t argc);
    void reset();
};

void Program::run()
{
    auto &p = this->state;
    while (!this->done)
    {
        const auto oc = Opcode(p[i]);
        if (oc.instruction == 99) {
            this->done = true;
            return;
        }

        switch (oc.instruction) {
            case 1: p[p[i + 3]] = getArg(oc, i, 1) + getArg(oc, i, 2)         ; i += 4; break; // Add
            case 2: p[p[i + 3]] = getArg(oc, i, 1) * getArg(oc, i, 2)         ; i += 4; break; // Mul
            case 3: return;
            case 4: this->output.push_back(getArg(oc, i, 1))                  ; i += 2; break; // Out
            case 5: if (getArg(oc, i, 1) != 0) i = getArg(oc, i, 2); else       i += 3; break; // Jit
            case 6: if (getArg(oc, i, 1) == 0) i = getArg(oc, i, 2); else       i += 3; break; // Jif
            case 7: p[p[i + 3]] = getArg(oc, i, 1) < getArg(oc, i, 2) ? 1 : 0 ; i += 4; break; // <
            case 8: p[p[i + 3]] = getArg(oc, i, 1) == getArg(oc, i, 2) ? 1 : 0; i += 4; break; // eq
            case 9: this->relativeBase += getArg(oc, i, 1)                    ; i += 2; break; // Adjust relative base
            default: printf("Invalid opcode! %llu\n", p[i]);exit(1)                   ; break; // ERR
        }
    }
}

void Program::input(int val)
{
    if (this->done) {
        return;
    }
    auto &p = this->state;
    p[p[i + 1]] = val;
    this->i += 2;
    this->run();
}

int Program::getArg(const Opcode &opcode, size_t pointer, size_t argc)
{
    auto &p = this->state;
    const auto loc = pointer + argc;

    switch(opcode.modes[argc - 1]) {
        case 0: return p[p[loc]];                     // Position mode
        case 1: return p[loc];                        // Immidiate mode
        case 2: return p[p[loc]] + this->relativeBase;// Relative mode
        default: return 0;
    }
}

void Program::reset()
{
    this->state = this->initial;
    this->output.clear();
    this->i = 0;
    this->done = false;
    this->relativeBase = 0;
}
