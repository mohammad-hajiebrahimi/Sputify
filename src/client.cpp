#include "client.hpp"


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
