#include "../include/observer.h"
#include "../include/npc.h"

FileObserver::FileObserver(const std::string& filename) {
    log_file.open(filename, std::ios::out);
}

FileObserver::~FileObserver() {
    log_file.close();
}

void FileObserver::update(const Npc& attacker, const Npc& defender) {
    if (log_file.is_open()) {
        log_file << "[file observer]: ";
        attacker.save(log_file);
        log_file << "kill ";
        defender.save(log_file);
        log_file << '\n';
        log_file.flush();
    } else {
        throw std::logic_error("File could not be opened");
    }
}

void StdinObserver::update(const Npc& attacker, const Npc& defender) {
    std::cout << "[stdin observer]:";
    attacker.print(std::cout) << ' ';
    std::cout << "kill ";
    defender.print(std::cout);
    std::cout << '\n';
}