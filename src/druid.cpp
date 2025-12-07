#include "../include/druid.h"
#include "../include/visitor_fight.h"

std::string Druid::info() const {
    return "druid(" + std::to_string(x) + ' ' + std::to_string(y) + ") [" + unique_name + ']';
}

bool Druid::accept(std::shared_ptr<Npc> npc_ptr) const {
    VisitorFightDruid visitor;
    return visitor.fight(npc_ptr);
}

unsigned int Druid::get_distance_step() const {
    return distance_step;
}

unsigned int Druid::get_distance_kill() const {
    return distance_kill;
}