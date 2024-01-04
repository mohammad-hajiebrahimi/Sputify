#ifndef MAGIC_HPP_INCLUDE
#define MAGIC_HPP_INCLUDE

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
const vector < string > COMMANDS = {
    "GET",
    "POST",
    "DELETE",
    "PUT"
};
#endif
