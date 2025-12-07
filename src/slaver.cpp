#include "../include/slaver.h"
#include "../include/visitor_fight.h"

std::string Slaver::info() const {
    return "slaver(" + std::to_string(x) + ' ' + std::to_string(y) + ") [" + unique_name + ']';
}

bool Slaver::accept(std::shared_ptr<Npc> npc_ptr) const {
    VisitorFightSlaver visitor;
    return visitor.fight(npc_ptr);
}

unsigned int Slaver::get_distance_step() const {
    return distance_step;
}

unsigned int Slaver::get_distance_kill() const {
    return distance_kill;
}