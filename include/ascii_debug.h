#ifndef JUMI_ASCII_ART_ASCII_DEBUG_H
#define JUMI_ASCII_ART_ASCII_DEBUG_H
#include <chrono>
#include <string>

class scoped_timer
{
public:
    scoped_timer(const std::string& name);
    ~scoped_timer();
    scoped_timer(const scoped_timer& rhs) = delete;
    scoped_timer& operator=(const scoped_timer& rhs) = delete;
    scoped_timer(scoped_timer&& rhs) = delete;
    scoped_timer& operator=(scoped_timer&& rhs) = delete;

private:
    std::string _name;
    std::chrono::time_point<std::chrono::high_resolution_clock> _start;
};

#endif
