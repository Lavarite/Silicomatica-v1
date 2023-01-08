//
// Created by avary on 10/8/2022.
//

#ifndef TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_CRAFTINGRECIPE_H
#define TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_CRAFTINGRECIPE_H


using namespace std;

class CraftingRecipe {
public:
    vector<vector<int>> in;
    vector<int> out;

    bool isShapeless = false;

    void create(vector<vector<int>> in, vector<int> out, bool isShapeless) {
        this->in = in;
        this->out = out;
        this->isShapeless = isShapeless;
    }

    bool complete(vector<vector<int>> n, int size) {
        if (isShapeless) {
            bool complete = true;
            for (int i = 0; i < size - n.size(); i++) {
                for (int j = 0; j < size - n.size(); j++) {
                    complete = true;
                    for (int k = 0; k < n.size(); k++) {
                        for (int l = 0; l < n.size(); l++) {
                            if (in[k][l] != n[k + i][l + j]) complete = false;
                        }
                    }
                    if (complete) return true;
                }
            }
            return false;
        } else {
            for (int i = 0; i < in.size(); i++) {
                for (int j = 0; j < in[i].size(); j++) {
                    if (in[i][j] != n[i][j]) {
                        return false;
                    }
                }
            }
        }
    }
};

#endif //TOO_HOT_OUTSIDE_FOR_A_BIT_TOO_LONG_CRAFTINGRECIPE_H
