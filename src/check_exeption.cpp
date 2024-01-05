Client * find_cli(string username, vector < Client * > clients) {
    for (int j = 0; j < clients.size(); j++) {
        if (clients[j] -> get_username() == username) {
            return clients[j];
        }
    }

    return NULL;
}

Client * check_signup_exeption(Client * login_user, vector < Client * > clients, VPSS arg) {
    string mode;
    Client * new_cli = NULL;
    for (int i = 0; i < arg.size(); i++) {
        if (arg[i].first == "mode") {
            mode = arg[i].second;
        }
    }

    if (mode == "artist") new_cli = new Artist();
    else {
        new_cli = new User();
    }

    for (int i = 0; i < arg.size(); i++) {
        if (arg[i].first == "username") {
            for (int j = 0; j < clients.size(); j++) {
                if (clients[i] -> get_username() == arg[i].second) throw string("invalid");
            }

            new_cli -> set_username(arg[i].second);
        }

        if (arg[i].first == "mode" && (arg[i].second != "artist" && arg[i].second != "user")) throw string("invalid");
        if (arg[i].first == "mode") {
            new_cli -> set_mode(arg[i].second);
        }

        if (arg[i].first == "password") {
            new_cli -> set_password(arg[i].second);
        }
    }

    if (login_user != NULL) throw string("Permission");

    return new_cli;
}

Client * check_login_exeption(Client * login_user, vector < Client * > clients, VPSS arg) {
    Client * try_to_login = NULL;
    for (int i = 0; i < arg.size(); i++) {
        if (arg[i].first == "username") {
            try_to_login = find_cli(arg[i].second, clients);
        }
    }

    if (try_to_login == NULL) throw string("Not exist");
    for (int i = 0; i < arg.size(); i++) {
        if (arg[i].first == "password") {
            if (arg[i].second != try_to_login -> get_password()) throw string("Permission");
        }
    }

    if (login_user != NULL) throw string("Permission");
    return try_to_login;
}

Client * check_logout_exeption(Client * login_user) {
    if (login_user == NULL) throw string("Permission");
    return NULL;
}


void check_musics_exeption(Client * login_user, vector < Music * > musics) {
    if (login_user == NULL) throw string("Permission");
    if (musics.size() == 0) throw string("empty");
    cout << "ID, Name, Artist" << endl;
    for (int i = 0; i < musics.size(); i++) {
        cout << musics[i] -> get_id() << ", " << musics[i] -> get_name() << ", " << (musics[i] -> get_artist()) -> get_username() << endl;
    }
}

void check_music_exeption(Client * login_user, vector < Music * > musics, int id) {
    if (login_user == NULL) throw string("Permission");
    int flag = 0;
    for (int i = 0; i < musics.size(); i++) {
        if (musics[i] -> get_id() == id) {
            flag = 1;
            cout << "ID, Name, Artist, Year, Album, Tags, Duration" << endl;
            cout << musics[i] -> get_id() << ", " << musics[i] -> get_name() << ", " << (musics[i] -> get_artist()) -> get_username() << ", " << musics[i] -> get_year() << ", " << musics[i] -> get_album() << ", " << musics[i] -> get_tags() << ", " << musics[i] -> get_duration() << endl;
        }
    }

    if (!flag) throw string("Not exist");
}

void check_users_exeption(Client * login_user, vector < Client * > clients) {
    if (login_user == NULL) throw string("Permission");
    if (clients.size() == 0) throw string("empty");
    cout << "ID, Mode, Username, Playlists_number/Songs_number" << endl;
    for (int i = 0; i < clients.size(); i++) {
        if (clients[i] -> get_mode() == ARTIST) {
            cout << i + 1 << ", " << clients[i] -> get_mode() << ", " << clients[i] -> get_username() << ", " << clients[i] -> get_num() << endl;
        } else {
            cout << i + 1 << ", " << clients[i] -> get_mode() << ", " << clients[i] -> get_username() << ", " << clients[i] -> get_num() << endl;
        }
    }
}

void check_user_exeptoin(Client * login_user, vector < Client * > clients, int id, vector < Music * > musics, vector < Playlist * > playlists) {
    if (login_user == NULL) throw string("Permission");
    if (clients.size() == 0) throw string("empty");
    if (clients.size() < id) throw string("Not exist");
    cout << "ID: " << id << endl;
    cout << "Mode: " << clients[id - 1] -> get_mode() << endl;
    cout << "Username: " << clients[id - 1] -> get_username() << endl;
    cout <<"Followings: ";
    vector<int> followings = clients[id-1]->get_following();
    for (int i=0;i<followings.size();i++){
        for(int j=0;j<clients.size();j++){
            if(followings[i] == clients[j]->get_id()){
                cout<<clients[j]->get_username();
                if(i<followings.size()-1)cout<<", ";
            }
        }
    }
    cout<<endl<<"Followers: ";
    vector<int> followers = clients[id-1]->get_follower();
    for (int i=0;i<followers.size();i++){
        for(int j=0;j<clients.size();j++){
            if(followers[i] == clients[j]->get_id()){
                cout<<clients[j]->get_username();
                if(i<followers.size()-1)cout<<", ";
            }
        }
    }
    cout<<endl;
    if (clients[id - 1] -> get_mode() == "artist") {
        cout << "Songs: ";
        int flag = 0;
        for (int i = 0; i < musics.size(); i++) {
            if ((musics[i] -> get_artist()) -> get_username() == clients[id - 1] -> get_username()) {
                if (!flag){
                    cout << musics[i] -> get_name();
                    flag = 1;
                }
                else{
                    cout <<", "<< musics[i] -> get_name();
                }
            }
        }
        cout << endl;
    }

    if (clients[id - 1] -> get_mode() == "user") {
        cout << "Playlists: ";
        int flag = 0;
        for (int i = 0; i < playlists.size(); i++) {
            if ((playlists[i] -> get_owner()) -> get_id() == id) {
                if(!flag){
                    cout << playlists[i] -> get_name();
                    flag = 1;
                }
                else{
                    cout <<", "<< playlists[i] -> get_name();
                }
            }
        }

        cout << endl;
    }
}

vector <Music *> check_share_exeption(Client * login_user, vector < Music * > musics, int musics_num) {
    musics_num++;
    if (login_user -> get_mode() != "artist") throw string("Permission");
    Music * new_music = new Music(musics_num, "", login_user);
    VPSS arg = get_arg(6);
    for (int i = 0; i < arg.size(); i++) {

        if (arg[i].first == TITLE) new_music -> set_name(arg[i].second);
        else if (arg[i].first == PATH) new_music -> set_path(arg[i].second);
        else if (arg[i].first == YEAR) new_music -> set_year(stoi(arg[i].second));
        else if (arg[i].first == TAGS) new_music -> set_tags(arg[i].second);
        else if (arg[i].first == DURATION) new_music -> set_duration(arg[i].second);
        else if (arg[i].first == ALBUM) new_music -> set_album(arg[i].second);
        else {
            throw string("invalid");
        }
    }

    login_user -> add_num();
    musics.push_back(new_music);
    return musics;
}

void check_registerd_musics_exeption(Client * login_user, vector < Music * > musics) {
    if (login_user -> get_mode() != "artist") throw string("Permission");
    vector < Music * > artist_musics;
    for (int i = 0; i < musics.size(); i++) {
        if (login_user -> get_username() == (musics[i] -> get_artist()) -> get_username()) {
            artist_musics.push_back(musics[i]);
        }
    }

    if (artist_musics.size() == 0) throw ("empty");
    cout << "ID, Name, Year, Album, Tags, Duration" << endl;
    for (int i = 0; i < artist_musics.size(); i++) {
        cout << artist_musics[i] -> get_id() << ", " << artist_musics[i] -> get_name() << ", " << artist_musics[i] -> get_year() << ", " << artist_musics[i] -> get_album() << ", " << artist_musics[i] -> get_tags() << ", " << artist_musics[i] -> get_duration() << endl;
    }
}

vector < Playlist * > check_add_playlist_exeption(Client * login_user, vector < Playlist * > playlists) {
    if (login_user -> get_mode() != "user") throw string("Permission");
    VPSS arg = get_arg(1);
    for (int i = 0; i < playlists.size(); i++) {
        if (playlists[i] -> get_name() == arg[0].second && (playlists[i] -> get_owner()) -> get_username() == login_user -> get_username()) throw string("invalid");
    }

    playlists.push_back(new Playlist(arg[0].second, login_user));
    login_user -> add_num();
    return playlists;
}

vector < Playlist * > check_add_music_to_playlist_exeptoin(Client * login_user, vector < Playlist * > playlists, vector < Music * > musics) {
    if (login_user -> get_mode() != "user") throw string("Permission");
    VPSS arg = get_arg(2);
    int id = -1;
    string name;
    for (int i = 0; i < arg.size(); i++) {
        if (arg[i].first == "id") {
            int flag = 0;
            for (int j = 0; j < musics.size(); j++) {
                if (musics[j] -> get_id() == stoi(arg[i].second)) {
                    flag = 1;
                    id = stoi(arg[i].second);
                }
            }

            if (!flag) throw string("Not exist");
        } else if (arg[i].first == "name") {
            int flag = 0;
            for (int j = 0; j < playlists.size(); j++) {
                if (playlists[j] -> get_name() == arg[i].second && (playlists[j] -> get_owner()) -> get_username() == login_user -> get_username()) {
                    flag = 1;
                    name = arg[i].second;
                }
            }

            if (!flag) throw string("Not exist");
        } else {
            throw string("invalid");
        }
    }

    for (int j = 0; j < playlists.size(); j++) {
        if (playlists[j] -> get_name() == name && (playlists[j] -> get_owner()) -> get_username() == login_user -> get_username()) {
            playlists[j] -> add_song(id);
        }
    }

    return playlists;

}

vector < Music * > check_delete_music_exeption(Client * login_user, vector < Music * > musics, int id) {
    int flag = 0;
    for (int i = 0; i < musics.size(); i++) {
        if (musics[i] -> get_id() == id) flag = 1;
    }

    if (!flag) throw string("Not exist");
    flag = 0;
    for (int i = 0; i < musics.size(); i++) {
        if (musics[i] -> get_id() == id && (musics[i] -> get_artist()) -> get_username() == login_user -> get_username()) {
            flag = 1;
            login_user -> del_num();
            musics.erase(musics.begin() + i);
            return musics;
        }
    }

    if (!flag) throw string("Permission");
    return musics;
}

vector < Playlist * > check_delete_song_of_playlist_exeption(vector < Playlist * > playlists, int id) {
    for (int i = 0; i < playlists.size(); i++) {
        vector < int > songs = playlists[i] -> get_songs();
        for (int j = 0; j < songs.size(); j++) {
            if (songs[j] == id) {
                songs.erase(songs.begin() + j);
                break;
            }
        }

        playlists[i] -> set_songs(songs);
    }

    return playlists;
}

void check_show_playlist_exeption(Client * login_user, vector < Playlist * > playlists, vector < Music * > musics, vector < Client * > clients, int id) {
    if (clients.size() < id) throw string("Not exist");
    if (clients[id - 1] -> get_mode() == "artist") throw string("invalid");
    if (login_user -> get_mode() == "artist") throw string("Permission");
    vector < vector < string >> lists;
    for (int i = 0; i < playlists.size(); i++) {
        vector < string > list;
        if ((playlists[i] -> get_owner()) -> get_id() == id) {
            list.push_back(playlists[i] -> get_name());
            list.push_back(to_string((playlists[i] -> get_songs()).size()));
            list.push_back(get_duration_of_playlist(playlists[i] -> get_songs(), musics));
            lists.push_back(list);
        }
    }

    sort(lists.begin(), lists.end(), compare_two_vector);
    cout << "Playlist_ID, Playlist_name, Songs_number, Duration" << endl;
    for (int i = 0; i < lists.size(); i++) {
        cout << i + 1 << ", " << lists[i][0] << ", " << lists[i][1] << ", " << lists[i][2] << endl;
    }
}

void check_search_exeption(Client * login_user, vector < Music * > musics) {
    if (login_user -> get_mode() == "artist") throw string("Permission");
    VPSS arg = get_arg(3);
    vector < Music * > tmp;
    for (int i = 0; i < arg.size(); i++) {
        if (arg[i].first == "name") {
            for (int j = 0; j < musics.size(); j++) {
                if ((musics[j] -> get_name()).find(arg[i].second) != string::npos) {
                    tmp.push_back(musics[j]);
                }
            }

            musics = tmp;
            tmp.clear();
        }

        if (arg[i].first == "artist") {
            for (int j = 0; j < musics.size(); j++) {
                if (((musics[j] -> get_artist()) -> get_username()).find(arg[i].second) != string::npos) {
                    tmp.push_back(musics[j]);
                }
            }

            musics = tmp;
            tmp.clear();
        }

        if (arg[i].first == "tag") {
            for (int j = 0; j < musics.size(); j++) {
                if ((musics[j] -> get_tags()).find(arg[i].second) != string::npos) {
                    tmp.push_back(musics[j]);
                }
            }

            musics = tmp;
            tmp.clear();
        }
    }

    if (musics.size() == 0) throw string("empty");
    cout << "ID, Name, Artist" << endl;
    for (int i = 0; i < musics.size(); i++) {
        cout << musics[i] -> get_id() << ", " << musics[i] -> get_name() << ", " << (musics[i] -> get_artist()) -> get_username() << endl;
    }
}
