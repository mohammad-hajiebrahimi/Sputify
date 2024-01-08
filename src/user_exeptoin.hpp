#ifndef USER_EXEPTION_HPP_INCLUDE
#define USER_EXEPTION_HPP_INCLUDE
#include <bits/stdc++.h>

using namespace std;

Client * find_cli(string username, vector < Client * > clients);
Client * check_signup_exeption(Client * login_user, vector < Client * > clients, VPSS arg);
Client * check_login_exeption(Client * login_user, vector < Client * > clients, VPSS arg);
Client * check_logout_exeption(Client * login_user);
void check_users_exeption(Client * login_user, vector < Client * > clients);
void check_user_exeptoin(Client * login_user, vector < Client * > clients, int id, vector < Music * > musics, vector < Playlist * > playlists);
void check_search_exeption(Client * login_user, vector < Music * > musics);
void check_follow_exeption(Client * login_user, vector < Client * > & clients, int id);
void check_unfollow_exeption(Client * login_user, vector < Client * > & clients, int id);
void check_show_likes_exeption(Client * login_user);
void check_like_exeption(Client * login_user, vector < Music * > musics, int id);
#endif
