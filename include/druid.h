#ifndef DRUID_H
#define DRUID_H

#include "../include/npc.h"

class Druid : public Npc {
private:
    unsigned int distance_step = 10;
    unsigned int distance_kill = 10;

public:
    Druid() : Npc() {};
    Druid(unsigned int x, unsigned int y, const std::string& name) : Npc(x, y, name) {};
    Druid(Druid&& other) noexcept : Npc(std::move(other)) {};
    Druid(const Druid& other) = default;

    unsigned int get_distance_step() const override;
    unsigned int get_distance_kill() const override;
    bool accept(std::shared_ptr<Npc> npc_ptr) const override;
    std::string info() const override;
};

#endif