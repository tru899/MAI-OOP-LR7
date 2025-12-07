#ifndef VISITOR_FIGHT_H
#define VISITOR_FIGHT_H

#include <memory>
#include "npc.h"
#include "druid.h"
#include "orc.h"
#include "slaver.h"

class IVisitorFight {
public:
    virtual bool fight(std::shared_ptr<Npc> defender) = 0;
    virtual ~IVisitorFight() = default;
};

struct VisitorFightDruid : IVisitorFight {
    bool fight(std::shared_ptr<Npc> defender) override;
};

struct VisitorFightOrc : IVisitorFight {
    bool fight(std::shared_ptr<Npc> defender) override;
};

struct VisitorFightSlaver : IVisitorFight {
    bool fight(std::shared_ptr<Npc> defender) override;
};

#endif