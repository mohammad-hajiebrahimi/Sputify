#ifndef MUSIC_EXEPTION_HPP_INCLUDE
#define MUSIC_EXEPTION_HPP_INCLUDE
void check_musics_exeption(Client * login_user, vector < Music * > musics);
void check_music_exeption(Client * login_user, vector < Music * > musics, int id);
vector < Music * > check_share_exeption(Client * login_user, vector < Music * > musics, int musics_num);
void check_registerd_musics_exeption(Client * login_user, vector < Music * > musics);
vector < Music * > check_delete_music_exeption(Client * login_user, vector < Music * > musics, int id);
void check_recommendations_exeption(Client * login_user, vector < Music * > musics);
#endif
