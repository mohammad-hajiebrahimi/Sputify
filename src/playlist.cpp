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
