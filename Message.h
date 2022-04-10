//
// Created by 16000 on 2022/4/10.
//

#ifndef SUDOKU_MESSAGE_H
#define SUDOKU_MESSAGE_H

#include <vector>
#include <string>
using std::vector;
using std::string;

class Message {
public:
    vector<int> message;
    string type;

    Message(const vector<int> &message, const string &type);

};


#endif //SUDOKU_MESSAGE_H
