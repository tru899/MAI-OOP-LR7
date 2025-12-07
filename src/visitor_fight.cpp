#include "../include/visitor_fight.h"

bool VisitorFightDruid::fight(std::shared_ptr<Npc> defender) {
    // Друид побеждает орка
    if (std::dynamic_pointer_cast<Orc>(defender)) {
        return true;
    }
    return false;
}

bool VisitorFightOrc::fight(std::shared_ptr<Npc> defender) {
    // Орк побеждает работорговца
    if (std::dynamic_pointer_cast<Slaver>(defender)) {
        return true;
    }
    return false;
}

bool VisitorFightSlaver::fight(std::shared_ptr<Npc> defender) {
    // Работорговец побеждает друида
    if (std::dynamic_pointer_cast<Druid>(defender)) {
        return true;
    }
    return false;
}