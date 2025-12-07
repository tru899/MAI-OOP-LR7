#ifndef ORC_H
#define ORC_H

#include "../include/npc.h"

class Orc : public Npc {
private:
    unsigned int distance_step = 20;
    unsigned int distance_kill = 10;

public:
    Orc() : Npc() {};
    Orc(unsigned int x, unsigned int y, const std::string& name) : Npc(x, y, name) {};
    Orc(Orc&& other) noexcept : Npc(std::move(other)) {};
    Orc(const Orc& other) = default;

    unsigned int get_distance_step() const override;
    unsigned int get_distance_kill() const override;
    bool accept(std::shared_ptr<Npc> npc_ptr) const override;
    std::string info() const override;
};

#endif