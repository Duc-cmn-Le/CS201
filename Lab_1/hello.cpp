#include <iostream>
#define debun(x) cout << x << endl

using namespace std;

unsigned float_abs(unsigned uf) {
    unsigned minNan = 0x7f800001;
    unsigned res = uf & 0x7fffffff;
    if (res >= minNan)
        return uf;
    else
        return res;
}

int main() {
    unsigned uf;
//    cin >> uf;
    unsigned minNan = 0x7f800001;
    unsigned res = uf & 0x7fffffff;

    cout << minNan;
    /*
    cout <<"Hello ";
    if (res >= minNan)
        cout << uf << endl;
    else
        cout << res << endl;
        */
    return 0;
}
