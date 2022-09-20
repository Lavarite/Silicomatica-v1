#ifndef TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_WORLD_H
#define TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_WORLD_H

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "Player.h"
#include "Block.h"
#include "PerlinNoise.h"

using namespace std;

class World {
public:
    string name = "Unnamed World";


    int size = 100;
    short seed = 0;

    int getSeed() { return seed; };

    int getSize() { return size; };

    void setSize(int size) { this->size = size; };

    void setSeed(int seed) { this->seed = seed; };


    vector<Player> players;
    vector<vector<Block>> map;


    Block getBlock(int x, int y) {
        return map[x][y];
    };

    vector<vector<Block>> getMap() {
        return map;
    };

    void setBlock(int x, int y, char b) {
        Block block;
        if (b == '-') {
            block.setName("Air");
            block.setType("gas");
            block.setTool("None");
            block.setTransparent(true);
            block.setColor(2);
        } else if (b == '|') {
            block.setName("Wood");
            block.setType("wood");
            block.setTool("Axe");
            block.setTransparent(false);
            block.setColor(6);
            block.setDrop(1);
        } else if (b == '#') {
            block.setName("Stone");
            block.setType("stone");
            block.setTool("Pickaxe");
            block.setTransparent(false);
            block.setColor(8);
            block.setDrop(2);
        } else if (b == '*') {
            block.setName("Sand");
            block.setType("sand");
            block.setTool("Shovel");
            block.setTransparent(true);
            block.setColor(14);
            block.setDrop(3);
        } else if (b == ',') {
            block.setName("Water");
            block.setType("liquid");
            block.setTool("None");
            block.setTransparent(true);
            block.setColor(9);
        }
        block.setSymbol(b);
        map[x][y] = block;
    };

    void setMap(vector<string> Map) {
        for (int i = 0; i < Map.size(); i++) {
            for (int j = 0; j < Map[i].length(); j++) {
                setBlock(i, j, Map[i][j]);
            }
        }
    };

    vector<Player> getPlayers() {
        return players;
    };

    Player getPlayer(int num) {
        return players[num];
    };

    void setPlayer(int num, Player player) {
        players[num] = player;
    };

    void removePlayer(string player) {
        players.erase(players.begin() + this->findPlayer(player));
    };

    void addPlayer(Player player) {
        players.push_back(player);
    };

    int findPlayer(string name) {
        for (int i = 0; i < players.size(); i++) {
            if (players[i].getName() == name) {
                return i;
            }
        }
        return -1;
    };

    void updatePlayer(Player player) {
        players[this->findPlayer(player.getName())] = player;
    }

    void printMap(Player player) {
        static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD topLeft = {0, 0};
        SetConsoleCursorPosition(hOut, topLeft);
        cout << "Coordinates: " << player.getX() << ", " << player.getY() << endl;
        int x, y;
        x = player.getX();
        y = player.getY();
        for (int i = y - 15; i < y + 15; i++) {
            for (int j = x - 15; j < x + 15; j++) {
                if (i < 0 || j < 0 || i >= size || j >= size) {
                    cout << "  ";
                } else {
                    for (int k = 0; k < players.size(); k++) {
                        if (players[k].getX() == j && players[k].getY() == i) {
                            SetConsoleTextAttribute(hOut, player.getColor());
                            cout << players[k].getSymbol() << " ";
                            SetConsoleTextAttribute(hOut, 7);
                        } else {
                            SetConsoleTextAttribute(hOut, map[i][j].getColor());
                            cout << map[i][j].getSymbol() << " ";
                            SetConsoleTextAttribute(hOut, 7);
                        }
                    }
                }
            }
            cout << endl;
        }
    }

    void generate(unsigned int Seed) {
        map = vector<vector<Block>>(size, vector<Block>(size));
        PerlinNoise pn(Seed);
        for (int i = 0; i < size; ++i) {     // y
            for (int j = 0; j < size; ++j) {  // x
                //double x = (double) j / ((double) size);
                //double y = (double) i / ((double) size);
                double n = pn.noise(((double) j / 10), ((double) i / 10), 0.8);
                if (n < 0.2) {
                    this->setBlock(i, j, ',');
                } else if (n >= 0.2 && n < 0.3) {
                    this->setBlock(i, j, '|');
                } else if (n >= 0.3 && n < 0.37) {
                    this->setBlock(i, j, '*');
                } else if (n >= 0.37 && n < 0.68) {
                    this->setBlock(i, j, '-');
                } else {
                    this->setBlock(i, j, '#');
                }
            }
        }
    }

    void saveFile() {
        fstream file;
        file.open("../saves/" + name + ".txt", ios::out);
        if (file.is_open()) {
            file << name << endl;
            file << seed << endl;
            file << size << endl;
            file << endl;
            file << "Blocks:" << endl;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    file << map[i][j].name << " ";
                }
                file << endl;
                for (int j = 0; j < size; j++) {
                    file << map[i][j].type << " ";
                }
                file << endl;
                for (int j = 0; j < size; j++) {
                    file << map[i][j].color << " ";
                }
                file << endl;
                for (int j = 0; j < size; j++) {
                    file << map[i][j].transparent << " ";
                }
                file << endl;
                for (int j = 0; j < size; j++) {
                    file << map[i][j].symbol << " ";
                }
                file << endl;
                for (int j = 0; j < size; j++) {
                    file << map[i][j].tool << " ";
                }
                file << endl;
                for (int j = 0; j < size; j++) {
                    file << map[i][j].interactable << " ";
                }
                file << endl;
                for (int j = 0; j < size; j++) {
                    file << map[i][j].drop << " ";
                }
            }
            file << endl;
            file << "Players:" << endl;
            for (int playerN = 0; playerN < players.size(); playerN++) {
                file << players[playerN].name << endl;
                file << players[playerN].x << endl;
                file << players[playerN].y << endl;
                file << players[playerN].color << endl;
                file << players[playerN].symbol << endl;
                file << players[playerN].selectedSlot << endl;
                /*file << "Inventory:" << endl;
                for (int itemsN = 0; itemsN < players[playerN].inventory.size; itemsN++) {
                    file << players[playerN].inventory.items[itemsN].name << endl;
                    file << players[playerN].inventory.items[itemsN].quantity << endl;
                    file << players[playerN].inventory.items[itemsN].type << endl;
                    file << players[playerN].inventory.items[itemsN].symbol << endl;
                    file << endl;
                }*/

                file << endl;
            }
        }
    }

    void loadFile(string dir) {
        fstream file;
        file.open(dir, ios::in);
        if (file.is_open()) {
            string line;
            getline(file, line);
            name = line;
            getline(file, line);
            seed = stoi(line);
            getline(file, line);
            size = stoi(line);
            getline(file, line);
            getline(file, line);
            map = vector<vector<Block>>(size, vector<Block>(size));
            char *info;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    file >> map[i][j].name;
                }
                for (int j = 0; j < size; j++) {
                    file >> map[i][j].type;
                }
                for (int j = 0; j < size; j++) {
                    file >> map[i][j].color;
                }
                for (int j = 0; j < size; j++) {
                    file >> map[i][j].transparent;
                }
                for (int j = 0; j < size; j++) {
                    file >> map[i][j].symbol;
                }
                for (int j = 0; j < size; j++) {
                    file >> map[i][j].tool;
                }
                for (int j = 0; j < size; j++) {
                    file >> map[i][j].interactable;
                }
                for (int j = 0; j < size; j++) {
                    file >> map[i][j].drop;
                }
            }
            getline(file, line);
            getline(file, line);
        }
    }
};

#endif
