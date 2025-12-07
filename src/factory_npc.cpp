#include "../include/factory_npc.h"

std::shared_ptr<Npc> FactoryNpc::create_npc(const TypeNpc& type, const std::string& name, unsigned int x, unsigned int y) {
    switch (type) {
        case TypeNpc::druid:
            return std::make_shared<Druid>(x, y, name);
        case TypeNpc::orc:
            return std::make_shared<Orc>(x, y, name);
        case TypeNpc::slaver:
            return std::make_shared<Slaver>(x, y, name);
    }
    return nullptr;
}

std::shared_ptr<Npc> FactoryNpc::create_npc_from_file(const TypeNpc& type, std::ifstream& in) {
    switch (type) {
        case TypeNpc::druid: {
            Druid druid;
            if (in.is_open()) in >> druid;
            else throw std::logic_error("File not found");
            return std::make_shared<Druid>(druid);
        }
        case TypeNpc::orc: {
            Orc orc;
            if (in.is_open()) in >> orc;
            else throw std::logic_error("File not found");
            return std::make_shared<Orc>(orc);
        }
        case TypeNpc::slaver: {
            Slaver slaver;
            if (in.is_open()) in >> slaver;
            else throw std::logic_error("File not found");
            return std::make_shared<Slaver>(slaver);
        }
    }
    return nullptr;
}