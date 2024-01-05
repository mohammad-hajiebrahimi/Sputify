#include <bits/stdc++.h>

using namespace std;

#define sep ' '
#define endl '\n'
#define tab '\t'
typedef vector < pair < string, string >> VPSS;
const string OK = "OK";
const string EMPTY = "Empty";
const string NOT_FOUND = "Not Found";
const string BAD_REQUEST = "Bad Request";
const string PERMISSION = "Permission Denied";
const string ARTIST = "Artist";
const string USER = "User";
const string SIGNUP = "signup";
const string LOGIN = "login";
const string LOGOUT = "logout";
const string MUSIC = "music";
const string PLAYLIST = "playlist";
const string MUSICS = "musics";
const string USERS = "users";
const string SEARCH_MUSIC = "search_music";
const string REGISTERED_MUSICS = "registered_musics";
const string ADD_PLAYLIST = "add_playlist";
const string TITLE = "title";
const string PATH = "path";
const string YEAR = "year";
const string TAGS = "tags";
const string DURATION = "duration";
const string ALBUM = "album";
const string ERR_INVALID = "invalid";
const string ERR_PERMISSION = "Permission";
const string ERR_NOTEXIST = "Not exist";
const string ERR_EMPTY = "empty";
const string MODE = "mode";
const string LARTIST = "artist";
const string LIKES = "likes";
const string RECOMMENDATIONS = "recommendations";
const string USERNAME = "username";
const string LUSER = "user";
const string PASSWORD = "password";
const string NAME = "name";
const string _ID = "id";
const string TAG = "tag";
const string FOLLOW = "follow";
const string UNFOLLOW = "unfollow";
const string LIKE = "like";
const vector < string > COMMANDS = {
    "GET",
    "POST",
    "DELETE",
    "PUT"
};
class Music;
class Client {
    public: Client();
    virtual string get_username() {
        return username;
    }

    virtual string get_password() {
        return password;
    }

    virtual string get_mode() {
        return mode;
    }

    virtual void set_username(string user) {
        username = user;
    }

    virtual void set_password(string pass) {
        password = pass;
    }

    virtual void set_mode(string _mode) {
        mode = _mode;
    }

    virtual int get_num() {
        return -1;
    }

    virtual void add_num() {}

    virtual void del_num() {}

    virtual int get_id() {
        return id;
    }

    virtual void set_id(int _id) {
        id = _id;
    }
    virtual vector < int > get_following() {
        return follow_id;
    }
    virtual void follow(int _id) {
        follow_id.push_back(_id);
    }
    virtual void set_following(vector < int > _follow_id) {
        follow_id = _follow_id;
    }
    virtual vector < int > get_follower() {
        return follower_id;
    }
    virtual void follower(int _id) {
        follower_id.push_back(_id);
    }
    virtual void set_follower(vector < int > _follower_id) {
        follower_id = _follower_id;
    }
    virtual vector < Music * > get_likes() {
        return likes;
    }
    virtual void add_like(Music * like) {
        likes.push_back(like);
    }
    protected: int id;
    string username;
    string password;
    string mode;
    vector < int > follow_id;
    vector < int > follower_id;
    vector < Music * > likes;
};

Client::Client() {
    username = " ";
    password = " ";
    mode = "";
    int id = -1;
}

class User: public Client {
    public: User();
    int get_num() {
        return playlist_num;
    }

    void add_num() {
        playlist_num++;
    }

    protected: int playlist_num;

};

User::User(): Client() {
    mode = USER;
    playlist_num = 0;
}

class Artist: public Client {
    public: Artist();
    int get_num() {
        return songs_num;
    }

    void add_num() {
        songs_num++;
    }

    void del_num() {
        songs_num--;
    }

    protected: int songs_num;
    vector < string > songs;
};

Artist::Artist(): Client() {
    mode = ARTIST;
    songs_num = 0;
}

class Music {
    public: Music(int _id, string _name, Client * _artist);
    int get_id() {
        return id;
    }

    string get_name() {
        return name;
    }

    Client * get_artist() {
        return artist;
    }

    int get_year() {
        return year;
    }

    string get_album() {
        return album;
    }

    string get_tags() {
        return tags;
    }

    string get_duration() {
        return duration;
    }

    void set_name(string _name) {
        name = _name;
    }

    void set_year(int _year) {
        year = _year;
    }

    void set_album(string _album) {
        album = _album;
    }

    void set_tags(string _tags) {
        tags = _tags;
    }

    void set_path(string _path) {
        path = _path;
    }

    void set_duration(string _duration) {
        duration = _duration;
    }
    int get_like() {
        return like;
    }
    void add_like() {
        like++;
    }
    private: int id;
    string name;
    Client * artist;
    int year;
    string album;
    string tags;
    string duration;
    string path;
    int like;
};

Music::Music(int _id, string _name, Client * _artist) {
    id = _id;
    name = _name;
    artist = _artist;
    like = 0;
}

class Playlist {
    public: Playlist(string _name, Client * _owner) {
        name = _name;
        owner = _owner;
    }

    string get_name() {
        return name;
    }

    Client * get_owner() {
        return owner;
    }

    vector < int > get_songs() {
        return songs;
    }

    void set_songs(vector < int > _songs) {
        songs = _songs;
    }

    void add_song(int id) {
        songs.push_back(id);
    }

    private: string name;
    Client * owner;
    vector < int > songs;
};

VPSS get_arg(int n) {
    VPSS content;
    string line;
    getline(cin, line);
    line = line;
    vector < string > row;
    stringstream str(line);
    string word;
    while (getline(str, word, '>')) {
        row.clear();
        word += ">";
        string text;
        stringstream strr(word);
        getline(strr, text, ' ');
        while (getline(strr, text, ' ')) {
            row.push_back(text);
        }

        string fir, sec = "";
        for (int i = 1; i < row.size(); i++) {
            sec += (row[i] + " ");
        }

        sec = sec.substr(1, sec.length() - 3);
        content.push_back(make_pair(row[0], sec));
    }

    return content;
}

void try_catch_result(string err) {
    if (err == ERR_INVALID) {
        cout << BAD_REQUEST << endl;
    }

    if (err == ERR_PERMISSION) {
        cout << PERMISSION << endl;
    }

    if (err == ERR_NOTEXIST) {
        cout << NOT_FOUND << endl;
    }

    if (err == ERR_EMPTY) {
        cout << EMPTY << endl;
    }
}

int get_seconds_from_string(const string & timeString) {
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

string get_duration_of_playlist(vector < int > songs, vector < Music * > musics) {
    int dur = 0;
    for (int i = 0; i < songs.size(); i++) {
        for (int j = 0; j < musics.size(); j++) {
            if (songs[i] == musics[j] -> get_id()) {
                dur += get_seconds_from_string(musics[j] -> get_duration());
            }
        }
    }

    return get_string_from_seconds(dur);
}

bool compare_two_vector(vector < string > a, vector < string > b) {
    return a[0] < b[0];
}

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

void check_show_likes_exeption(Client * login_user) {
    if (login_user -> get_mode() == LARTIST) throw string(ERR_PERMISSION);
    vector < Music * > likes = login_user -> get_likes();
    if (likes.size() == 0) throw string(ERR_EMPTY);
    cout << "ID, Name, Artist" << endl;
    for (int i = 0; i < likes.size(); i++) {
        cout << likes[i] -> get_id() << ", " << likes[i] -> get_name() << ", " << (likes[i] -> get_artist()) -> get_username() << endl;
    }
}

bool compare_two_music(Music * a, Music * b) {
    return (a -> get_like() > b -> get_like() && a -> get_id() < b -> get_id());
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
