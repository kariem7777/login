#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include "Register.cpp"
#include <map>

using namespace std;


int main() {
    int choice;
  while (true){
    loadData(users_info);
    attemps=0;
    cout<<"(1) Register\n(2) Login\n(3)Change Password\n(4) Exit\nchoose from the menu: ";
    cin>>choice;
    if (choice ==1){
        RegisterUser();

    }else if(choice ==2){
        if(login()==true){
            cout<<endl<<"login success"<<endl;

        }else{
            cout<<endl<<"login failed"<<endl;
        }

    }else if(choice==3){
        if(login()){
        change_password();
        cout<<"password changed"<<endl;
        }else{
            cout<<"failed to login"<<endl;
        }
    }else if(choice==4){
      break;
    }
  }
  return 0;
}
