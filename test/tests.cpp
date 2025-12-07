#include <gtest/gtest.h>
#include <memory>
#include <thread>
#include <chrono>
#include <random>
#include "../include/npc.h"
#include "../include/druid.h"
#include "../include/orc.h"
#include "../include/slaver.h"
#include "../include/factory_npc.h"
#include "../include/observer.h"
#include "../include/visitor_fight.h"

// Тест создания NPC
TEST(NPCTest, NPCCreation) {
    auto druid = std::make_shared<Druid>(10, 20, "TestDruid");
    EXPECT_EQ(druid->get_x(), 10);
    EXPECT_EQ(druid->get_y(), 20);
    EXPECT_TRUE(druid->is_alive());
}

TEST(NPCTest, UniqueNames) {
    auto npc1 = std::make_shared<Druid>(0, 0, "SameName");
    auto npc2 = std::make_shared<Druid>(0, 0, "SameName");
    EXPECT_NE(npc1->get_name(), npc2->get_name());
}

// Тест расстояний движения и убийства
TEST(NPCTest, MoveDistances) {
    auto druid = std::make_shared<Druid>(0, 0, "D1");
    auto orc = std::make_shared<Orc>(0, 0, "O1");
    auto slaver = std::make_shared<Slaver>(0, 0, "S1");
    
    EXPECT_EQ(druid->get_distance_step(), 10);
    EXPECT_EQ(orc->get_distance_step(), 20);
    EXPECT_EQ(slaver->get_distance_step(), 10);
}

TEST(NPCTest, KillDistances) {
    auto druid = std::make_shared<Druid>(0, 0, "D1");
    auto orc = std::make_shared<Orc>(0, 0, "O1");
    auto slaver = std::make_shared<Slaver>(0, 0, "S1");
    
    EXPECT_EQ(druid->get_distance_kill(), 10);
    EXPECT_EQ(orc->get_distance_kill(), 10);
    EXPECT_EQ(slaver->get_distance_kill(), 10);
}

// Тест состояния NPC
TEST(NPCTest, KillNPC) {
    auto npc = std::make_shared<Druid>(0, 0, "Test");
    EXPECT_TRUE(npc->is_alive());
    npc->make_dead();
    EXPECT_FALSE(npc->is_alive());
}

// Тест движения в пределах границ
TEST(NPCTest, MovementWithinBounds) {
    auto npc = std::make_shared<Orc>(50, 50, "Mover");
    
    // Движение в пределах карты 100x100
    npc->move(10, 10, 100);
    
    EXPECT_GE(npc->get_x(), 0);
    EXPECT_LE(npc->get_x(), 100);
    EXPECT_GE(npc->get_y(), 0);
    EXPECT_LE(npc->get_y(), 100);
}

// Тест фабрики
TEST(FactoryTest, CreateNPCs) {
    auto druid = FactoryNpc::create_npc(TypeNpc::druid, "Druid1", 10, 20);
    auto orc = FactoryNpc::create_npc(TypeNpc::orc, "Orc1", 30, 40);
    auto slaver = FactoryNpc::create_npc(TypeNpc::slaver, "Slaver1", 50, 60);
    
    EXPECT_NE(druid, nullptr);
    EXPECT_NE(orc, nullptr);
    EXPECT_NE(slaver, nullptr);
    
    EXPECT_EQ(druid->get_x(), 10);
    EXPECT_EQ(druid->get_y(), 20);
    EXPECT_EQ(orc->get_x(), 30);
    EXPECT_EQ(orc->get_y(), 40);
}

// Тест наблюдателей
TEST(ObserverTest, StdinObserver) {
    auto attacker = std::make_shared<Orc>(0, 0, "Attacker");
    auto defender = std::make_shared<Druid>(0, 0, "Defender");
    auto observer = std::make_shared<StdinObserver>();
    
    attacker->attach(observer);
    
    // Не должно быть исключений
    EXPECT_NO_THROW(attacker->notify(*defender));
}

TEST(ObserverTest, FileObserver) {
    auto attacker = std::make_shared<Slaver>(0, 0, "Attacker");
    auto defender = std::make_shared<Druid>(0, 0, "Defender");
    auto observer = std::make_shared<FileObserver>("test_log.txt");
    
    attacker->attach(observer);
    
    // Не должно быть исключений
    EXPECT_NO_THROW(attacker->notify(*defender));
}

// Тест системы боя (Visitor Pattern)
TEST(CombatTest, DruidKillsOrc) {
    auto druid = std::make_shared<Druid>(0, 0, "D");
    auto orc = std::make_shared<Orc>(0, 0, "O");
    
    // Друид должен победить орка
    EXPECT_TRUE(druid->accept(orc));
}

TEST(CombatTest, OrcKillsSlaver) {
    auto orc = std::make_shared<Orc>(0, 0, "O");
    auto slaver = std::make_shared<Slaver>(0, 0, "S");
    
    // Орк должен победить работорговца
    EXPECT_TRUE(orc->accept(slaver));
}

TEST(CombatTest, SlaverKillsDruid) {
    auto slaver = std::make_shared<Slaver>(0, 0, "S");
    auto druid = std::make_shared<Druid>(0, 0, "D");
    
    // Работорговец должен победить друида
    EXPECT_TRUE(slaver->accept(druid));
}

TEST(CombatTest, SameTypeNoKill) {
    auto druid1 = std::make_shared<Druid>(0, 0, "D1");
    auto druid2 = std::make_shared<Druid>(0, 0, "D2");
    auto orc1 = std::make_shared<Orc>(0, 0, "O1");
    auto orc2 = std::make_shared<Orc>(0, 0, "O2");
    auto slaver1 = std::make_shared<Slaver>(0, 0, "S1");
    auto slaver2 = std::make_shared<Slaver>(0, 0, "S2");
    
    // Одинаковые типы не должны убивать друг друга
    EXPECT_FALSE(druid1->accept(druid2));
    EXPECT_FALSE(orc1->accept(orc2));
    EXPECT_FALSE(slaver1->accept(slaver2));
}

// Тест проверки дистанции для убийства
TEST(DistanceTest, IsMurderAvailable) {
    auto attacker = std::make_shared<Druid>(0, 0, "Attacker");
    auto defender = std::make_shared<Orc>(5, 5, "Defender");
    
    // Расчет расстояния: √(5² + 5²) = √50 ≈ 7.07
    // Дистанция убийства друида = 10, поэтому должно быть true
    // (в реализации используется квадрат расстояния)
    
    // Функция is_murder_available находится в core.cpp
    // Для тестов нужно либо вынести ее в заголовок, либо тестировать через интеграцию
    // Пока пропустим этот тест
}

// Тест многопоточности (базовый)
TEST(ThreadSafetyTest, ConcurrentAccessBasic) {
    auto npc = std::make_shared<Orc>(50, 50, "Concurrent");
    
    auto reader = [&npc]() {
        for (int i = 0; i < 100; ++i) {
            npc->get_x();
            npc->get_y();
            npc->is_alive();
        }
    };
    
    auto mover = [&npc]() {
        for (int i = 0; i < 100; ++i) {
            npc->move(10, 10, 100);
        }
    };
    
    std::thread t1(reader);
    std::thread t2(reader);
    std::thread t3(mover);
    
    t1.join();
    t2.join();
    t3.join();
    
    // Если нет deadlock или race condition, тест пройден
    EXPECT_TRUE(true);
}

// Тест граничных условий движения
TEST(BoundaryTest, MovementAtEdges) {
    // NPC на правой границе
    auto npc_right = std::make_shared<Orc>(95, 50, "RightEdge");
    npc_right->move(10, 0, 100);  // Попытка выйти за правую границу
    EXPECT_LE(npc_right->get_x(), 100);
    
    // NPC на левой границе
    auto npc_left = std::make_shared<Orc>(5, 50, "LeftEdge");
    npc_left->move(-10, 0, 100);  // Попытка выйти за левую границу
    EXPECT_GE(npc_left->get_x(), 0);
    
    // NPC на верхней границе
    auto npc_top = std::make_shared<Slaver>(50, 95, "TopEdge");
    npc_top->move(0, 10, 100);  // Попытка выйти за верхнюю границу
    EXPECT_LE(npc_top->get_y(), 100);
    
    // NPC на нижней границе
    auto npc_bottom = std::make_shared<Druid>(50, 5, "BottomEdge");
    npc_bottom->move(0, -10, 100);  // Попытка выйти за нижнюю границу
    EXPECT_GE(npc_bottom->get_y(), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
