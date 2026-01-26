#ifndef BEETLE_HPP_
#define BEETLE_HPP_

#include "LifeStage.hpp"

enum class BeetleColor {
    Normal,
    Striped,
    Duochrome,
    Iridescent
};

enum class BeetleSpecies {
    Flower,
    Stag,
    Hercules
};

class Beetle{
    private:
        BeetleSpecies species;
        BeetleColor color;
        LifeStage stage;
        int health;
        int growth;
        int stress; 
        bool hasMold;
        bool hasMites;
    public:
        Beetle(BeetleSpecies species);

        void tick();
        void printStatus () const;

        bool isAdult() const;
        bool isDead() const;
        LifeStage getStage() const;

        void cleanMold();
        void treatMites();

        bool moldPresent() const;
        bool mitesPresent() const;

        void printEnding() const; 
};



#endif