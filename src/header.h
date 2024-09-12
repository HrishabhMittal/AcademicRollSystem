#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

// getch in conio.h doesnt echo 
// for linux turn off echo and take input

#if __has_include(<conio.h>)
#include <conio.h>
int getpass(string& out) {
    out="";
    char c;
    c=getch()
    while(c!='\n' && c!=' ') {
        out+=c;
        c=getch();
    }
    return 1;
}
#else
#include <termios.h>
#include <stdio.h>
int getpass(string& out) {
    out="";
    struct termios old, n;
    int nread;
    if (tcgetattr(fileno(stdin),&old) != 0) return 0;
    n=old;
    n.c_lflag&=~ECHO;
    //set to no echo
    if (tcsetattr(fileno(stdin),TCSAFLUSH,&n) != 0) return 0;
    //input
    cin >> out;
    //reset
    tcsetattr(fileno(stdin),TCSAFLUSH,&old);
    return 1;
}
#endif