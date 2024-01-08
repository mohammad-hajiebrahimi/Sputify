#include <bits/stdc++.h>

using namespace std;

#include "src/magic.hpp"
#include "src/client.cc"
#include "src/music.cc"
#include "src/playlist.cc"
#include "src/help.cc"
#include "src/user_exeption.cc"
#include "src/playlist_exeption.cc"
#include "src/music_exeption.cc"



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
    void like_command();
    void search_music_command();
    void show_likes_command();
    void show_recocommendations_command();
    void delete_playlist_command();
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
        if (arg.size() == 1) {
            check_show_playlist_exeption(login_user, playlists, musics, clients, stoi(arg[0].second));
        } else {
            check_show_user_playlist_exeption(login_user, playlists, clients, musics, arg);
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

void Sputify::follow_command() {
    try {
        VPSS arg = get_arg(1);
        check_follow_exeption(login_user, clients, stoi(arg[0].second));
        cout << OK << endl;
    } catch (string err) {
        try_catch_result(err);
    }
}

void Sputify::unfollow_command() {
    try {
        VPSS arg = get_arg(1);
        check_unfollow_exeption(login_user, clients, stoi(arg[0].second));
        cout << OK << endl;
    } catch (string err) {
        try_catch_result(err);
    }
}

void Sputify::like_command() {
    try {
        VPSS arg = get_arg(1);
        check_like_exeption(login_user, musics, stoi(arg[0].second));
        cout << OK << endl;
    } catch (string err) {
        try_catch_result(err);
    }
}

void Sputify::search_music_command() {
    try {
        check_search_exeption(login_user, musics);
    } catch (string err) {
        try_catch_result(err);
    }
}

void Sputify::show_likes_command() {
    try {
        check_show_likes_exeption(login_user);
    } catch (string err) {
        try_catch_result(err);
    }
}

void Sputify::show_recocommendations_command() {
    try {
        check_recommendations_exeption(login_user, musics);
    } catch (string err) {
        try_catch_result(err);
    }
}

void Sputify::delete_playlist_command() {
    try {
        VPSS arg = get_arg(1);
        check_delete_playlist_exeption(login_user, playlists, arg[0].second);
        cout << OK << endl;
    } catch (string err) {
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
            } else if (task == FOLLOW && delimiter == "?") {
                follow_command();
            } else if (task == UNFOLLOW && delimiter == "?") {
                unfollow_command();
            } else if (task == LIKE && delimiter == "?") {
                like_command();
            } else {
                try_catch_result(ERR_INVALID);
            }
        }

        else if (command == COMMANDS[0]) {
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
                search_music_command();
            } else if (task == LIKES && delimiter == "?") {
                show_likes_command();
            } else if (task == RECOMMENDATIONS && delimiter == "?") {
                show_recocommendations_command();
            } else {
                try_catch_result(ERR_INVALID);
            }
        }

        else if (command == COMMANDS[3]) {
            string task, delimiter;
            cin >> task >> delimiter;
            if (task == ADD_PLAYLIST && delimiter == "?") {
                add_song_to_playlist_command();
            } else {
                try_catch_result(ERR_INVALID);
            }
        }

        else if (command == COMMANDS[2]) {
            string task, delimiter;
            cin >> task >> delimiter;
            if (task == MUSIC && delimiter == "?") {
                delete_song_command();
            } else if (task == PLAYLIST && delimiter == "?") {
                delete_playlist_command();
            } else {
                try_catch_result(ERR_INVALID);
            }
        }
        else{
            try_catch_result(ERR_INVALID);
        }
    }
}

int main() {
    Sputify sputify;
    sputify.commands();
    return 0;
}
