#ifndef NPC_H
#define NPC_H

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <set>
#include "../include/observer.h"

class Npc {
    friend std::istream& operator>>(std::istream& is, Npc& npc);

protected:
    unsigned int x = 0;
    unsigned int y = 0;
    std::string unique_name;
    bool alive = true;
    std::vector<std::shared_ptr<Observer>> observers;

public:
    Npc() = default;
    Npc(unsigned int x, unsigned int y, const std::string& name);
    Npc(Npc&& other) noexcept;
    Npc(const Npc& other) = default;

    unsigned int get_x() const;
    unsigned int get_y() const;
    std::string get_name() const;
    virtual unsigned int get_distance_step() const = 0;
    virtual unsigned int get_distance_kill() const = 0;
    bool is_alive() const;
    void make_dead();
    virtual bool accept(std::shared_ptr<Npc> npc_ptr) const = 0;
    void attach(const std::shared_ptr<Observer>& observer);
    void detach(const std::shared_ptr<Observer>& observer);
    void notify(Npc& defender);
    virtual std::string info() const = 0;
    std::ostream& print(std::ostream& os) const;
    std::ofstream& save(std::ofstream& os) const;
    void move(int shift_x, int shift_y, int MAX_VALUE);
    virtual ~Npc() = default;
};

std::ostream& print_all_npc(std::ostream& os, std::set<std::shared_ptr<Npc>>& set_npc);

#endif