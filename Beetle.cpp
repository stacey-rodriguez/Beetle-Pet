#include "Beetle.hpp"
#include "AsciiArt.hpp"

#include <iostream>
#include <string>
#include <algorithm>
//random support 
#include <cstdlib>
#include <ctime>


const int EGG_TO_L1 = 30;
const int L1_TO_L2 = 60;
const int L2_TO_L3 = 100;
const int L3_TO_PUPA = 150;
const int PUPA_TO_ADULT = 200;

const int MAX_STRESS = 100;
const int MAX_HEALTH = 100;


std::string stageToString(LifeStage stage);
//constructor initizaltion list 
Beetle::Beetle(BeetleSpecies species)
    : species (species),
      stage(LifeStage::Egg),
      health(100), 
      growth(0), 
      stress(0),
      hasMold(false),
      hasMites(false),
      color(BeetleColor::Normal) {}

void Beetle::tick() {
    if (stage == LifeStage::Dead)
        return;

    // species rate
    int growthRate = 10;
    int stressRate = 5;

    switch (species) {
        case BeetleSpecies::Flower:
            growthRate = 15;
            stressRate = 2;
            break;
        case BeetleSpecies::Stag:
            growthRate = 10;
            stressRate = 5;
            break;
        case BeetleSpecies::Hercules:
            growthRate = 8;
            stressRate = 8;
            break;
    }

    growth += growthRate;
    stress += stressRate;

    //calm during pupa
    if (stage == LifeStage::Pupa) {
        stress -= 3;
    }

    // rand event not in pupa
    if (stage != LifeStage::Pupa) {
        int eventRoll = std::rand() % 100;

        if (eventRoll < 10 && !hasMold) {
            hasMold = true;
            std::cout << "🍄🍄🍄 Mold has appeared in the enclosure! 🍄🍄🍄\n";
        }
        else if (eventRoll < 15 && !hasMites) {
            hasMites = true;
            std::cout << "🕷️🕷️🕷️ Mites are infesting your beetle! 🕷️🕷️🕷️\n";
        }
    }

    //mold n mite effect
    int moldStress = 5;
    int moldDamage = 2;
    int miteStress = 8;
    int miteDamage = 4;

    // Species resistances
    switch (species) {
        case BeetleSpecies::Flower:
            moldStress -= 2;
            break;
        case BeetleSpecies::Stag:
            miteDamage -= 2;
            break;
        case BeetleSpecies::Hercules:
            moldStress -= 3;
            miteDamage -= 2;
            break;
    }

    if (hasMold) {
        stress += moldStress;
        health -= moldDamage;
    }

    if (hasMites) {
        stress += miteStress;
        health -= miteDamage;
    }

    // stress damage
    if (stress >= MAX_STRESS) {
        health -= 10;
        std::cout << "⚠️ Oh no! Your beetle is overwhelmed by stress!\n";
    }

    // progression
    if (stage == LifeStage::Egg && growth >= EGG_TO_L1) {
        stage = LifeStage::Larva_L1;
        std::cout << "Your egg has hatched into a L1 larva!\n";
        printLarvaL1();
    }
    else if (stage == LifeStage::Larva_L1 && growth >= L1_TO_L2) {
        stage = LifeStage::Larva_L2;
        std::cout << "Your L1 larva molted into a L2 larva!\n";
        printLarvaL2();
    }
    else if (stage == LifeStage::Larva_L2 && growth >= L2_TO_L3) {
        stage = LifeStage::Larva_L3;
        std::cout << "Your L2 larva molted into a L3 larva — The final larval stage!\n";
        printLarvaL3();
    }
    else if (stage == LifeStage::Larva_L3 && growth >= L3_TO_PUPA) {
        stage = LifeStage::Pupa;
        std::cout << "Your larva has pupated. Do not disturb it.\n";
    }
    else if (stage == LifeStage::Pupa && growth >= PUPA_TO_ADULT) {
    stage = LifeStage::Adult;

    //rare color mutation roll- rand
    int roll = std::rand() % 100;

    if (roll < 3) {
        color = BeetleColor::Striped;
    } else if (roll < 6) {
        color = BeetleColor::Duochrome;
    } else if (roll < 10) {
        color = BeetleColor::Iridescent;
    }

    std::cout << "Your beetle has emerged from it's pupa and is now an adult!\n";
    printAdultBeetle();
    printEnding();
}



    // death
    if (health <= 0) {
        stage = LifeStage::Dead;
        std::cout << "💀 Your beetle has died due to poor conditions.\n";
    }

    // clamp
    if (stress < 0) stress = 0;
    if (stress > MAX_STRESS) stress = MAX_STRESS;
    if (health < 0) health = 0;
    if (health > MAX_HEALTH) health = MAX_HEALTH;

}


void Beetle::printStatus() const {
    int stressLevel = std::min((stress + 5) / 10, 10);
//incase it goes over 100

    std::cout << "Health: " << health 
              << " | Growth: " << growth 
              << " | Stress: " << stress 
              << " | Stage: " << stageToString(stage) << "\n";

    std::cout << "Stress: [";
    for (int i = 0; i < stressLevel; i++) std::cout << "#";
    for (int i = stressLevel; i < 10; i++) std::cout << "-";
    std::cout << "]\n";
    if (stage == LifeStage::Larva_L1)
    std::cout << "The larva is so small and cute.\n";
    if (hasMold)  std::cout << "⚠️ Mold present\n";
    if (hasMites) std::cout << "⚠️ Mites present\n";
    std::cout << "Species: ";
    switch (species) {
        case BeetleSpecies::Flower:   std::cout << "Flower Beetle"; break;
        case BeetleSpecies::Stag:     std::cout << "Stag Beetle"; break;
        case BeetleSpecies::Hercules: std::cout << "Hercules Beetle"; break;
    if (stage == LifeStage::Adult)
    std::cout << "The beetle's life cycle is complete. Now it eagerly looks forward to some beetle Jelly.\n";

}
std::cout << "\n";


}
void Beetle::cleanMold() {
    if (hasMold) {
        hasMold = false;
        stress -= 10;
        std::cout << "You removed the mold.\n";
    } else {
        std::cout << "No mold to clean.\n";
    }
}

void Beetle::treatMites() {
    if (hasMites) {
        hasMites = false;
        stress -= 15;
        std::cout << "You removed the mites.\n";
    } else {
        std::cout << "No mites to treat.\n";
    }
}

bool Beetle::moldPresent() const { return hasMold; }
bool Beetle::mitesPresent() const { return hasMites; }




bool Beetle::isAdult() const {
    return stage == LifeStage::Adult;
}

bool Beetle::isDead() const {
    return stage == LifeStage::Dead || health <= 0;
}

void Beetle::printEnding() const {
    if (color != BeetleColor::Normal) {
    std::cout << "✨ RARE MUTATION DISCOVERED ✨\n";

    switch (color) {
        case BeetleColor::Striped:
            std::cout << "The beetle is Striped! It is black and green and extremely rare!\n";
            break;
        case BeetleColor::Duochrome:
            std::cout << "The beetle is Duochrome! It shimmers between green and purple!\n";
            break;
        case BeetleColor::Iridescent:
            std::cout << "The beetle displays intense iridescence, shifting colors as it moves!\n";
            break;
        default:
            break;
    }
    std::cout << "\n";
}

    std::cout << "You successfully raised a Beetle!\n";

    switch (species) {
        case BeetleSpecies::Flower:
            std::cout <<
            "Your Flower Beetle emerges. It is beautifully colored.\n"
            "Its mandibles hidden, tucked under it's head.\n"
            "It flies for its first time using it's colorful wings.\n"
            "A complete Metamorphosis.\n";
            break;

        case BeetleSpecies::Stag:
            std::cout <<
            "Your Stag Beetle emerges. It has powerful massive mandibles,\n"
            "ready for combat.\n"
            "It buzzes as it takes its first brief flight.\n"
            "A complete Metamorphosis.\n";
            break;

        case BeetleSpecies::Hercules:
            std::cout <<
            "Your Hercules Beetle emerges. A massive horn stands on its head and thorax.\n"
            "It possesses great strength, able to life more than its weight. \n"
            "A complete Metamorphosis.\n";
            break;
    }

}


std:: string stageToString(LifeStage stage){
    switch(stage){
        case LifeStage::Egg: return "Egg";
        case LifeStage::Larva_L1: return "Larva(L1)";
        case LifeStage::Larva_L2: return "Larva(L2)";
        case LifeStage::Larva_L3: return "Larva(L3)";
        case LifeStage::Pupa: return "Pupa";
        case LifeStage::Adult: return "Adult";
        case LifeStage::Dead: return "Dead";
        default: return "Unknown";

    }
}

