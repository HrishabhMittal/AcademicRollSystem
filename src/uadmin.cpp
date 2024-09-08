#include "edit.cpp"

// support functions

bool to_number(string num,double& out) {
    if (num.size()==0) return false;
    out=0.0;
    double decimal=1.0;
    int sign=1,dot=0;
    int ii=0;
    if (num[0]=='+') ii++;
    else if (num[0]=='-') {
        ii++;
        sign=-1;
    }
    for (int ii=0;ii<num.size();ii++) {
        char i=num[ii];
        if (i=='.') {
            if (dot) return false;
            dot=1;
            continue;
        }
        int dig=i-'0';
        if (dig>=0 && dig<10) {
            if (out) decimal*=10.0;
            out=out*10.0+(double)dig;
        } else return false;
    }
    out/=decimal;
    return true;
}
template<typename T>
void splice(vector<T>& vec,int index,int number=0,vector<T> elements={}) {
    vector<T> newvec;
    if (index>vec.size()) index=vec.size();
    for (int i=0;i<index;i++) {
        newvec.push_back(vec[i]);
    }
    for (T i:elements) {
        newvec.push_back(i);
    }
    for (int i=index+number;i<vec.size();i++) {
        newvec.push_back(vec[i]);
    }
    vec=newvec;
}
void display(vector<vector<string>>& data) {
    vector<int> size(data[0].size(),0);
    for (vector i:data) {
        for (int jj=0;jj<i.size();jj++) {
            string j=i[jj];
            if (j.size()>size[jj]) {
                size[jj]=j.size();
            }
        }
    }
    string sep="+";
    for (int i:size) {
        for (int j=-2;j<i;j++) {
            sep+='-';
        }
        sep+="+";
    }
    cout << sep << endl;
    for (vector i:data) {
        cout << "| ";
        int ii=0;
        for (string j:i) {
            cout << j;
            for (int k=j.size();k<size[ii];k++) {
                cout << " ";
            }
            cout << " | ";
            ii++;
        }
        cout << endl << sep << endl;
    }
}
string grade(double d) {
    // d is out of 4
    d*=2.5;
    if (d==10.0) return "AP";
    if (d>9.0) return "AA";
    if (d>8.0) return "AB";
    if (d>7.0) return "BB";
    if (d>6.0) return "BC";
    if (d>5.0) return "CC";
    if (d>4.0) return "CD";
    if (d>0.0) return "DD";
    if (d==0.0) return "FR";
    return "none"; 
}
double SPI(int sem,string roll,int& numOfSubs) {
    vector<vector<string>> dat;
    parseCSV(getSemFile(sem),dat);
    numOfSubs=dat[0].size()-3;
    for (vector i:dat) {
        if (i[2]==roll) {
            double total=0.0;
            for (int j=3;j<i.size();j++) {
                double credits;
                to_number(i[j],credits);
                total+=credits;
            }
            total/=(double)(i.size()-3);
            total*=2.5;
            return total;
        }
    }
    return 0.0;
}
double CPI(int sem,string roll) {
    double total=0.0;
    int sub;
    int num=0;
    for (int i=1;i<=sem;i++) {
        double n=SPI(sem,roll,sub);
        n*=(double)sub;
        total+=n;
        num+=sub;
    }
    return total/(double)num;
}

// admin/user

void admin(vector<vector<string>>& data,string filename) {
    cout << "the following are valid commands\n"
            "1.> display: display the table\n"
            "2.> delete: delete entire table and all entries\n"
            "3.> remove <number>: remove the record at index <number>\n"
            "4.> add <number>: add a new (empty/filled asked) record at index <number>\n"
            "5.> add-sub <name>: add a new subject\n"
            "6.> rem-sub <name>: remove a subject\n"
            "7.> edit <number> <name> <value>: edit record to <value> of S.no. <number> and for subject <name>\n"
            "8.> check: checks if all rollno. are integers, and marks are decimal no. and less than 4 credits,\n"
            "           replaces invalid credit records with 0, and deletes invalid rollno. records\n"
            "9.> exit: exits, asks if changes made should be saved" << endl;
    for (;;) {
        string s;
        cout << "enter command: " << endl;
        cin >> s;
        if (s=="display") {
            display(data);
        } else if (s=="remove") {
            int i;
            cin >> i;
            if (i<=0 || i >=data.size()) cout << "provide a valid S.no." << endl;
            else {
                splice(data,i,1);
                for (int j=1;j<data.size();j++) {
                    data[j][0]=to_string(j);
                }
            }
        } else if (s=="check") {
            for (int i=1;i<data.size();i++) {
                try {stoi(data[i][2]);} catch (std::invalid_argument) {
                    splice(data,i,1);
                    for (int j=1;j<data.size();j++) {
                        data[j][0]=to_string(j);
                    }
                }
                double num;
                for (int j=3;j<data[i].size();j++) {
                    if (!to_number(data[i][j],num) || num>4.0 || num<0.0)
                        data[i][j]="0.0";
                }
            }
        } else if (s=="delete") {
            data={};
        } else if (s=="add") {
            int i;
            cin >> i;
            if (i>data.size()) i=data.size();
            splice(data,i,0,{vector<string>(data[0].size(),"")});
            for (int j=i;j<data.size();j++) {
                data[j][0]=to_string(j);
            }
            cout << "do you want to fill details in the record?(y/n)";
            char c;
            cin>>c;
            if (c=='y' || c=='Y') {
                for (int j=1;j<data[i].size();j++) {
                    cout << "enter " << data[0][j];
                    if (j>2) cout << " marks";
                    cout << ":"<< endl;
                    cin>>data[i][j];
                }
            }
        } else if (s=="add-sub") {
            cin >>s;
            data[0].push_back(s);
            for (int i=1;i<data.size();i++) {
                data[i].push_back("");
            }
        } else if (s=="rem-sub") {
            cin>>s;
            int i=indexOf(data[0],s);
            if (i==-1) {
                cout << "invalid subject" << endl;
                continue;
            }
            for (int j=0;j<data.size();j++) {
                splice(data[j],i,1);
            }
        } else if (s=="edit") {
            int i,j;
            cin >> i;
            cin >> s;
            j=indexOf(data[0],s);
            cin >> s;
            if (j!=-1 && i>0 && i<data.size()) {
                data[i][j]=s;
            }
        } else if (s=="exit") {
            cout << "save all changes? (y/n)" << endl;
            cin >> s;
            if (s[0]=='y' || s[0]=='Y') {
                writeCSV(filename,data);
            }
            return;
        } else {
            cout << "there is no such command!" << endl;
        }
    }
}
void user(string uname) {
    vector<vector<string>> dat;
    cout << "enter sem:";
    int sem;
    cin >> sem;
    parseCSV(getSemFile(sem),dat);
    for (vector i:dat) {
        if (i[1]==uname) {
            cout << endl << "YOUR RESULT:" << endl << endl;
            cout << "Name: " << uname << endl;
            cout << "Roll no. " << i[2] << endl << endl;
            double total=0.0;
            for (int j=3;j<i.size();j++) {
                double credits;
                to_number(i[j],credits);
                cout << dat[0][j] << " marks:" << i[j] << " grade:" << grade(credits) << endl;
                total+=credits;
            }
            total/=(double)(i.size()-3);
            cout << "Overall grade " << grade(total) << endl;
            total*=2.5;
            cout << "SPI = " << total << endl;
            cout << "CPI till this semester = " << CPI(sem,i[2]) << endl;
            return;
        }
    }
    cout << "Your result has not been declared!" << endl;
}