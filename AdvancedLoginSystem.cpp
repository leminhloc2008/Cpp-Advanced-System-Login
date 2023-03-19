#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<dos.h>
#include<dirent.h>
#include<fstream>
#include<iostream>
#include<string>

using namespace std;

//just to change text color, not necessary
void SetColor(int ForgC)
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

int main()
{
    bool login_successful = false;
    long option = 6; 
    long remain = 6;
    string account_name;
    string account_name_login;
    string password;
    string password_login;
    string username;

    SetColor(14);
    cout << "Welcome to my login system, made by LML STUDIO" << endl << "[Press 1] to sign up" << endl << "[Press 2] to login" << endl << "[Press 3] if you forgot your account password" << endl;
    cout << "Your Option: ";
    cin >> option; // Program checks for input after printing out some stuff.
                   // this input is then put into the variable "option".
    // If option after input evaluates to '1'
    if (option == 1)
    {
        // System is set to color 11
        SetColor(11);
        cout << "Create an user name: "; // Asks for username input and 
        cin >> account_name;            // this input is then stored in 'account_name'

        ifstream tester;
        tester.open("user_" + account_name + ".txt");
        if (tester.fail()){
            cout << endl;                  // skip line after getting input and
            cout << "Create a password: ";// asks for password input.
            cin >> password;             // next input is then stored in a variable called 'password'
            cout << endl;               // skip line after getting second input and 

            ofstream user_info;                               // calls the ofstream file manager initializer
            user_info.open("user_" + account_name + ".txt"); // the initializer is then opened into a new file
            user_info << account_name << endl << password;  // then, account name and password is inserted in the file
            user_info.close();    
                                    // file is then closed after operations is done.
        } else {
            SetColor(30);
            cout << "Failed: Username already in use!" << endl << endl;
            main();
        }

        SetColor(10);                                 // system color is then set to 10
        cout << "Your account has been saved!" << endl << endl; 
        main(); // main function is called to wait for second input, this works in a recursive manner.
    }
    else if (option == 2)
    {
        do
        {
            SetColor(9);
            cout << "----------LOGIN-----------" << endl;
            cout << "Now, log in your account" << endl;
            SetColor(11);
            cout << endl << "Type in your account name: ";
            cin >> account_name_login;
            cout << endl << "Type in your password: ";
            cin >> password_login;
            ifstream find_account("user_" + account_name_login + ".txt");
            getline(find_account, account_name);
            getline(find_account, password);
            if (account_name_login == account_name && password_login == password)
            {
                SetColor(2);
                cout << endl << "You have logged in successfully!" << endl << endl;
                login_successful = true;
                main();
            }
            else
            {
                SetColor(4);
                cout << endl << "Invaild username or password" << endl << "You have " 
                << remain << " times left to try!" << endl << "Please try again!" << endl;
                remain--;
                login_successful = false;
            }
        } 
        while (!login_successful && remain != 0);
        if (remain == 0)
        {
            SetColor(12);
            cout << "You have 0 times left to try" << endl << "The program will now exit";
            Sleep(5);
            return 0;
        }
    }
    else if (option == 3)
    {
        SetColor(6);
        cout << "Type in your username: ";
        cin >> username;
        ifstream find_account("user_" + username + ".txt");
        if (find_account.is_open())
        {
            getline(find_account, account_name);
            getline(find_account, password);
            cout << "Your password is: " << password << endl << endl;
        }
        else
        {
            cout << "Sorry,we couldn't find your account!" << endl << endl;
        }
        main();
    }
    return 0;
}
