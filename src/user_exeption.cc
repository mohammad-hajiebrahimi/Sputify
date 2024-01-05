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
        if (arg[i].first == MODE) {
            mode = arg[i].second;
        }
    }

    if (mode == LARTIST) new_cli = new Artist();
    else {
        new_cli = new User();
    }

    for (int i = 0; i < arg.size(); i++) {
        if (arg[i].first == USERNAME) {
            for (int j = 0; j < clients.size(); j++) {
                if (clients[j] -> get_username() == arg[i].second) throw string(ERR_INVALID);
            }

            new_cli -> set_username(arg[i].second);
        }

        if (arg[i].first == MODE && (arg[i].second != LARTIST && arg[i].second != LUSER)) throw string(ERR_INVALID);
        if (arg[i].first == MODE) {
            new_cli -> set_mode(arg[i].second);
        }

        if (arg[i].first == PASSWORD) {
            new_cli -> set_password(arg[i].second);
        }
    }

    if (login_user != NULL) throw string(ERR_PERMISSION);

    return new_cli;
}

Client * check_login_exeption(Client * login_user, vector < Client * > clients, VPSS arg) {
    Client * try_to_login = NULL;
    for (int i = 0; i < arg.size(); i++) {
        if (arg[i].first == USERNAME) {
            try_to_login = find_cli(arg[i].second, clients);
        }
    }

    if (try_to_login == NULL) throw string(ERR_NOTEXIST);
    for (int i = 0; i < arg.size(); i++) {
        if (arg[i].first == PASSWORD) {
            if (arg[i].second != try_to_login -> get_password()) throw string(ERR_PERMISSION);
        }
    }

    if (login_user != NULL) throw string(ERR_PERMISSION);
    return try_to_login;
}

Client * check_logout_exeption(Client * login_user) {
    if (login_user == NULL) throw string(ERR_PERMISSION);
    return NULL;
}

void check_users_exeption(Client * login_user, vector < Client * > clients) {
    if (login_user == NULL) throw string(ERR_PERMISSION);
    if (clients.size() == 0) throw string(ERR_EMPTY);
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
    if (login_user == NULL) throw string(ERR_PERMISSION);
    if (clients.size() == 0) throw string(ERR_EMPTY);
    if (clients.size() < id) throw string(ERR_NOTEXIST);
    cout << "ID: " << id << endl;
    cout << "Mode: " << clients[id - 1] -> get_mode() << endl;
    cout << "Username: " << clients[id - 1] -> get_username() << endl;
    cout << "Followings: ";
    vector < int > followings = clients[id - 1] -> get_following();
    for (int i = 0; i < followings.size(); i++) {
        for (int j = 0; j < clients.size(); j++) {
            if (followings[i] == clients[j] -> get_id()) {
                cout << clients[j] -> get_username();
                if (i < followings.size() - 1) cout << ", ";
            }
        }
    }
    cout << endl << "Followers: ";
    vector < int > followers = clients[id - 1] -> get_follower();
    for (int i = 0; i < followers.size(); i++) {
        for (int j = 0; j < clients.size(); j++) {
            if (followers[i] == clients[j] -> get_id()) {
                cout << clients[j] -> get_username();
                if (i < followers.size() - 1) cout << ", ";
            }
        }
    }
    cout << endl;
    if (clients[id - 1] -> get_mode() == LARTIST) {
        cout << "Songs: ";
        int flag = 0;
        for (int i = 0; i < musics.size(); i++) {
            if ((musics[i] -> get_artist()) -> get_username() == clients[id - 1] -> get_username()) {
                if (!flag) {
                    cout << musics[i] -> get_name();
                    flag = 1;
                } else {
                    cout << ", " << musics[i] -> get_name();
                }
            }
        }
        cout << endl;
    }

    if (clients[id - 1] -> get_mode() == LUSER) {
        cout << "Playlists: ";
        int flag = 0;
        for (int i = 0; i < playlists.size(); i++) {
            if ((playlists[i] -> get_owner()) -> get_id() == id) {
                if (!flag) {
                    cout << playlists[i] -> get_name();
                    flag = 1;
                } else {
                    cout << ", " << playlists[i] -> get_name();
                }
            }
        }

        cout << endl;
    }
}

void check_search_exeption(Client * login_user, vector < Music * > musics) {
    if (login_user -> get_mode() == LARTIST) throw string(ERR_PERMISSION);
    VPSS arg = get_arg(3);
    vector < Music * > tmp;
    for (int i = 0; i < arg.size(); i++) {
        if (arg[i].first == NAME) {
            for (int j = 0; j < musics.size(); j++) {
                if ((musics[j] -> get_name()).find(arg[i].second) != string::npos) {
                    tmp.push_back(musics[j]);
                }
            }

            musics = tmp;
            tmp.clear();
        }

        if (arg[i].first == LARTIST) {
            for (int j = 0; j < musics.size(); j++) {
                if (((musics[j] -> get_artist()) -> get_username()).find(arg[i].second) != string::npos) {
                    tmp.push_back(musics[j]);
                }
            }

            musics = tmp;
            tmp.clear();
        }

        if (arg[i].first == TAG) {
            for (int j = 0; j < musics.size(); j++) {
                if ((musics[j] -> get_tags()).find(arg[i].second) != string::npos) {
                    tmp.push_back(musics[j]);
                }
            }

            musics = tmp;
            tmp.clear();
        }
    }

    if (musics.size() == 0) throw string(ERR_EMPTY);
    cout << "ID, Name, Artist" << endl;
    for (int i = 0; i < musics.size(); i++) {
        cout << musics[i] -> get_id() << ", " << musics[i] -> get_name() << ", " << (musics[i] -> get_artist()) -> get_username() << endl;
    }
}

void check_follow_exeption(Client * login_user, vector < Client * > & clients, int id) {
    if (login_user == NULL) throw string(ERR_PERMISSION);
    if (login_user -> get_id() == id) throw string(ERR_INVALID);
    vector < int > following = login_user -> get_following();
    if (find(following.begin(), following.end(), id) != following.end()) throw string(ERR_INVALID);
    int flag = 0;
    for (int i = 0; i < clients.size(); i++) {
        if (clients[i] -> get_id() == id) {
            login_user -> follow(id);
            clients[i] -> follower(login_user -> get_id());
            flag = 1;
        }
    }
    if (!flag) throw string(ERR_NOTEXIST);
}

void check_unfollow_exeption(Client * login_user, vector < Client * > & clients, int id) {
    if (login_user == NULL) throw string(ERR_PERMISSION);
    if (login_user -> get_id() == id) throw string(ERR_INVALID);
    vector < int > following = login_user -> get_following();
    int flag = 0;
    for (int i = 0; i < clients.size(); i++) {
        if (clients[i] -> get_id() == id) {
            flag = 1;
        }
    }
    if (!flag) throw string(ERR_NOTEXIST);
    if (find(following.begin(), following.end(), id) == following.end()) throw string(ERR_INVALID);
    auto ptr = find(following.begin(), following.end(), id);
    following.erase(ptr);
    login_user -> set_following(following);
    for (int i = 0; i < clients.size(); i++) {
        if (clients[i] -> get_id() == id) {
            vector < int > follower = clients[i] -> get_follower();
            auto ptr1 = find(follower.begin(), follower.end(), login_user -> get_id());
            follower.erase(ptr1);
            clients[i] -> set_follower(follower);
        }
    }
}

void check_show_likes_exeption(Client * login_user) {
    if (login_user -> get_mode() == LARTIST) throw string(ERR_PERMISSION);
    vector < Music * > likes = login_user -> get_likes();
    if (likes.size() == 0) throw string(ERR_EMPTY);
    cout << "ID, Name, Artist" << endl;
    for (int i = 0; i < likes.size(); i++) {
        cout << likes[i] -> get_id() << ", " << likes[i] -> get_name() << ", " << (likes[i] -> get_artist()) -> get_username() << endl;
    }
}

void check_like_exeption(Client * login_user, vector < Music * > musics, int id) {
    if (login_user -> get_mode() == LARTIST) throw string(ERR_PERMISSION);
    Music * music = NULL;
    for (int i = 0; i < musics.size(); i++) {
        if (musics[i] -> get_id() == id) {
            music = musics[i];
        }
    }
    if (music == NULL) throw string(ERR_NOTEXIST);
    vector < Music * > likes = login_user -> get_likes();
    for (int i = 0; i < likes.size(); i++) {
        if (likes[i] -> get_id() == music -> get_id()) {
            throw string(ERR_INVALID);
        }
    }
    music -> add_like();
    login_user -> add_like(music);
}
