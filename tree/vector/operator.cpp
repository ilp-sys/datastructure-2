#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> v (10);
    vector<int>::size_type sz = v.size();

    for(unsigned i = 0; i < sz; i++) v[i] = i;
    for(unsigned i = 0; i < sz/2; i++){
        int temp;
        temp = v[sz-1-i];
        v[sz-1-i] = v[i];
        v[i] = temp;
    }
    cout << "my vector contains: ";
    for(unsigned i = 0; i <sz; i++)
        cout << " " << v[i];
    cout << "\n";

    return 0;
}
