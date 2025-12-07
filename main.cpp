#include <iostream>
#include <memory>
#include <fstream>
#include "include/core.h"
#include "include/factory_npc.h"
#include "include/observer.h"

int main() {
    // Чтение NPC из input.txt если файл существует
    std::ifstream in("input.txt");
    if (in.is_open()) {
        try {
            auto druid_from_file = FactoryNpc::create_npc_from_file(TypeNpc::druid, in);
            auto orc_from_file = FactoryNpc::create_npc_from_file(TypeNpc::orc, in);
            auto slaver_from_file = FactoryNpc::create_npc_from_file(TypeNpc::slaver, in);
            
            druid_from_file->print(std::cout) << "\n";
            orc_from_file->print(std::cout) << "\n";
            slaver_from_file->print(std::cout) << "\n";
        } catch (const std::exception& e) {
            std::cout << "error: " << e.what() << "\n";
        }
        in.close();
        std::cout << "\n";
    }
    
    // Простой тест создания NPC
    std::cout << "Тест создания NPC:\n";
    auto druid = FactoryNpc::create_npc(TypeNpc::druid, "ElvenDruid", 10, 20);
    auto orc = FactoryNpc::create_npc(TypeNpc::orc, "BloodOrc", 30, 40);
    auto slaver = FactoryNpc::create_npc(TypeNpc::slaver, "DarkSlaver", 50, 60);
    
    druid->print(std::cout) << "\n";
    orc->print(std::cout) << "\n";
    slaver->print(std::cout) << "\n\n";
    
    // Проверка движений
    std::cout << "Тест движения (границы 100x100):\n";
    orc->move(15, 25, 100);
    std::cout << "Орк переместился: (" << orc->get_x() << ", " << orc->get_y() << ")\n\n";
    
    // Проверка боя
    std::cout << "Тест правил боя:\n";
    std::cout << "Друид vs Орк: " << (druid->accept(orc) ? "может убить" : "не может убить") << "\n";
    std::cout << "Орк vs Работорговец: " << (orc->accept(slaver) ? "может убить" : "не может убить") << "\n";
    std::cout << "Работорговец vs Друид: " << (slaver->accept(druid) ? "может убить" : "не может убить") << "\n\n";
    
    // Наблюдатели
    auto console_obs = std::make_shared<StdinObserver>();
    auto file_obs = std::make_shared<FileObserver>("test_log.txt");
    druid->attach(console_obs);
    druid->attach(file_obs);
    
    // Симуляция уведомления
    std::cout << "Тест уведомлений:\n";
    druid->notify(*orc);
    
    
    return 0;
}
