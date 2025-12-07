#ifndef SLAVER_H
#define SLAVER_H

#include "../include/npc.h"

class Slaver : public Npc {
private:
    unsigned int distance_step = 10;
    unsigned int distance_kill = 10;

public:
    Slaver() : Npc() {};
    Slaver(unsigned int x, unsigned int y, const std::string& name) : Npc(x, y, name) {};
    Slaver(Slaver&& other) noexcept : Npc(std::move(other)) {};
    Slaver(const Slaver& other) = default;

    unsigned int get_distance_step() const override;
    unsigned int get_distance_kill() const override;
    bool accept(std::shared_ptr<Npc> npc_ptr) const override;
    std::string info() const override;
};

#endif