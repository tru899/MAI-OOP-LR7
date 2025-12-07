#include "../include/orc.h"
#include "../include/visitor_fight.h"

std::string Orc::info() const {
    return "orc(" + std::to_string(x) + ' ' + std::to_string(y) + ") [" + unique_name + ']';
}

bool Orc::accept(std::shared_ptr<Npc> npc_ptr) const {
    VisitorFightOrc visitor;
    return visitor.fight(npc_ptr);
}

unsigned int Orc::get_distance_step() const {
    return distance_step;
}

unsigned int Orc::get_distance_kill() const {
    return distance_kill;
}