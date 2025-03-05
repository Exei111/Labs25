#include "planets.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>

namespace planets {

    Planet::Planet(const char* name, int diameter, int life, int satellites) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->diameter = diameter;
        this->life = life;
        this->satellites = satellites;
    }

    Planet::Planet() {
        this->name = new char[5];
        strcpy(this->name, "name");
        this->diameter = 0;
        this->life = 0;
        this->satellites = 0;
    }
    Planet::Planet(const Planet& other) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->diameter = other.diameter;
        this->life = other.life;
        this->satellites = other.satellites;
    }

    Planet& Planet::operator=(const Planet& other) {
    if (this == &other) return *this;

    delete[] name;

    this->name = new char[strlen(other.name) + 1];
    strcpy(this->name, other.name);
    this->diameter = other.diameter;
    this->life = other.life;
    this->satellites = other.satellites;

    return *this;
}


    Planet::~Planet() {
        delete[] name;
    }
    
    bool Planet::operator==(const Planet& other) {
        return name == other.name;
    }

    bool Planet::operator>(const Planet& other) {
        return diameter > other.diameter;
    }

    std::ostream& operator<<(std::ostream& out, const Planet& other) {
        out << other.name << " " << other.diameter << " " << other.life << " " << other.satellites;
        return out;
    }

    std::ifstream& operator>>(std::ifstream& in, Planet& other) {
        char tempName[100];
        in >> tempName;
        delete[] other.getName();
        other.setName((new char[strlen(tempName) + 1]));
        strcpy(other.getName(), tempName);

        int diameter = 0;
        int life = 0;
        int satellites = 0;

        in >> diameter >> life >> satellites;

        return in;

    }

    
    

    char* Planet::getName() {
        return name;
    }

    int Planet::getDiameter() {
        return diameter;
    }

    int Planet::getLife() {
        return life;
    }

    int Planet::getSatellites() {
        return satellites;
    }

    void Planet::setName(char* name) {
        delete[] this->name;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    void Planet::setDiameter(int diameter) {
        this->diameter = diameter;
    }

    void Planet::setLife(int life) {
        this->life = life;
    }

    void Planet::setSatelites(int satellites) {
        this->satellites = satellites;
    }


    


    int size = 1;
    int index = 0;

    Planet* planet;

    void Planet::loadFromFile(const char* filename) {
        Planet* planets = new Planet[size];

        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "Не удалось открыть файл" << std::endl;
        }
        char line[200];
 
        while (file.getline(line, sizeof(line))) {
            char* separator1 = std::strchr(line, ' ');
            if (separator1 == nullptr) {
                continue;
            }
            *separator1 = '\0';

            char* separator2 = std::strchr(separator1 + 1, ' ');
            if (separator2 == nullptr) {
                continue;
            }
            *separator2 = '\0';

            char* separator3 = std::strchr(separator2 + 1, ' ');
            if (separator3 == nullptr) {
                continue;
            }
            *separator3 = '\0';

            
            const char* name = line;                      
            const char* diameterStr = separator1 + 1;          
            const char* lifeStr = separator2 + 1;           
            const char* satelitesStr = separator3 + 1;

            int diameter = std::stoi(diameterStr);
            int life = std::stoi(lifeStr);
            int satelites = std::stoi(satelitesStr);


            Planet* newPlanets = new Planet[size * 2];
            std::copy(planets, planets + index + 1, newPlanets);
            delete[] planets;
            planets = newPlanets;
        


            planets[index] = Planet(name, diameter, life, satelites);

            size++;
            index++;
        }
        index--;

        planet = planets;
        Planet::sort();
    }

    

    void Planet::sort() {
        for (int i = 0; i < index + 1; i++) {
            bool isSwaped = false;
            for (int j = 0; j < index - i; j++) {
                if (planet[j] > planet[j+1]) {
                    std::swap(planet[j], planet[j+1]);
                }
            }
        }
    }

    void Planet::addToDb(const char* name, int diameter, int life, int satelites) {
        Planet newPlanetObject(name, diameter, life, satelites);
        Planet* newPlanet = new Planet[++size];
        std::copy(planet, planet + index+1, newPlanet);
        delete[] planet;
        newPlanet[index + 1] = newPlanetObject;
        planet = newPlanet;
        index++;
    }

    // test
    void Planet::addToDb(Planet findPlanet) {
        Planet* newPlanet = new Planet[++size];
        std::copy(planet, planet + index+1, newPlanet);
        delete[] planet;
        newPlanet[index + 1] = findPlanet;
        planet = newPlanet;
        index++;
    }

    bool isEqualName(const char* name1, const char* name2) {
        bool isEqual = true;
        if (strlen(name1) != strlen(name2)) {
            return false;
        }

        for (int i = 0; i < strlen(name1); i++) {
            if (name1[i] != name2[i]) {
                return false;
            }
        }
        return true;
    }

    void Planet::removeFromDb(const char* name) {
        int findIndex = getIndexOfPlanet(name);

        Planet* newPlanet = new Planet[--size];

        std::copy(planet, planet + findIndex, newPlanet);
        std::copy(planet + findIndex + 1, planet + index + 1, newPlanet + findIndex);

        delete[] planet;

        planet = newPlanet;
        index--;

    }
    

    void Planet::printDb() {
        for (int i = 0; i < index + 1; i++) {
            std::cout << planet[i].name << " " <<  planet[i].diameter << " " << planet[i].life << " " << planet[i].satellites << std::endl;
        }
    }

    void Planet::saveToFile() {
        std::ofstream out("database.txt");
        if (!out) {
            std::cout << "Не удалось открыть файл" << std::endl;
        }

        for (int i = 0; i < index + 1; i++) {
            out << planet[i] << "\n";
        }


        out.close();

        delete[] planet;
    }

    void Planet::editDb(const char* name, Planet newValue) {
        int findPlanetIndex = getIndexOfPlanet(newValue);
        planet[findPlanetIndex] = newValue;
    }

    int Planet::getIndexOfPlanet(Planet findPlanet) {
        int findPlanetIndex = 0;
        bool isFind = false;
        for (int i = 0; i < index + 1; i++) {
            if (isEqualName(findPlanet.name, planet[i].name)) {
                isFind = true;
                findPlanetIndex = i;
            }
        }

        if (!isFind) {
            std::cout << "В базе данных нет объекта с именем " << findPlanet.name << std::endl;
            return -1;
        }

        return findPlanetIndex;
    }

    int Planet::getIndexOfPlanet(const char* findName) {
        int findPlanetIndex = 0;
        bool isFind = false;
        for (int i = 0; i < index + 1; i++) {
            if (isEqualName(findName, planet[i].name)) {
                isFind = true;
                findPlanetIndex = i;
            }
        }

        if (!isFind) {
            std::cout << "В базе данных нет объекта с именем " << findName << std::endl;
            return -1;
        }

        return findPlanetIndex;
    }

}

