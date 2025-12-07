#ifndef FACTORY_NPC_H
#define FACTORY_NPC_H

#include <memory>
#include <fstream>
#include "../include/npc.h"
#include "../include/druid.h"
#include "../include/orc.h"
#include "../include/slaver.h"

enum class TypeNpc { druid, orc, slaver };

class FactoryNpc {
public:
    static std::shared_ptr<Npc> create_npc(const TypeNpc& type, const std::string& name, unsigned int x = 0, unsigned int y = 0);
    static std::shared_ptr<Npc> create_npc_from_file(const TypeNpc& type, std::ifstream& in);
};

#endif