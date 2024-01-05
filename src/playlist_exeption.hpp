#ifndef PLAYLIST_EXEPTION_HPP_INCLUDE
#define PLAYLIST_EXEPTION_HPP_INCLUDE
vector < Playlist * > check_add_playlist_exeption(Client * login_user, vector < Playlist * > playlists);
vector < Playlist * > check_add_music_to_playlist_exeptoin(Client * login_user, vector < Playlist * > playlists, vector < Music * > musics);
vector < Playlist * > check_delete_song_of_playlist_exeption(vector < Playlist * > playlists, int id);
void check_show_playlist_exeption(Client * login_user, vector < Playlist * > playlists, vector < Music * > musics, vector < Client * > clients, int id);
void check_delete_playlist_exeption(Client * login_user, vector < Playlist * > & playlists, string name);
void show_playlist_info(vector < int > songs, vector < Music * > musics);
void check_show_user_playlist_exeption(Client * login_user, vector < Playlist * > & playlists, vector < Client * > & clients, vector < Music * > musics, VPSS arg);
#endif
