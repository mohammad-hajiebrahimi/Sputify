#include "music_exeption.hpp"
void check_musics_exeption(Client * login_user, vector < Music * > musics) {
    if (login_user == NULL) throw string(ERR_PERMISSION);
    if (musics.size() == 0) throw string(ERR_EMPTY);
    cout << "ID, Name, Artist" << endl;
    for (int i = 0; i < musics.size(); i++) {
        cout << musics[i] -> get_id() << ", " << musics[i] -> get_name() << ", " << (musics[i] -> get_artist()) -> get_username() << endl;
    }
}

void check_music_exeption(Client * login_user, vector < Music * > musics, int id) {
    if (login_user == NULL) throw string(ERR_PERMISSION);
    int flag = 0;
    for (int i = 0; i < musics.size(); i++) {
        if (musics[i] -> get_id() == id) {
            flag = 1;
            cout << "ID, Name, Artist, Year, Album, Tags, Duration" << endl;
            cout << musics[i] -> get_id() << ", " << musics[i] -> get_name() << ", " << (musics[i] -> get_artist()) -> get_username() << ", " << musics[i] -> get_year() << ", " << musics[i] -> get_album() << ", " << musics[i] -> get_tags() << ", " << musics[i] -> get_duration() << endl;
        }
    }

    if (!flag) throw string(ERR_NOTEXIST);
}

vector < Music * > check_share_exeption(Client * login_user, vector < Music * > musics, int musics_num) {
    musics_num++;
    if (login_user -> get_mode() != LARTIST) throw string(ERR_PERMISSION);
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
            throw string(ERR_INVALID);
        }
    }

    login_user -> add_num();
    musics.push_back(new_music);
    return musics;
}

void check_registerd_musics_exeption(Client * login_user, vector < Music * > musics) {
    if (login_user == NULL || login_user -> get_mode() != LARTIST) throw string(ERR_PERMISSION);
    vector < Music * > artist_musics;
    for (int i = 0; i < musics.size(); i++) {
        if (login_user -> get_username() == (musics[i] -> get_artist()) -> get_username()) {
            artist_musics.push_back(musics[i]);
        }
    }

    if (artist_musics.size() == 0) throw (ERR_EMPTY);
    cout << "ID, Name, Year, Album, Tags, Duration" << endl;
    for (int i = 0; i < artist_musics.size(); i++) {
        cout << artist_musics[i] -> get_id() << ", " << artist_musics[i] -> get_name() << ", " << artist_musics[i] -> get_year() << ", " << artist_musics[i] -> get_album() << ", " << artist_musics[i] -> get_tags() << ", " << artist_musics[i] -> get_duration() << endl;
    }
}

vector < Music * > check_delete_music_exeption(Client * login_user, vector < Music * > musics, int id) {
    int flag = 0;
    for (int i = 0; i < musics.size(); i++) {
        if (musics[i] -> get_id() == id) flag = 1;
    }

    if (!flag) throw string(ERR_NOTEXIST);
    flag = 0;
    for (int i = 0; i < musics.size(); i++) {
        if (musics[i] -> get_id() == id && (musics[i] -> get_artist()) -> get_username() == login_user -> get_username()) {
            flag = 1;
            login_user -> del_num();
            musics.erase(musics.begin() + i);
            return musics;
        }
    }

    if (!flag) throw string(ERR_PERMISSION);
    return musics;
}

void check_recommendations_exeption(Client * login_user, vector < Music * > musics) {

    if (login_user==NULL || login_user -> get_mode() == LARTIST) throw string(ERR_PERMISSION);
    sort(musics.begin(), musics.end(), compare_two_music);
    vector < Music * > likes = login_user -> get_likes();
    for (int i = 0; i < likes.size(); i++) {
        for (int j = 0; j < musics.size(); j++) {
            if (likes[i] -> get_id() == musics[j] -> get_id()) {
                musics.erase(musics.begin() + j);
                break;
            }
        }
    }
    vector < Music * > ans_music;
    for (int i = 0; i < musics.size(); i++) {
        if (musics[i] -> get_like() != 0) {
            ans_music.push_back(musics[i]);
        }
    }
    musics = ans_music;
    if (musics.size() == 0) throw string(ERR_EMPTY);
    cout << "ID, Name, Artist, Likes" << endl;
    for (int i = 0; i < min(int(musics.size()), 5); i++) {
        cout << musics[i] -> get_id() << ", " << musics[i] -> get_name() << ", " << (musics[i] -> get_artist()) -> get_username() << ", " << musics[i] -> get_like() << endl;
    }
}
