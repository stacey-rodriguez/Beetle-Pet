#include "Beetle.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(std::time(nullptr));
//prevents same events
    std::cout << "Choose your beetle species :\n";
    std::cout << "1. Flower Beetle (fast growth, low stress)\n";
    std::cout << "2. Stag Beetle (balanced)\n";
    std::cout << "3. Hercules Beetle (slow growth, high stress)\n";
    std::cout << "-> ";

    int choice;
    std::cin >> choice;

    BeetleSpecies selectedSpecies;

    if (choice == 1) selectedSpecies = BeetleSpecies::Flower;
    else if (choice == 2) selectedSpecies = BeetleSpecies::Stag;
    else selectedSpecies = BeetleSpecies::Hercules;

    Beetle beetle(selectedSpecies);

    char input;
int day = 1;

while (true) {
    std::cout << "\nDay " << day << "\n";
    beetle.tick();
    beetle.printStatus();

if (beetle.isAdult()) {
    beetle.printEnding();
    break;
}

if (beetle.isDead()) {
    std::cout << "\n Your beetle has died. I'm sorry.\n";
    break;
}


    std::cout << "Press ENTER to continue watching it grow ...";
    std::cin.ignore();
    std::cin.get();

    day++;

    char choice;
std::cout << "\nActions:\n";
if (beetle.moldPresent())  std::cout << " (C) Clean mold\n";
if (beetle.mitesPresent()) std::cout << " (M) Treat mites\n";
std::cout << " (P) Peer into container \n";
std::cout << "Choice: ";

std::cin >> choice;

switch (choice) {
    case 'C':
    case 'c':
        beetle.cleanMold();
        break;
    case 'M':
    case 'm':
        beetle.treatMites();
        break;
    default:
        std::cout << "You wait ...\n";
}

}


    return 0;
}
