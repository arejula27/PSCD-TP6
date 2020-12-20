#include "Tupla.hpp"
using namespace std;
int main(int argc, char* argv[]) {
    
    Tupla t3("aprieta","el","pan","45","34","88");
    Tupla t4("aprieta","el","pan","45","34","88");
    cout << t3.to_string();
    cout << t4.to_string();
    cout << t3.match(t4);
    Tupla t5(t4);
    t3.from_string("[a,b,c,45,34,pan]");
    cout << t3.to_string();
    cout << t3.match(t4);
}