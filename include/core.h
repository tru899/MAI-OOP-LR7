#ifndef CORE_H
#define CORE_H

#include <set>
#include <queue>
#include <string>
#include <thread>
#include <chrono>
#include <shared_mutex>
#include <memory>
#include <mutex>

#include "../include/npc.h"
#include "../include/factory_npc.h"

struct FightEvent {
    std::shared_ptr<Npc> attacker;
    std::shared_ptr<Npc> defender;
    
    FightEvent(std::shared_ptr<Npc> a, std::shared_ptr<Npc> d) 
        : attacker(std::move(a)), defender(std::move(d)) {}
};

class FightFunctor {
private:
    std::shared_ptr<std::queue<FightEvent>> events;
    std::shared_ptr<bool> is_work_thread;
    std::shared_ptr<std::shared_mutex> mtx;
    std::shared_ptr<std::mutex> mtx_cout;

public:
    FightFunctor() = delete;
    FightFunctor(std::shared_ptr<bool> is_work_thread,
        std::shared_ptr<std::shared_mutex> mtx,
        std::shared_ptr<std::mutex> mtx_cout);
    FightFunctor(const FightFunctor &other);
    void add_event(std::shared_ptr<Npc> attacker, std::shared_ptr<Npc> defender);
    bool throw_the_dice();
    void operator()();
};

class MoveFunctor {
private:
    std::set<std::shared_ptr<Npc>> set_npc;
    std::shared_ptr<FightFunctor> fight_functor_ptr;
    const int MAX_VALUE;
    std::shared_ptr<bool> is_work_thread;
    std::shared_ptr<std::shared_mutex> mtx;
    std::shared_ptr<std::mutex> mtx_cout;

public:
    MoveFunctor() = delete;
    explicit MoveFunctor(const std::set<std::shared_ptr<Npc>>& set_npc,
        std::shared_ptr<FightFunctor> fight_functor_ptr,
        const int MAX_VALUE,
        std::shared_ptr<bool> is_work_thread,
        std::shared_ptr<std::shared_mutex> mtx,
        std::shared_ptr<std::mutex> mtx_cout);
    void operator()();
};

void start_programm();

#endif