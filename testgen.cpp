#include <ctime>
#include <random>
#include <sys/time.h>
#include <iostream>
using namespace std;

int main(){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    unsigned long time_in_micros = 1000000 * tv.tv_sec + tv.tv_usec;

    srand(time_in_micros);

    int n;
    cin >> n;
    int lim;
    cin >> lim;
    cout << n << endl;
    for(int i=0; i<n; ++i){
        cout << rand() % lim << " " << rand() % lim << endl;
    }
    return 0;

}