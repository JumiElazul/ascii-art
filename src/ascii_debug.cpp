#include "ascii_debug.h"
#include <chrono>
#include <fmt/color.h>

scoped_timer::scoped_timer(const std::string& name)
    : _name(name)
    , _start(std::chrono::high_resolution_clock::now())
{

}

scoped_timer::~scoped_timer()
{
    std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
    int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _start).count();
    fmt::print(fg(fmt::rgb(10, 255, 10)), "Time elapsed for {} was: {} milliseconds\n", _name, elapsed);
}
