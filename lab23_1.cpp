#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string> &names,vector<int> &scores,vector<char> &grades){
ifstream file(filename);
    string text;
    while(getline(file,text)){
        const char *data = text.c_str();
        char format[] = "%[^:]: %d %d %d";
        char name[100];
        int score1,score2,score3;
        sscanf(data,format,name,&score1,&score2,&score3);
        int tatolscore = score1+score2+score3;
        names.push_back(string(name));
        scores.push_back(tatolscore);
        grades.push_back(score2grade(tatolscore));
    }
    file.close();}

void getCommand(string &command, string &key){
cout << "Please input your command: " << endl;
    string input;
    getline(cin,input);
    const char*text = input.c_str();
    char format[] = "%s %[^\n]";
    char c_command[100],c_key[100];
    sscanf(text,format,c_command,c_key);
    command = string(c_command);
    key = string(c_key);


}

void searchName(vector<string> names,vector<int> scores,vector<char> grades,string key){
    bool found = false;
    for(unsigned int i=0;i < names.size();i++){
        if(toUpperStr(names[i]) == key){
            cout << "---------------------------------" << endl;
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            cout << "---------------------------------" << endl;
            found = true;
            break;
        }
    }
    if(found == false){
        cout << "---------------------------------" << endl;
        cout << "Cannot found." << endl;
        cout << "---------------------------------" << endl;
    }
}

void searchGrade(vector<string> names,vector<int> scores,vector<char> grades,string key){
    bool found = false;
    cout << "---------------------------------" << endl;
    for(unsigned int i=0;i < names.size();i++){
        if(grades[i] == key[0]){
            cout << names[i] << " (" << scores[i] << ")"<< endl;
            found = true;
        }
    }
    if(found == false){
        cout << "Cannot found." << endl;
    }
    cout << "---------------------------------" << endl;
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}