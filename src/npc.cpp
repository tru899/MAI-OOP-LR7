#include "../include/npc.h"
#include <memory>

std::istream& operator>>(std::istream& is, Npc& npc) {
    is >> npc.x >> npc.y >> npc.unique_name;
    return is;
}

Npc::Npc(Npc&& other) noexcept {
    unique_name = std::move(other.unique_name);
    x = other.x;
    y = other.y;
}

Npc::Npc(unsigned int x, unsigned int y, const std::string& name) {
    static std::set<std::string> names;
    static unsigned int count = 0;

    this->x = x;
    this->y = y;
    std::string copy_name = name;
    if (names.count(name) != 0) {
        copy_name += std::to_string(count++);
    }
    unique_name = std::move(copy_name);
    names.insert(name);
}

unsigned int Npc::get_x() const {
    return x;
}

unsigned int Npc::get_y() const {
    return y;
}

std::string Npc::get_name() const {
    return unique_name;
}

bool Npc::is_alive() const {
    return alive;
}

void Npc::make_dead() {
    alive = false;
}

void Npc::attach(const std::shared_ptr<Observer>& observer) {
    observers.push_back(observer);
}

void Npc::detach(const std::shared_ptr<Observer>& observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Npc::notify(Npc& defender) {
    for (auto& observer : observers) {
        observer->update(*this, defender);
    }
}

std::ofstream& Npc::save(std::ofstream& os) const {
    os << info();
    return os;
}

std::ostream& Npc::print(std::ostream& os) const {
    os << info();
    return os;
}

void Npc::move(int shift_x, int shift_y, int MAX_VALUE) {
    if (shift_x + static_cast<int>(x) <= MAX_VALUE && shift_x + static_cast<int>(x) >= 0) {
        x += shift_x;
    }

    if (shift_y + static_cast<int>(y) <= MAX_VALUE && shift_y + static_cast<int>(y) >= 0) {
        y += shift_y;
    }
}

std::ostream& print_all_npc(std::ostream& os, std::set<std::shared_ptr<Npc>>& set_npc) {
    for (auto& npc : set_npc) {
        npc->print(os);
    }
    return os;
}