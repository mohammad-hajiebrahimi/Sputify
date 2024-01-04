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
    virtual int get_num(){return -1;}
    virtual void add_num(){}
    virtual void del_num(){}
    virtual int get_id(){return id;}
    virtual void set_id(int _id){id = _id;}

protected:
    int id;
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
    int get_num(){return playlist_num;}
    void add_num(){playlist_num++;}

protected:
    int playlist_num;

};
User::User():Client(){
    mode = USER;
    playlist_num = 0;
}
class Artist: public Client{
public:
    Artist();
    int get_num(){return songs_num;}
    void add_num(){songs_num++;}
    void del_num(){songs_num--;}
protected:
    int songs_num;
    vector<string> songs;
};
Artist::Artist():Client(){
    mode = ARTIST;
    songs_num = 0;
}
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
    void set_name(string _name){name = _name;}
    void set_year(int _year){year = _year;}
    void set_album(string _album){album = _album;}
    void set_tags(string _tags){tags = _tags;}
    void set_path(string _path){path = _path;}
    void set_duration(string _duration){duration = _duration;}


private:
    int id;
    string name;
    Client* artist;
    int year;
    string album;
    string tags;
    string duration;
    string path;
};
Music::Music(int _id, string _name, Client* _artist){
    id = _id;
    name = _name;
    artist = _artist;
}
class Playlist{
public:
    Playlist(string _name, Client* _owner){
        name = _name;
        owner = _owner;
    }
    string get_name(){return name;}
    Client* get_owner(){return owner;}
    vector<int> get_songs(){return songs;}
    void set_songs(vector<int> _songs){songs = _songs;}
    void add_song(int id){songs.push_back(id);}
private:
    string name;
    Client* owner;
    vector<int> songs;
};
VPSS get_arg(int n){
    VPSS content;/*
    for (int i=0;i<n;i++){
        string fir,sec,tmp=" ";
        cin>>fir;

        while(tmp[tmp.size()-1]!='>'){
            cin>>tmp;
            sec+=(" "+tmp);
        }
        sec = sec.substr(2,sec.length()-3);
        content.push_back(make_pair(fir,sec));
    }*/
    string line;
    getline(cin, line);
    line =line;
    vector < string > row;
    stringstream str(line);
    string word;
    while (getline(str, word, '>')) {
        row.clear();
        word+=">";
        string text;
        stringstream strr(word);
        getline(strr, text, ' ');
        while (getline(strr, text, ' ')){
            row.push_back(text);
        }
        string fir,sec="";
        for(int i=1;i<row.size();i++){
            sec+=(row[i]+" ");
        }
        sec = sec.substr(1,sec.length()-3);
        content.push_back(make_pair(row[0],sec));
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
    string mode;
    Client* new_cli = NULL;
    for(int i=0;i<arg.size();i++){
        if(arg[i].first == "mode"){
            mode = arg[i].second;
        }
    }
    if (mode == "artist") new_cli = new Artist();
    else{new_cli = new User();}
    for(int i=0;i<arg.size();i++){
        if(arg[i].first == "username"){
            for(int j=0;j<clients.size();j++){
                if(clients[i]->get_username() == arg[i].second) throw string("invalid");
            }
            new_cli->set_username(arg[i].second);
        }
        if(arg[i].first == "mode" && (arg[i].second != "artist" && arg[i].second != "user")) throw string("invalid");
        if(arg[i].first == "mode"){
            new_cli->set_mode(arg[i].second);
        }
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
    int flag=0;
    for(int i = 0 ;i<musics.size();i++){
        if(musics[i]->get_id()==id){
            flag = 1;
            cout<<"ID, Name, Artist, Year, Album, Tags, Duration"<<endl;
            cout<<musics[i]->get_id()<<", "<<musics[i]->get_name()<<", "<<(musics[i]->get_artist())->get_username()<<", "<<musics[i]->get_year()<<", "<<musics[i]->get_album()<<", "<<musics[i]->get_tags()<<", "<<musics[i]->get_duration()<<endl;
        }
    }
    if(! flag) throw string("Not exist");
}
void check_users_exeption(Client* login_user,vector<Client*> clients){
    if(login_user == NULL) throw string ("Permission");
    if(clients.size()== 0) throw string ("empty");
    cout<<"ID, Mode, Username, Playlists_number/Songs_number"<<endl;
    for(int i=0; i<clients.size();i++){
        if (clients[i]->get_mode()==ARTIST){
            cout<<i+1<<", "<<clients[i]->get_mode()<<", "<<clients[i]->get_username()<<", "<<clients[i]->get_num()<<endl;
        }
        else{
            cout<<i+1<<", "<<clients[i]->get_mode()<<", "<<clients[i]->get_username()<<", "<<clients[i]->get_num()<<endl;
        }
    }
}
void check_user_exeptoin(Client* login_user,vector<Client*> clients, int id,vector<Music*> musics, vector<Playlist*> playlists){
    if(login_user == NULL) throw string ("Permission");
    if(clients.size()== 0) throw string ("empty");
    if(clients.size()<id) throw string("Not exist");
    cout<<"ID: "<<id<<endl;
    cout<<"Mode: "<<clients[id-1]->get_mode()<<endl;
    cout<<"Username: "<<clients[id-1]->get_username()<<endl;
    if(clients[id-1]->get_mode() == "artist"){
        cout<<"Songs: ";
        for (int i=0;i<musics.size();i++){
            if ( (musics[i]->get_artist())->get_username() == clients[id-1]->get_username()){
                cout<<musics[i]->get_name();
            }
            if(i!=musics.size()-1)cout<<", ";
        }
        cout<<endl;
    }
    if(clients[id-1]->get_mode() == "user"){
        cout<<"Playlists: ";
        for(int i=0;i<playlists.size();i++){
            if((playlists[i]->get_owner())->get_id() == id)cout<<playlists[i]->get_name();
            if(i!=playlists.size()-1)cout<<", ";
        }
        cout<<endl;

    }

}
vector<Music*> check_share_exeption(Client* login_user,vector<Music*> musics,int musics_num){
    musics_num++;
    if(login_user->get_mode()!="artist")throw string("Permission");
    Music* new_music = new Music(musics_num, "",login_user);
    VPSS arg = get_arg(6);
    for (int i=0;i<arg.size();i++){
        if (arg[i].first == "title")new_music->set_name(arg[i].second);
        else if(arg[i].first == "path")new_music->set_path(arg[i].second);
        else if(arg[i].first == "year")new_music->set_year(stoi(arg[i].second));
        else if(arg[i].first == "tags")new_music->set_tags(arg[i].second);
        else if(arg[i].first == "duration") new_music->set_duration(arg[i].second);
        else if(arg[i].first == "album")new_music->set_album(arg[i].second);
        else{
            throw string ("invalid");
        }
    }
    login_user->add_num();
    musics.push_back(new_music);
    return musics;
}
void check_registerd_musics_exeption(Client* login_user,vector<Music*> musics){
    if(login_user->get_mode()!="artist")throw string("Permission");
    vector<Music*> artist_musics;
    for(int i=0;i<musics.size();i++){
        if(login_user->get_username() == (musics[i]->get_artist())->get_username()){
            artist_musics.push_back(musics[i]);
        }
    }
    if (artist_musics.size()== 0) throw("empty");
    cout<<"ID, Name, Year, Album, Tags, Duration"<<endl;
    for(int i=0;i<artist_musics.size();i++){
        cout<<artist_musics[i]->get_id()<<", "<<artist_musics[i]->get_name()<<", "<<artist_musics[i]->get_year()<<", "<<artist_musics[i]->get_album()<<", "<<artist_musics[i]->get_tags()<<", "<<artist_musics[i]->get_duration()<<endl;
    }
}
vector<Playlist*> check_add_playlist_exeption(Client* login_user, vector<Playlist*> playlists){
    if(login_user->get_mode()!="user")throw string("Permission");
    VPSS arg = get_arg(1);
    for (int i = 0 ;i<playlists.size();i++){
        if(playlists[i]->get_name() == arg[0].second && (playlists[i]->get_owner())->get_username() == login_user->get_username() )throw string("invalid");
    }
    playlists.push_back(new Playlist(arg[0].second, login_user));
    login_user->add_num();
    return playlists;
}
vector<Playlist*> check_add_music_to_playlist_exeptoin(Client* login_user, vector<Playlist*> playlists,vector<Music*> musics){
    if(login_user->get_mode()!="user")throw string("Permission");
    VPSS arg = get_arg(2);
    int id = -1;
    string name;
    for(int i=0;i<arg.size();i++){
        if(arg[i].first == "id"){
            int flag = 0;
            for(int j=0;j<musics.size();j++){
                if (musics[j]->get_id() == stoi(arg[i].second)){
                    flag = 1;
                    id = stoi(arg[i].second);
                }
            }
            if(!flag) throw string("Not exist");
        }
        else if(arg[i].first == "name"){
            int flag = 0;
            for(int j=0;j<playlists.size();j++){
                if (playlists[j]->get_name() == arg[i].second && (playlists[j]->get_owner())->get_username() == login_user->get_username()){
                    flag =1;
                    name = arg[i].second;
                }
            }
            if (!flag)throw string("Not exist");
        }
        else{
            throw string("invalid");
        }
    }
    for(int j=0;j<playlists.size();j++){
        if (playlists[j]->get_name() == name && (playlists[j]->get_owner())->get_username() == login_user->get_username()){
            playlists[j]->add_song(id);
        }
    }
    return playlists;

}
vector<Music*> check_delete_music_exeption(Client* login_user, vector<Music*> musics, int id){
    int flag = 0;
    for (int i=0;i<musics.size();i++){
        if(musics[i]->get_id() == id)flag = 1;
    }
    if(!flag) throw string("Not exist");
    flag = 0;
    for (int i=0;i<musics.size();i++){
        if(musics[i]->get_id() == id && (musics[i]->get_artist())->get_username() == login_user->get_username()){
            flag = 1;
            login_user->del_num();
            musics.erase(musics.begin()+i);
            return musics;
        }
    }
    if(!flag) throw string("Permission");
    return musics;
}
vector<Playlist*> check_delete_playlist_exeption( vector<Playlist*> playlists,int id){
    for(int i = 0;i<playlists.size();i++){
        vector<int> songs = playlists[i]->get_songs();
        for(int j=0;j<songs.size();j++){
            if(songs[j] == id){
                songs.erase(songs.begin()+j);
                break;
            }
        }
        playlists[i]->set_songs(songs);
    }
    return playlists;
}
int get_seconds_from_string(const string& timeString) {
    int hours, minutes, seconds;
    char delimiter;
    stringstream ss(timeString);
    ss >> hours;
    ss >> delimiter;
    ss >> minutes;
    ss >> delimiter;
    ss >> seconds;
    return (hours * 3600) + (minutes * 60) + seconds;
}
string get_string_from_seconds(int seconds) {
    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;
    int secs = (seconds % 3600) % 60;
    stringstream ss;
    ss << setw(2) << setfill('0') << hours << ":" << setw(2) << setfill('0') << minutes << ":" << setw(2) << setfill('0') << secs;
    return ss.str();
}
string get_duration_of_playlist(vector<int>songs, vector<Music*> musics){
    int dur=0;
    for(int i=0;i<songs.size();i++){
        for(int j=0;j<musics.size();j++){
            if(songs[i]==musics[j]->get_id()){
                dur+=get_seconds_from_string(musics[j]->get_duration());
            }
        }
    }
    return get_string_from_seconds(dur);
}
bool compare_two_vector(vector<string> a, vector<string>b){
    return a[0]<b[0];
}
void check_show_playlist_exeption(Client* login_user, vector<Playlist*> playlists,vector<Music*> musics,vector<Client*> clients,int id){
    if(clients.size()<id)throw string("Not exist");
    if(clients[id-1]->get_mode()=="artist")throw string("invalid");
    if(login_user->get_mode()=="artist")throw string("Permission");
    vector<vector<string>> lists;
    for(int i=0;i<playlists.size();i++){
        vector<string> list;
        if((playlists[i]->get_owner())->get_id() == id){
            list.push_back(playlists[i]->get_name());
            list.push_back(to_string((playlists[i]->get_songs()).size()));
            list.push_back(get_duration_of_playlist(playlists[i]->get_songs(), musics));
            lists.push_back(list);
        }
    }
    sort(lists.begin(),lists.end(),compare_two_vector);
    cout<<"Playlist_ID, Playlist_name, Songs_number, Duration"<<endl;
    for(int i=0;i<lists.size();i++){
        cout<<i+1<<", "<<lists[i][0]<<", "<<lists[i][1]<<", "<<lists[i][2]<<endl;
    }
}
class Sputify{
public:
    Sputify();
    void signup_command();
    void login_command();
    void logout_command();
    void show_musics_command();
    void show_users_command();
    void share_music_command();
    void show_registered_music_command();
    void add_playlist_command();
    void add_song_to_playlist_command();
    void delete_song_command();
    void commands();
private:
    Client* login_user;
    vector<Client*> clients;
    vector<Music*> musics;
    vector<Playlist*> playlists;
    int musics_num;
};
Sputify::Sputify(){
    login_user = NULL;
    musics_num = 0;
}
void Sputify::signup_command(){
    VPSS arg = get_arg(3);
    try{
        clients.push_back(check_signup_exeption(login_user,clients,arg));
        login_user = clients[clients.size()-1];
        login_user->set_id(clients.size());
        cout<<OK<<endl;
    }
    catch (string err){
        try_catch_result(err);
    }
}
void Sputify::login_command(){
    VPSS arg = get_arg(2);
    try{
        login_user = check_login_exeption(login_user,clients,arg);
        cout<<OK<<endl;
    }
    catch(string err){
        try_catch_result(err);
    }
}
void Sputify::logout_command(){
    try{
        login_user = check_logout_exeption(login_user);
        cout<<OK<<endl;
    }
    catch(string err){
        try_catch_result(err);
    }
}
void Sputify::show_musics_command(){
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
void Sputify::show_users_command(){
    string arg;
    getline (cin,arg);
    try{
        if(arg == ""){
            check_users_exeption(login_user, clients);
        }
        else{
            arg = arg.substr(arg.find("<")+1,arg.find(">")-arg.find("<")-1);
            check_user_exeptoin(login_user, clients, stoi(arg),musics, playlists);
        }
    }
    catch(string err){
        try_catch_result(err);
    }
}
void Sputify::share_music_command(){
    try{
        musics = check_share_exeption(login_user, musics,musics_num);
        musics_num++;
        cout<<OK<<endl;
    }
    catch(string err){
        try_catch_result(err);
    }
}
void Sputify::show_registered_music_command(){
    try{
        check_registerd_musics_exeption(login_user, musics);
    }
    catch(string err){
        try_catch_result(err);
    }
}
void Sputify::add_playlist_command(){
    try{
        playlists = check_add_playlist_exeption(login_user,playlists);
        cout<<OK<<endl;
    }
    catch(string err){
        try_catch_result(err);
    }
}
void Sputify::add_song_to_playlist_command(){
    try{
        playlists = check_add_music_to_playlist_exeptoin(login_user,playlists,musics);
        cout<<OK<<endl;
    }
    catch(string err){
        try_catch_result(err);
    }
}
void Sputify::delete_song_command(){
    try{
        VPSS arg = get_arg(1);
        musics = check_delete_music_exeption(login_user,musics,stoi(arg[0].second));
        playlists = check_delete_playlist_exeption(playlists, stoi(arg[0].second));
        cout<<OK<<endl;
    }
    catch(string err){
        try_catch_result(err);
    }
}
void Sputify::commands(){
    string command;
    while(cin>>command){
        if (command == COMMANDS[1]){
            string task,delimiter;
            cin>>task>>delimiter;
            if (task == "signup" && delimiter == "?"){
                signup_command();
            }
            else if (task == "login" && delimiter == "?"){
                login_command();
            }
            else if (task == "logout" && delimiter == "?"){
                logout_command();
            }
            else if (task == "music" && delimiter == "?"){
                share_music_command();
            }
            else if (task == "playlist" && delimiter == "?"){
                add_playlist_command();
            }
            else{
                try_catch_result("invalid");
            }
        }
        if (command == COMMANDS[0]){
            string task,delimiter;
            cin>>task>>delimiter;
            if (task == "musics" && delimiter =="?"){
                show_musics_command();
            }
            else if(task == "users" && delimiter =="?"){
                show_users_command();
            }
            else if(task == "registered_musics" && delimiter == "?"){
                show_registered_music_command();
            }
            else if(task == "playlist" && delimiter == "?"){
                try{
                    VPSS arg = get_arg(1);
                    check_show_playlist_exeption(login_user,playlists, musics,clients, stoi(arg[0].second));
                }
                catch(string err){
                    try_catch_result(err);
                }
            }
            else{
                try_catch_result("invalid");
            }
        }
        if (command == COMMANDS[3]){
            string task,delimiter;
            cin>>task>>delimiter;
            if (task == "add_playlist" && delimiter == "?"){
                add_song_to_playlist_command();
            }
            else{
                try_catch_result("invalid");
            }
        }
        if (command == COMMANDS[2]){
            string task,delimiter;
            cin>>task>>delimiter;
            if (task == "music" && delimiter == "?"){
                delete_song_command();
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
