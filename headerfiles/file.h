#pragma once
#include "iostream"
#include "string"
class file{
private:
    std::string* f;
    int l = 0;
    int maxLines = 100;
    int r = 0;
public:
    file(){
        f = new std::string[maxLines];
    }

    void expandStorage(){
        maxLines *=2;
        std::string* temp = new std::string[maxLines];
        for(int i = 0; i < maxLines/2; i++){
            temp[i] = f[i];
        }
        delete[] f;
        f = temp;
    }

    void addline(std::string line){
        if(l>=maxLines){
            expandStorage();
        }
        f[l] = line;
        l++;
    };

    int getlinecount(){
        return l;
    }

    std::string getline(int i){
        r = 0;
            return f[i];
        if(i < l && l >= 0){
        }
        std::cout << "ERROR: line out of range";
        exit(0);
    }

    std::string addtoline(int line, int c, std::string addition){
        if(addition == "\n"){
            if(l>=maxLines){
                expandStorage();
            }
            for(int i = l; i > line; i--)   {
                f[i+1] = f[i];
            }
            f[line+1] = f[line].substr(c+r);
            f[line] = f[line].substr(0,c+r);
            r++;
            l++;
            return getline(line);
        }
        if(c +r < (int)f[line].length()){
            f[line] = f[line].substr(0,c+r) + addition + "" + f[line].substr(c+r);
            r++;
        }
        if(c+r >= (int)f[line].length()){
            f[line] += addition;
        }
        return getline(line);
    }

    std::string removefromline(int i, int c, int l = 1){
        if(c == 0){
            f[i] = f[i].substr(1);
        }
        else if(c+r < (int)f[i].length()){
            f[i] = f[i].substr(0,c) + "" + f[i].substr(c+l);
            r--;
        }
        return getline(i);
    }

    void reset(){
        delete[] f;
    }

    void addline(int lineNumber) {
        if(lineNumber>=l) return void();
        if(l>=maxLines){
            expandStorage();
        }     
        for(int i = l; i > lineNumber; i--)   {
            f[i+1] = f[i];
        }
        f[lineNumber] = "";
        std::cout << this->getline(0) << std::endl;
        /*if(l>=maxLines){
            expandStorage();
        }
        f[l] = line;
        l++;*/
    }
};
