#ifndef OBSERVER_H
#define OBSERVER_H

#include <filesystem>
#include <iostream>
#include <fstream>
#include <memory>

class Npc;

class Observer {
public:
    virtual void update(const Npc& attacker, const Npc& defender) = 0;
    Observer() = default;
    Observer(const Observer&) = default;
    virtual ~Observer() = default;
};

class FileObserver : public Observer {
private:
    std::ofstream log_file;
public:
    explicit FileObserver(const std::string& filename);
    void update(const Npc& attacker, const Npc& defender) override;
    ~FileObserver() override;
};

class StdinObserver : public Observer {
public:
    void update(const Npc& attacker, const Npc& defender) override;
};

#endif