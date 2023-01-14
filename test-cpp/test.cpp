#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    vector<string> msg {"Hello","C++","World","from","France"};
    for(const string& word:msg) {
        cout << word << " ";
    }
    cout << endl;
}