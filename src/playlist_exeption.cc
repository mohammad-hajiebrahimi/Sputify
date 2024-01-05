vector < Playlist * > check_add_playlist_exeption(Client * login_user, vector < Playlist * > playlists) {
    if (login_user -> get_mode() != LUSER) throw string(ERR_PERMISSION);
    VPSS arg = get_arg(1);
    for (int i = 0; i < playlists.size(); i++) {
        if (playlists[i] -> get_name() == arg[0].second && (playlists[i] -> get_owner()) -> get_username() == login_user -> get_username()) throw string(ERR_INVALID);
    }

    playlists.push_back(new Playlist(arg[0].second, login_user));
    login_user -> add_num();
    return playlists;
}

vector < Playlist * > check_add_music_to_playlist_exeptoin(Client * login_user, vector < Playlist * > playlists, vector < Music * > musics) {
    if (login_user -> get_mode() != LUSER) throw string(ERR_PERMISSION);
    VPSS arg = get_arg(2);
    int id = -1;
    string name;
    for (int i = 0; i < arg.size(); i++) {
        if (arg[i].first == _ID) {
            int flag = 0;
            for (int j = 0; j < musics.size(); j++) {
                if (musics[j] -> get_id() == stoi(arg[i].second)) {
                    flag = 1;
                    id = stoi(arg[i].second);
                }
            }

            if (!flag) throw string(ERR_NOTEXIST);
        } else if (arg[i].first == NAME) {
            int flag = 0;
            for (int j = 0; j < playlists.size(); j++) {
                if (playlists[j] -> get_name() == arg[i].second && (playlists[j] -> get_owner()) -> get_username() == login_user -> get_username()) {
                    flag = 1;
                    name = arg[i].second;
                }
            }

            if (!flag) throw string(ERR_NOTEXIST);
        } else {
            throw string(ERR_INVALID);
        }
    }

    for (int j = 0; j < playlists.size(); j++) {
        if (playlists[j] -> get_name() == name && (playlists[j] -> get_owner()) -> get_username() == login_user -> get_username()) {
            playlists[j] -> add_song(id);
        }
    }

    return playlists;

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
    if (clients.size() < id) throw string(ERR_NOTEXIST);
    if (clients[id - 1] -> get_mode() == LARTIST) throw string(ERR_INVALID);
    if (login_user -> get_mode() == LARTIST) throw string(ERR_PERMISSION);
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

void check_delete_playlist_exeption(Client * login_user, vector < Playlist * > & playlists, string name) {
    if (login_user -> get_mode() == LARTIST) throw string(ERR_PERMISSION);
    int flag = 0;
    for (int i = 0; i < playlists.size(); i++) {
        if (playlists[i] -> get_name() == name && login_user -> get_username() == (playlists[i] -> get_owner()) -> get_username()) {
            playlists.erase(playlists.begin() - i);
            flag = 1;
            break;
        }
    }
    if (!flag) throw string(ERR_NOTEXIST);
}

void show_playlist_info(vector < int > songs, vector < Music * > musics) {
    for (int i = 0; i < songs.size(); i++) {
        for (int j = 0; j < musics.size(); j++) {
            if (songs[i] == musics[j] -> get_id()) {
                cout << musics[j] -> get_id() << ", " << musics[j] -> get_name() << ", " << (musics[j] -> get_artist()) -> get_username() << endl;
            }
        }
    }
}

void check_show_user_playlist_exeption(Client * login_user, vector < Playlist * > & playlists, vector < Client * > & clients, vector < Music * > musics, VPSS arg) {
    if (login_user -> get_mode() == LARTIST) throw string(ERR_PERMISSION);
    string name;
    int id;
    for (int i = 0; i < arg.size(); i++) {
        if (arg[i].first == NAME) name = arg[i].second;
        else if (arg[i].first == _ID) id = stoi(arg[i].second);
    }
    for (int i = 0; i < clients.size(); i++) {
        if (clients[i] -> get_id() == id && clients[i] -> get_mode() == LARTIST) throw string(ERR_INVALID);
    }
    int flag = 0;
    for (int i = 0; i < playlists.size(); i++) {
        if (playlists[i] -> get_name() == name && (playlists[i] -> get_owner()) -> get_id() == id) {
            cout << "ID, Name, Artist" << endl;
            show_playlist_info(playlists[i] -> get_songs(), musics);
            flag = 1;
        }
    }
    if (!flag) throw string(ERR_NOTEXIST);
}
