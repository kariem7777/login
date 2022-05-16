#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <conio.h>
#include "Register.h"

using namespace std;



void RegisterUser(){


    file.open("users.txt",ios::app);
    cout<<"enter the ID: ";
    new_user.ID=validId();

    cout<<"enter the Username: ";
    new_user.username=validusername();

    cout<<"enter the e-mail: ";
    new_user.email=validemail();

    cout<<"enter the mobile: ";
    new_user.mobile=validmobile();

    Password();


    file.close();
}

string validId(){
    regex goodID ("[0-9]{8}");
    cin.clear();
    cin.sync();
    here:
    getline(cin,input);
    for(auto i:users_info){
        if(i.first==input){
            cout<<"ID is taken, enter another ID: ";
            goto here;
        }
    }
    while(!regex_match(input,goodID)){
        cout<<"please enter only 8 numbers: ";
        goto here;
    }
    return input;
}

string validusername(){
    regex username("[a-zA-Z-]*");
    getline(cin,input);
    while(!regex_match(input,username)){
        cout<<"please enter only letters or (-): ";
        getline(cin,input);
    }
    return input;
}

string validemail(){
    regex email("[a-zA-Z0-9!#$'+*_/=?.{}|~-]*[@](gmail|yahoo|hotmail)[.](com|net|eg)");
    here:
    getline(cin,input);
    for(auto i:users_info){
        if(i.second.email==input){
            cout<<"e-mail is already exists, enter another e-mail: ";
            goto here;
        }
    }
    while(!regex_match(input,email) || (input.length()>64) || (input[0]=='.')||(input[input.length()-1]=='.')){
        cout<<"please enter a valid e-mail format (john@gmail.com): ";
        goto here;
    }
    return input;
}

string validmobile(){
    regex mobile ("[0][1][0125][0-9]{8}");
    getline(cin,input);
    while(!regex_match(input,mobile)){
        cout<<"invalid mobile number\nplease enter a valid number: ";
        getline(cin,input);
    }
    return input;
}


void Password(){
    string password,confirmpass,KeyWordLine;
    cout<<"(at least 8 characters mixture of upper ,lower letters ,numbers and at least 1 special character)"<<endl;
    start:
    cout<<"enter the password: ";
    password=validpass();
    cout <<"confirm password: ";
    confirmpass=validpass();
    if(password!=confirmpass){
        cout<<"\npassword does not match"<<endl;
        goto start;
    }else{
        cout<<"\npassword matched."<<endl;

        password=encrypt_decrypt(password);
        new_user.password=password;
        file<<new_user.ID<<endl;
        file<<new_user.username<<endl;
        file<<new_user.email<<endl;
        file<<new_user.mobile<<endl;
        file<<new_user.password<<endl;
    }

}


string validpass(){
    input=hidepass();
    regex Validpass("(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[!@?#$%_.,-])[a-zA-Z0-9!@?#$%_.,-]{8,}");
    while(!regex_match(input,Validpass) || (input.length()<8)){
        cout<<"\nnot a strong password(at least 8 characters mixture of upper and lower letters and numbers and at least 1 special"
              "character)"<<endl<<"please enter a strong password: ";
        input=hidepass();
    }
    return input;
}


string hidepass(){
    string pass;
    char ch;
    ch=getch();
    while(ch !='\r'){
        if(ch =='\b' && pass.length()!=0){
            cout<<"\b \b";
            pass.pop_back();
        }else if(ch !='\b'){
            pass.push_back(ch);
            cout<<"*";
        }
        ch=getch();
    }
    return pass;
}


void loadData(map <string, user> &users_info){
    string KeyWordLine;
    user temp;
    users_info.clear();
    file.open("users.txt",ios::app);
    file.close();
    file.open("users.txt",ios::in);
    while(getline(file,temp.ID)){
      getline(file,temp.username);
      getline(file,temp.email);
      getline(file,temp.mobile);
      getline(file,temp.password);

      temp.password=encrypt_decrypt(temp.password);
      users_info.emplace(temp.ID,temp);
    }
    file.close();
}

bool login() {
  int ID=0;
  cin.clear();
  cin.sync();
  beginng:
  cout<<"enter your ID: ";
  getline(cin,input);
  for(auto i:users_info){
    if (i.first==input){
      ++ID;
      new_user.ID=input;
      start:
        if(attemps==3){
            return false;
        }
        cout<<"enter your password: ";
        input=hidepass();
        if(i.second.password==input){
            return true;
        }else{
            cout<<endl<<"wrong Password"<<endl;
            ++attemps;
            goto start;
        }
    }
  }
  if (ID==0){
    cout<<endl<<"ID Not Found"<<endl;
    goto beginng;
  }
}

void change_password(){
    cin.clear();
    cin.sync();
    file.open("temp.txt",ios::app);
    for (auto i: users_info){
        if (new_user.ID==i.first){
            new_user.username=i.second.username;
            new_user.email=i.second.email;
            new_user.mobile=i.second.mobile;
            Password();
            continue;
        }else{
            file<<i.second.ID<<endl;
            file<<i.second.username<<endl;
            file<<i.second.email<<endl;
            file<<i.second.mobile<<endl;
            file<<i.second.password<<endl;
        }
    }
    file.close();
    remove("users.txt");
    rename("temp.txt","users.txt");
}

string encrypt_decrypt(string text){
    string nwpass="";
    for (int n=0 ; n<text.length() ; n++)
        {
            char newtext ;
            if (text[n] != ' ')
            {
                if (isupper(text[n]))
                {
                    newtext = 'Z'- (text[n]-'A') ;
                    nwpass+= newtext ;
                }
                else
                {
                    newtext = 'z'- (text[n]-'a') ;
                    nwpass+= newtext ;
                }
            }
            else
            {
                newtext =' ' ;
                nwpass+= newtext ;
            }
        }
        return nwpass;
    }
