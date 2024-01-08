#include "help.hpp"
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

bool compare_two_music(Music * a, Music * b) {
    return (a -> get_like() > b -> get_like() && a -> get_id() < b -> get_id());
}
