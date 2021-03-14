#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<dos.h>
#include<dir.h>
#include<fstream>
#include<bits/stdc++.h>

using namespace std;

void SetColor(int ForgC)
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

int main()
{
    bool login_successful=false;
    long long option,remain=5;
    string account_name,account_name_login,password,password_login,username;
    SetColor(14);
    cout<<"Welcome to my login system, made by LML STUDIO"<<endl<<"[Press 1] to sign up"<<endl<<"[Press 2] to login"<<endl<<"[Press 3] if you forgot your account password"<<endl;
    cout<<"Your Option: ";
    cin>>option;
    if(option==1)
    {
        SetColor(11);
        cout<<"Create an user name: ";
        cin>>account_name;
        cout<<endl;
        cout<<"Create a password: ";
        cin>>password;
        cout<<endl;
        ofstream user_info;
        user_info.open("user_"+account_name+".txt");
        user_info<<account_name<<endl<<password;
        user_info.close();
        SetColor(10);
        cout<<"Your account has been saved!"<<endl<<endl;
        main();
    }
    else if(option==2)
    {
      do
        {
            SetColor(9);
            cout<<"----------LOGIN-----------"<<endl;
            cout<<"Now, log in your account"<<endl;
            SetColor(11);
            cout<<endl<<"Type in your account name: ";
            cin>>account_name_login;
            cout<<endl<<"Type in your password: ";
            cin>>password_login;
            ifstream find_account("user_"+account_name_login+".txt");
            getline(find_account,account_name);
            getline(find_account,password);
            if(account_name_login==account_name&&password_login==password)
            {
                SetColor(2);
                cout<<endl<<"You have logged in successfully!"<<endl<<endl;
                login_successful=true;
                main();
            }
            else
            {
                SetColor(4);
                cout<<endl<<"Invaild username or password"<<endl<<"You have "<<remain<<" times left to try!"<<endl<<"Please try again!"<<endl;
                remain--;
                login_successful=false;
            }
        }
        while(!login_successful&&remain!=-1);
        if(remain==-1)
        {
            SetColor(12);
            cout<<"You have 0 times left to try"<<endl<<"The program will now exit";
            Sleep(1);
            return 0;
        }
    }
    else if(option==3)
    {
        SetColor(6);
        cout<<"Type in your username: ";
        cin>>username;
        ifstream find_account("user_"+username+".txt");
        if(find_account.is_open())
        {
            getline(find_account,account_name);
            getline(find_account,password);
            cout<<"Your password is: "<<password<<endl<<endl;
        }
        else
        {
            cout<<"Sorry,we couldn't find your account!"<<endl<<endl;
        }
        main();
    }
    return 0;
}
//Programed By LML STUDIO
//Page: https://lml-studio.itch.io/
//You can use my code without credit but I'll appreciate if you do
/*Change logs:
  v1.0(05/03/2021): Project Finished
  v2.0(14/03/2021): Added a feature that if the user type the username password wrong 5 times then
  the program wil stop
*/

