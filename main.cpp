#include <iostream>

#ifdef DEBUG
const bool debug = true;
#define DBG(x) x

void *init() {
    return freopen("../std.in", "r", stdin);
}

void *___p_t_r = init();
#else
const bool debug = false;
#define DBG(x)
void init(){}
#endif


using namespace std;

int main() {
    cerr << "Hello world";
    return 0;
}


