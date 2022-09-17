#ifndef TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_WORLD_H
#define TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_WORLD_H

#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "Block.h"
#include "PerlinNoise.h"

using namespace std;

class World {
public:
    int size = 100;
    int seed = 0;

    int getSeed() { return seed; };

    int getSize() { return size; };

    void setSize(int size) { this->size = size; };

    void setSeed(int seed) { this->seed = seed; };


    vector<Player> players;
    vector<vector<Block>> map = vector<vector<Block>>(size, vector<Block>(size));


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
            Item drop;
            drop.setName("Wood");
            drop.setQuantity(1);
            drop.setType("placeable");
            drop.setSymbol("|");
            block.setDrop(drop);
        } else if (b == '#') {
            block.setName("Stone");
            block.setType("stone");
            block.setTool("Pickaxe");
            block.setTransparent(false);
            block.setColor(8);
            Item drop;
            drop.setName("Stone");
            drop.setQuantity(1);
            drop.setType("placeable");
            drop.setSymbol("#");
            block.setDrop(drop);
        } else if (b == '*') {
            block.setName("Sand");
            block.setType("sand");
            block.setTool("Shovel");
            block.setTransparent(true);
            block.setColor(14);
            Item drop;
            drop.setName("Sand");
            drop.setQuantity(1);
            drop.setType("placeable");
            drop.setSymbol("*");
            block.setDrop(drop);
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
        PerlinNoise pn(Seed);
        for (int i = 0; i < size; ++i) {     // y
            for (int j = 0; j < size; ++j) {  // x
                double x = (double) j / ((double) size);
                double y = (double) i / ((double) size);
                double n = pn.noise(10 * x, 10 * y, 0.8);
                if (n < 0.2) {
                    this->setBlock(i, j, ',');
                } else if (n >= 0.2 && n < 0.32) {
                    this->setBlock(i, j, '*');
                } else if (n >= 0.32 && n < 0.4) {
                    this->setBlock(i, j, '|');
                } else if (n >= 0.4 && n < 0.65) {
                    this->setBlock(i, j, '-');
                } else {
                    this->setBlock(i, j, '#');
                }
            }
        }
    }
};

#endif
