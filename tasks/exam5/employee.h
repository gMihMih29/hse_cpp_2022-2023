#pragma once

#include <algorithm>
#include <cstdint>

class IEmployee {
public:
    virtual void Work(int) = 0;
    virtual size_t Result() = 0;
};

class Programmer : public IEmployee {
public:
    void Work(int x) override {
        if (x < 0 && -x > written_lines) {
            written_lines = 0;
        } else {
            written_lines += x;
        }
    }

    void FindBug() {
        written_lines += 100;
    }

    size_t Result() override {
        return written_lines;
    }

private:
    size_t written_lines = 0;
};

class Painter : public IEmployee {
public:
    void Work(int x) override {
        finished_work += x;
        used_paint += 100 * x;
    }

    void CreativeCrisis(int x) {
        used_paint += x;
    }

    size_t Result() override {
        return finished_work;
    }

    size_t ResourcesSpent() {
        return used_paint;
    }

private:
    size_t used_paint = 0;
    size_t finished_work = 0;
};