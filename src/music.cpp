#include "music.hpp"
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
    int get_like(){return like;}
    void add_like(){like++;}
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
