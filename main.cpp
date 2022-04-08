#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Board.h"

using namespace std;

int main() {

    vector<vector<int>> a;

    ifstream in("test.txt");
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
    board.Exclude();
    board.Print();

    return 0;
}
