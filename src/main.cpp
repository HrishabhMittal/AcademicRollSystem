#include "uadmin.cpp"
int main() {
    cout << "Login as (user/admin):" << endl;
    string strin,uname,pass,id;
    cin >> strin;
    if (strin=="exit") {
        return 0;
    } if (strin!="user" && strin!="admin") {
        cout << "invalid argument!" << endl;
        return 0;
    }
    cout << "enter username:";
    cin>>uname;
    if (strin=="admin") cout << "enter admin id:" << endl;
    else cout << "enter roll no.:" << endl;
    cin >> id; 
    cout << "enter password (hidden):";
    if (!getpass(pass)) {
        cout << "password couldnt be read!" <<endl;
        return 0;
    };
    cout << endl;


    if (strin=="admin" && isAdmin(id,uname,pass)) {
        vector<vector<string>> data;
        for (;;) {
            cout << "enter semester to manage:";
            int i;
            cin >> i;
            initSem(i);
            parseCSV(getSemFile(i),data);
            admin(data,getSemFile(i));
            cout << "continue?(y/n)";
            cin >> strin;
            if (strin!="y") break;
        }
    } else if (strin=="user" && isUser(id,uname,pass)) {
        user(uname);
    }
}