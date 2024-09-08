#include "csv.cpp"

// checking credentials

bool isAdmin(string id,string username,string password) {
    vector<vector<string>> dat;
    parseCSV("data/admins",dat);
    for (vector i:dat) {
        if (i[0]==id && i[1]==username && i[2]==password) {
            return true;
        }
    }
    return false;
}
bool isUser(string id,string username,string password) {
    vector<vector<string>> dat;
    parseCSV("data/users",dat);
    for (vector i:dat) {
        if (i[0]==id && i[1]==username && i[2]==password) {
            return true;
        }
    }
    return false;
}

// useful functions

int indexOf(vector<string> v,string s) {
    for (int i=0;i<v.size();i++) {
        if (v[i]==s) return i;
    }
    return -1;
}
string getSemFile(int i) {
    string name="./data/semesters/";
    name+=(char)(i+'0');
    return name;
}
int initSem(int i) {
    if (i<=0) return 0;
    string name=getSemFile(i);
    vector<vector<string>> data;
    parseCSV(name,data);
    if (data.size()==0 || data[0].size()<2) {
        data={};
        cout << "this is a new semester!\nplease add new subjects: " << endl;
        vector<string> head{"S.no.","Name","Rollno."};
        string instr;
        for (;;) {
            cout << "enter subject name: ";
            cin>>instr;
            head.push_back(instr);
            cout << "continue?(y/n)";
            cin >> instr;
            if (instr=="y" || instr=="yes");
            else break;
        }
        data.push_back(head);
        cout << "add all students from previous semester?(y/n)" << endl;
        char yn;
        cin >> yn;
        if (yn=='y') {
            if (i<=1) {
                cout << "there is no previous semester. add from user list?(y/n)" << endl;
                cin >> yn;
                if (yn) {
                    vector<vector<string>> dat2;
                    parseCSV("./data/users",dat2);
                    for (int i=0;i<dat2.size();i++) {
                        data.push_back(vector<string>(head.size(),""));
                        data[i+1][0]=to_string(i+1);
                        data[i+1][1]=dat2[i][1];
                        data[i+1][2]=dat2[i][0];
                    }
                }
            }
            else {
                vector<vector<string>> dat2;
                parseCSV(((string)("./data/semesters/"))+((char)(i-1+'0')),dat2);
                for (int i=1;i<dat2.size();i++) {
                    data.push_back(vector<string>(head.size(),""));
                    data[i][0]=dat2[i][0];
                    data[i][1]=dat2[i][1];
                    data[i][2]=dat2[i][2];
                }
            }
        }

        writeCSV(name,data);
    }
    return 1;
}
