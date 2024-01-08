#ifndef HELP_HPP_INCLUDE
#define HELP_HPP_INCLUDE
#include <bits/stdc++.h>

using namespace std;

#include "magic.hpp"
#include "music.hpp"

VPSS get_arg(int n);
void try_catch_result(string err);
int get_seconds_from_string(const string & timeString);
string get_string_from_seconds(int seconds);
string get_duration_of_playlist(vector < int > songs, vector < Music * > musics);
bool compare_two_vector(vector < string > a, vector < string > b);
bool compare_two_music(Music * a, Music * b);
#endif
