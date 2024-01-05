#ifndef CLIENT_HPP_INCLUDE
#define CLIENT_HPP_INCLUDE
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
    virtual vector<int> get_following(){return follow_id;}
    virtual void follow(int _id){follow_id.push_back(_id);}
    virtual void set_following(vector<int> _follow_id){follow_id = _follow_id;}
    virtual vector<int> get_follower(){return follower_id;}
    virtual void follower(int _id){follower_id.push_back(_id);}
    virtual void set_follower(vector<int> _follower_id){follower_id = _follower_id;}
    protected: int id;
    string username;
    string password;
    string mode;
    vector<int> follow_id;
    vector<int> follower_id;
};

Client::Client() {
    username = " ";
    password = " ";
    mode = "";
    int id = -1;
}
#endif
