//*****************************************************************
// File:   Tupla.cpp
// Author: PSCD-Unizar
// Date:   noviembre 2020
// Coms:
//*****************************************************************

#include <vector>
#include <string>
#include <cassert>
#include <string.h>
#include <Tupla.hpp>

Tupla::Tupla(int n) {
    data = new vector<string>(n,"");
}

Tupla::Tupla(string s1) {
    data = new vector<string>(1,s1);
}

Tupla::Tupla(string s1, string s2) {
    data = new vector<string>(2,"");
    data->at(0) = s1;
    data->at(1) = s2;
    //alternativamente se podía haber hecho como
    //data = new vector<string>{s1,s2};
}

Tupla::Tupla(string s1, string s2, string s3) {
    data = new vector<string>(3,"");
    data->at(0) = s1;
    data->at(1) = s2;
    data->at(2) = s3;
}

Tupla::Tupla(string s1, string s2, string s3, string s4) {
    data = new vector<string>(4,"");
    data->at(0) = s1;
    data->at(1) = s2;
    data->at(2) = s3;
    data->at(3) = s4;
}

Tupla::Tupla(string s1, string s2, string s3, string s4, string s5) {
    data = new vector<string>(5,"");
    data->at(0) = s1;
    data->at(1) = s2;
    data->at(2) = s3;
    data->at(3) = s4;
    data->at(4) = s5;
}

Tupla::Tupla(string s1, string s2, string s3, string s4, string s5, string s6) {
    data = new vector<string>(6,"");
    data->at(0) = s1;
    data->at(1) = s2;
    data->at(2) = s3;
    data->at(3) = s4;
    data->at(4) = s5;
    data->at(5) = s6;
}

Tupla::Tupla(Tupla& t) {
    //TODO
    //ESTO NO FUNCIONA!!!!!!!!!!!!!!
    int max=t.size();
    int i=0;
    while(i<max){
        set(i,t.get(i));
    }
}

Tupla::~Tupla() {
    delete data;
}

int Tupla::size() {
    return data->size();
}

string Tupla::to_string() {
    string res = "[";
    for (int i=0; i<data->size()-1; i++) {
        res = res + data->at(i) + ",";
    }
    res = res + data->at(data->size()-1) + "]";
    return res;
}

string Tupla::get(int pos) {
    return data->at(pos);
}

void Tupla::set(int pos, string value) {
    data->at(pos) = value;
}

void Tupla::from_string(string s) {
    assert(s.length()>2 && s[0]=='[' && s[s.size()-1]==']');
    int n = s.length(); 
    char c[n + 1];
    // string to char array
    strcpy(c, s.c_str());
    char *token = strtok(c, "[,]");
    int i=0;
    while(token!=NULL){
        data->at(i)=token;
        token = strtok(NULL, "[,]"); 
        i++;
    }
}

bool Tupla::match(Tupla& p) {
    bool igual=true;
    int tam=size();
    if(tam==p.size()){
        int i=0;
        while(i<tam && igual){
            if(get(i)!=p.get(i)) igual=false;
            i++;
        }
    }
    else igual=false;
    return igual;
}
