#include <bits/stdc++.h>

using namespace std;

#define sep ' '
#define endl '\n'
#define tab '\t'

const string OK = "OK";
const string EMPTY = "Empty";
const string NOT_FOUND = "Not Found";
const string BAD_REQUEST = "Bad Request";
const string PERMISSION = "Permission Denied";
const string ARTIST = "Artist";
const string USER = "User";
const vector<string> COMMANDS = {"GET","POST","DELETE","PUT"};

class Client{
public:
    Client();
    virtual string get_username(){return username;}
    virtual string get_password(){return password;}
    virtual string get_mode(){return mode;}
protected:
    string username;
    string password;
    string mode;
};
Client::Client(){
    username = " ";
    password = " ";
    mode = "babaii";
}

int main(){

    return 0;
}
