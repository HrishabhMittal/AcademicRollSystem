#include "header.h"
#define assert(a) if (!a) exit(1)
void parseCSV(string filename,vector<vector<string>>& dat) {
    dat={{}};
    int ind=0;
    ifstream file(filename);
        if (!file.good()) {
            dat={};
            return;
        }
        string line;
        while (!file.eof()) {
            getline(file,line);
            string temp;
            for (char i:line) {
                if (i!=',') temp+=i;
                else {
                    dat[ind].push_back(temp);
                    temp="";
                }
            }
            dat[ind].push_back(temp);
            dat.push_back({});
            ind++;
        }
        dat.pop_back();
    file.close();
}
void writeCSV(string filename,vector<vector<string>>& dat) {
    ofstream file(filename);
        int ind=0;
        for (vector i:dat) {
            string s;
            for (string j:i) {
                s+=j+',';
            }
            s.pop_back();
            if (ind<dat.size()-1) file << s << endl;
            else file<<s;
            ind++;
        }
    file.close();
}