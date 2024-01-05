#include <bits/stdc++.h>

using namespace std;

#include "src/magic.hpp"
#include "src/client.cpp"
#include "src/music.cpp"
#include "src/playlist.cpp"
#include "src/help.cpp"
#include "src/check_exeption.cpp"

class Sputify {
    public: Sputify();
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
    void show_playlist_command();
    void follow_command();
    void unfollow_command();
    void commands();
    private: Client * login_user;
    vector < Client * > clients;
    vector < Music * > musics;
    vector < Playlist * > playlists;
    int musics_num;
};

Sputify::Sputify() {
    login_user = NULL;
    musics_num = 0;
}
void check_follow_exeption(Client* login_user, vector < Client * > &clients, int id){
    if (login_user == NULL) throw string("Permission");
    if (login_user->get_id() == id) throw string("invalid");
    vector<int> following = login_user->get_following();
    if (find(following.begin(),following.end(),id) != following.end()) throw string("invalid");
    int flag = 0;
    for (int i=0;i<clients.size();i++){
        if (clients[i]->get_id() == id){
            login_user->follow(id);
            clients[i]->follower(login_user->get_id());
            flag = 1;
        }
    }
    if (!flag)throw string("Not exist");
}

void check_unfollow_exeption(Client* login_user, vector < Client * > &clients, int id){
    if (login_user == NULL) throw string("Permission");
    if (login_user->get_id() == id) throw string("invalid");
    vector<int> following = login_user->get_following();
    int flag = 0;
    for (int i=0;i<clients.size();i++){
        if (clients[i]->get_id() == id){
            flag = 1;
        }
    }
    if (!flag)throw string("Not exist");
    if (find(following.begin(),following.end(),id) == following.end()) throw string("invalid");
    auto ptr = find(following.begin(),following.end(),id);
    following.erase(ptr);
    login_user->set_following(following);
    for (int i=0;i<clients.size();i++){
        if (clients[i]->get_id() == id){
            vector<int> follower = clients[i]->get_follower();
            auto ptr1 = find(follower.begin(),follower.end(),login_user->get_id());
            follower.erase(ptr1);
            clients[i]->set_follower(follower);
        }
    }
}

void check_delete_playlist_exeption(Client* login_user, vector < Playlist * > &playlists, string name){
    if (login_user->get_mode() == "artist") throw string("Permission");
    int flag = 0;
    for(int i=0;i<playlists.size();i++){
        if(playlists[i]->get_name() == name && login_user->get_username() ==(playlists[i]->get_owner())->get_username()){
            playlists.erase(playlists.begin()-i);
            flag = 1;
            break;
        }
    }
    if (!flag)throw string("Not exist");
}

void show_playlist_info(vector<int> songs, vector < Music * > musics){
    for(int i=0;i<songs.size();i++){
        for(int j=0;j<musics.size();j++){
            if(songs[i] == musics[j]->get_id()){
                cout<<musics[j]->get_id()<<", "<<musics[j]->get_name()<<", "<<(musics[j]->get_artist())->get_username()<<endl;
            }
        }
    }
}

void check_show_user_playlist_exeption(Client* login_user, vector < Playlist * > &playlists, vector < Client * > &clients,vector < Music * > musics, VPSS arg){
    if (login_user->get_mode() == "artist") throw string("Permission");
    string name;
    int id;
    for (int i=0;i<arg.size();i++){
        if (arg[i].first == "name")name = arg[i].second;
        else if(arg[i].first == "id")id = stoi(arg[i].second);
    }
    for(int i=0;i<clients.size();i++){
        if(clients[i]->get_id() == id && clients[i]->get_mode() == "artist") throw string("invalid");
    }
    int flag = 0;
    for(int i=0;i<playlists.size();i++){
        if(playlists[i]->get_name() == name && (playlists[i]->get_owner())->get_id() == id){
            cout<<"ID, Name, Artist"<<endl;
            show_playlist_info(playlists[i]->get_songs(), musics);
            flag = 1;
        }
    }
    if (!flag)throw string("Not exist");
}

void check_like_exeption(Client* login_user, vector < Music * > musics, int id){
    if (login_user->get_mode() == "artist") throw string("Permission");
    Music* music = NULL;
    for (int i=0;i<musics.size();i++){
        if (musics[i]->get_id() == id){
            music = musics[i];
        }
    }
    if(music == NULL)throw string("Not exist");
    vector<Music*> likes = login_user->get_likes();
    for(int i=0;i<likes.size();i++){
        if(likes[i]->get_id() == music->get_id()){
            throw string("invalid");
        }
    }
    login_user->add_like(music);
}

void check_show_likes_exeption(Client* login_user){
    if (login_user->get_mode() == "artist") throw string("Permission");
    vector<Music*> likes = login_user->get_likes();
    if (likes.size()==0)throw string("empty");
    cout<<"ID, Name, Artist"<<endl;
    for(int i=0;i<likes.size();i++){
        cout<<likes[i]->get_id()<<", "<<likes[i]->get_name()<<", "<<(likes[i]->get_artist())->get_username()<<endl;
    }
}
void Sputify::signup_command() {
    VPSS arg = get_arg(3);
    try {
        clients.push_back(check_signup_exeption(login_user, clients, arg));
        login_user = clients[clients.size() - 1];
        login_user -> set_id(clients.size());
        cout << OK << endl;
    } catch (string err) {
        try_catch_result(err);
    }
}

void Sputify::login_command() {
    VPSS arg = get_arg(2);
    try {
        login_user = check_login_exeption(login_user, clients, arg);
        cout << OK << endl;
    } catch (string err) {
        try_catch_result(err);
    }
}

void Sputify::logout_command() {
    try {
        login_user = check_logout_exeption(login_user);
        cout << OK << endl;
    } catch (string err) {
        try_catch_result(err);
    }
}

void Sputify::show_musics_command() {
    string arg;
    getline(cin, arg);
    try {
        if (arg == "") {
            check_musics_exeption(login_user, musics);
        } else {
            arg = arg.substr(arg.find("<") + 1, arg.find(">") - arg.find("<") - 1);
            check_music_exeption(login_user, musics, stoi(arg));
        }
    } catch (string err) {
        try_catch_result(err);
    }
}

void Sputify::show_users_command() {
    string arg;
    getline(cin, arg);
    try {
        if (arg == "") {
            check_users_exeption(login_user, clients);
        } else {
            arg = arg.substr(arg.find("<") + 1, arg.find(">") - arg.find("<") - 1);
            check_user_exeptoin(login_user, clients, stoi(arg), musics, playlists);
        }
    } catch (string err) {
        try_catch_result(err);
    }
}

void Sputify::share_music_command() {
    try {
        musics = check_share_exeption(login_user, musics, musics_num);
        musics_num++;
        cout << OK << endl;
    } catch (string err) {
        try_catch_result(err);
    }
}

void Sputify::show_registered_music_command() {
    try {
        check_registerd_musics_exeption(login_user, musics);
    } catch (string err) {
        try_catch_result(err);
    }
}

void Sputify::add_playlist_command() {
    try {
        playlists = check_add_playlist_exeption(login_user, playlists);
        cout << OK << endl;
    } catch (string err) {
        try_catch_result(err);
    }
}

void Sputify::add_song_to_playlist_command() {
    try {
        playlists = check_add_music_to_playlist_exeptoin(login_user, playlists, musics);
        cout << OK << endl;
    } catch (string err) {
        try_catch_result(err);
    }
}

void Sputify::show_playlist_command() {
    try {
        VPSS arg = get_arg(1);
        if(arg.size()==1){
            check_show_playlist_exeption(login_user, playlists, musics, clients, stoi(arg[0].second));
        }
        else{
            check_show_user_playlist_exeption(login_user, playlists,clients,musics,arg);
        }
    } catch (string err) {
        try_catch_result(err);
    }
}

void Sputify::delete_song_command() {
    try {
        VPSS arg = get_arg(1);
        musics = check_delete_music_exeption(login_user, musics, stoi(arg[0].second));
        playlists = check_delete_song_of_playlist_exeption(playlists, stoi(arg[0].second));
        cout << OK << endl;
    } catch (string err) {
        try_catch_result(err);
    }
}

void Sputify::follow_command(){
    try{
        VPSS arg = get_arg(1);
        check_follow_exeption(login_user, clients, stoi(arg[0].second));
        cout<<OK<<endl;
    }
    catch(string err){
        try_catch_result(err);
    }
}

void Sputify::unfollow_command(){
    try{
        VPSS arg = get_arg(1);
        check_unfollow_exeption(login_user, clients, stoi(arg[0].second));
        cout<<OK<<endl;
    }
    catch(string err){
        try_catch_result(err);
    }
}

void Sputify::commands() {
    string command;
    while (cin >> command) {
        if (command == COMMANDS[1]) {
            string task, delimiter;
            cin >> task >> delimiter;
            if (task == SIGNUP && delimiter == "?") {
                signup_command();
            } else if (task == LOGIN && delimiter == "?") {
                login_command();
            } else if (task == LOGOUT && delimiter == "?") {
                logout_command();
            } else if (task == MUSIC && delimiter == "?") {
                share_music_command();
            } else if (task == PLAYLIST && delimiter == "?") {
                add_playlist_command();
            } else if (task == "follow" && delimiter == "?"){
                follow_command();
            } else if (task == "unfollow" && delimiter == "?"){
                unfollow_command();
            } else if (task == "like" && delimiter == "?"){
                try{
                    VPSS arg = get_arg(1);
                    check_like_exeption(login_user, musics,stoi(arg[0].second));
                    cout<<OK<<endl;
                }
                catch(string err){
                    try_catch_result(err);
                }
            }
            else {
                try_catch_result("invalid");
            }
        }

        if (command == COMMANDS[0]) {
            string task, delimiter;
            cin >> task >> delimiter;
            if (task == MUSICS && delimiter == "?") {
                show_musics_command();
            } else if (task == USERS && delimiter == "?") {
                show_users_command();
            } else if (task == REGISTERED_MUSICS && delimiter == "?") {
                show_registered_music_command();
            } else if (task == PLAYLIST && delimiter == "?") {
                show_playlist_command();
            } else if (task == SEARCH_MUSIC && delimiter == "?") {
                try {
                    check_search_exeption(login_user, musics);
                } catch (string err) {
                    try_catch_result(err);
                }
            } else if (task == "likes" && delimiter == "?"){
                try{
                    check_show_likes_exeption(login_user);
                }
                catch(string err){
                    try_catch_result(err);
                }
            } else {
                try_catch_result("invalid");
            }
        }

        if (command == COMMANDS[3]) {
            string task, delimiter;
            cin >> task >> delimiter;
            if (task == ADD_PLAYLIST && delimiter == "?") {
                add_song_to_playlist_command();
            } else {
                try_catch_result("invalid");
            }
        }

        if (command == COMMANDS[2]) {
            string task, delimiter;
            cin >> task >> delimiter;
            if (task == MUSIC && delimiter == "?") {
                delete_song_command();
            } else if (task == PLAYLIST && delimiter == "?"){
                try{
                    VPSS arg = get_arg(1);
                    check_delete_playlist_exeption(login_user, playlists, arg[0].second);
                    cout<<OK<<endl;
                }
                catch(string err){
                    try_catch_result(err);
                }
            }
            else {
                try_catch_result("invalid");
            }
        }
    }
}

int main() {
    Sputify sputify;
    sputify.commands();
    return 0;
}
