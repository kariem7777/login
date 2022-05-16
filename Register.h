
#ifndef NEW_FOLDER__4__REGISTER_H
#define NEW_FOLDER__4__REGISTER_H
#include <string>
using namespace  std;

string input;
fstream file;

struct user{
    string ID,username,email,password,mobile;
};

map <string, user> users_info;
user new_user;
int attemps,counter=-1;

void loadData(map <string, user> &users_info);
void RegisterUser();
bool login();
void change_password();
string validId();
string validusername();
string validemail();
string validmobile();
string validpass();
void Password();
string hidepass();
char keyword_line(string keyword);

string encrypt_decrypt(string text);
#endif //NEW_FOLDER__4__REGISTER_H


