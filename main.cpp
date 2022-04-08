#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Board.h"

using namespace std;

int main() {

    vector<vector<int>> a;

    ifstream in("test2.txt");
    string line;

    if (in) {
        while (getline(in, line)) {
            int b;
            vector<int> temp;
            stringstream ss(line);
            while (ss >> b) {
                temp.push_back(b);
            }
            a.push_back(temp);
        }
    } else {
        cout << "no such file" << endl;
    }

    Board board(a);
    board.UpdatePossibleNumList();
    board.run();
    return 0;
}
