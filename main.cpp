#include <bits/stdc++.h>

using namespace std;

#define sep ' '
#define endl '\n'
#define tab '\t'
typedef vector<pair<string,string>> VPSS;
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
    virtual void set_username(string user){username = user;}
    virtual void set_password(string pass){password = pass;}
    virtual void set_mode(string _mode){mode = _mode;}
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
class User: public Client{
public:
    User();
};
User::User():Client(){
    mode = USER;
}
class Artist: public Client{
public:
    Artist();
};
class Music{
public:
    Music(int _id, string _name, Client* _artist);
    int get_id(){return id;}
    string get_name(){return name;}
    Client* get_artist(){return artist;}
    int get_year(){return year;}
    string get_album(){return album;}
    string get_tags(){return tags;}
    string get_duration(){return duration;}


private:
    int id;
    string name;
    Client* artist;
    int year;
    string album;
    string tags;
    string duration;
};
Music::Music(int _id, string _name, Client* _artist){
    id = _id;
    name = _name;
    artist = _artist;
    year = 0;
    album = "baba";
    tags = "ff";
    duration = "5:15";
}
Artist::Artist():Client(){
    mode = ARTIST;
}
VPSS get_arg(int n){
    VPSS content;
    for (int i=0;i<n;i++){
        string fir,sec,tmp=" ";
        cin>>fir;

        while(tmp[tmp.size()-1]!='>'){
            cin>>tmp;
            sec+=(" "+tmp);
        }
        sec = sec.substr(2,sec.length()-3);
        content.push_back(make_pair(fir,sec));
    }
    return content;
}
Client* find_cli(string username , vector<Client*> clients){
    for (int j=0;j<clients.size();j++){
        if(clients[j]->get_username() == username) {
            return clients[j];
        }
    }
    return NULL;
}
Client* check_signup_exeption(Client* login_user, vector<Client*> clients, VPSS arg){
    Client* new_cli = new Client();
    for(int i=0;i<arg.size();i++){
        if(arg[i].first == "username"){
            for(int j=0;j<clients.size();j++){
                if(clients[i]->get_username() == arg[i].second) throw string("invalid");
            }
            new_cli->set_username(arg[i].second);
        }
        if(arg[i].first == "mode" && (arg[i].second != "artist" && arg[i].second != "user")) throw string("invalid");
        if(arg[i].first == "mode"){new_cli->set_mode(arg[i].second);}
        if(arg[i].first == "password"){new_cli->set_password(arg[i].second);}
    }
    if (login_user!=NULL) throw string("Permission");
    return new_cli;
}
Client* check_login_exeption(Client* login_user, vector<Client*> clients, VPSS arg){
    Client* try_to_login =NULL;
    for (int i=0;i<arg.size();i++){
        if(arg[i].first == "username"){

            try_to_login = find_cli(arg[i].second,clients);
        }
    }
    if (try_to_login == NULL) throw string("Not exist");
    for (int i=0;i<arg.size();i++){
        if(arg[i].first == "password"){
            if(arg[i].second != try_to_login->get_password()) throw string("Permission");
        }
    }
    if (login_user!=NULL)throw string("Permission");
    return try_to_login;
}
Client* check_logout_exeption(Client* login_user){
    if(login_user ==NULL)throw string("Permission");
    return NULL;
}
void try_catch_result(string err){
    if(err == "invalid"){cout<<BAD_REQUEST<<endl;}
    if(err == "Permission"){cout<<PERMISSION<<endl;}
    if(err == "Not exist"){cout<<NOT_FOUND<<endl;}
    if(err == "empty"){cout<<EMPTY<<endl;}
}
void check_musics_exeption(Client* login_user,vector<Music*> musics){
    if(login_user == NULL) throw string ("Permission");
    if(musics.size() == 0) throw string ("empty");
    cout<<"ID, Name, Artist"<<endl;
    for(int i=0;i<musics.size();i++){
        cout<<musics[i]->get_id()<<", "<<musics[i]->get_name()<<", "<<(musics[i]->get_artist())->get_username()<<endl;
    }
}
void check_music_exeption(Client* login_user, vector<Music*> musics,int id){
    if(login_user == NULL) throw string ("Permission");
    for(int i = 0 ;i<musics.size();i++){
        if(musics[i]->get_id()==id){
            cout<<"ID, Name, Artist, Year, Album, Tags, Duration"<<endl;
            cout<<musics[i]->get_id()<<", "<<musics[i]->get_name()<<", "<<(musics[i]->get_artist())->get_username()<<", "<<musics[i]->get_year()<<", "<<musics[i]->get_album()<<", "<<musics[i]->get_tags()<<", "<<musics[i]->get_duration()<<endl;
        }
    }
}
class Sputify{
public:
    Sputify();
    void commands();
private:
    Client* login_user;
    vector<Client*> clients;
    vector<Music*> musics;
    int musics_num;
};
Sputify::Sputify(){
    login_user = NULL;
}
void Sputify::commands(){
    string command;

    while(cin>>command){
        if (command == COMMANDS[1]){
            string task,delimiter;
            cin>>task>>delimiter;
            if (task == "signup"){
                VPSS arg = get_arg(3);
                try{
                    clients.push_back(check_signup_exeption(login_user,clients,arg));
                    login_user = clients[clients.size()-1];
                    musics.push_back(new Music(1, "babaii", login_user));
                    cout<<OK<<endl;
                }
                catch (string err){
                    try_catch_result(err);
                }
            }
            if (task == "login"){
                VPSS arg = get_arg(2);
                try{
                    login_user = check_login_exeption(login_user,clients,arg);
                    cout<<OK<<endl;
                }
                catch(string err){
                    try_catch_result(err);
                }
            }
            if (task == "logout"){
                try{
                    login_user = check_logout_exeption(login_user);
                    cout<<OK<<endl;
                }
                catch(string err){
                    try_catch_result(err);
                }
            }
        }
        if (command == COMMANDS[0]){
            string task,delimiter;
            cin>>task>>delimiter;
            if (task == "musics" && delimiter =="?"){
                string arg;
                getline (cin,arg);
                try{
                    if (arg == ""){
                        check_musics_exeption(login_user, musics);
                    }
                    else{
                        arg = arg.substr(arg.find("<")+1,arg.find(">")-arg.find("<")-1);
                        check_music_exeption(login_user,musics, stoi(arg));
                    }
                }
                catch(string err){
                    try_catch_result(err);
                }
            }
            else{
                try_catch_result("invalid");
            }
        }
    }
}
int main(){
    Sputify sputify;
    sputify.commands();
    return 0;
}
