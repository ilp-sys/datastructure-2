#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char* argv[]){

    //set vector from 1 to 5
    vector<int> v1;
    for(int i = 1; i <= 5; i++)
        v1.push_back(i);

    //print vector item using iterator
    //begin(): return first iterator
    //v1.end(): return iterator in next of last item
    for(auto i = v1.begin(); i != v1.end(); ++i)
        cout << *i << " ";

    //print reversely
    //rbegin(), rend() -> return revesed iterator
    cout << endl;
    for(auto ir = v1.rbegin(); ir != v1.rend(); ++ir)
        cout << *ir << " ";

    //print vector in a manner of array
    cout << endl;
    for(int i = 0; i < v1.size(); i++)
        cout << v1[i] << " ";

    //print vector item using .at(index)
    cout << endl;
    for(int i = 0; i < v1.size(); i++)
        cout << v1.at(i) << " ";

    cout << endl;
    return 0;
}

