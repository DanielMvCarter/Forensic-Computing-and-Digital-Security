#pragma once

#include<string>
using namespace std;

class MessageClass {
    public:
    void setMessage(string s);
    string getMessage();
    private:
    string message;
};