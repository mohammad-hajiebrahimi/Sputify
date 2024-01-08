#include "client.hpp"
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
