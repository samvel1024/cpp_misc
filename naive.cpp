#include <iostream>
#include <vector>
#include <climits>
#include <set>

#ifdef DEBUG
const bool debug = true;
#define DBG(x) x

void init() {
    freopen("../std.in", "r", stdin);
}

#else
const bool debug = false;
#define DBG(x)
void init(){}
#endif


using namespace std;

using point = pair<int, int>;

int n;
vector<point> points;
vector<int> dist(n, INT_MAX);


int cost(int i, int j) {
    int dx = abs(points[i].first - points[j].first);
    int dy = abs(points[i].second - points[j].second);
    return min(dx, dy);
}

struct compare {
    bool operator()(const int &lhs, const int &rhs) {
        return dist[lhs] < dist[rhs];
    }
};


int main() {
    init();
    {
        cin >> n;
        points.reserve(n);
        int a, b;
        for (int i = 0; i < n; ++i) {
            cin >> a >> b;
            points.emplace_back(a, b);
        }
    }

    {
        vector<int> d(n, INT_MAX), p(n);
        d[0] = 0;
        set<pair<int, int> > q;
        q.insert(make_pair(d[0], 0));
        while (!q.empty()) {
            int v = q.begin()->second;
            q.erase(q.begin());

            for (int j = 0; j < n; ++j) {
                int to = j,
                    len = cost(j, v);
                if (d[v] + len < d[to]) {
                    q.erase(make_pair(d[to], to));
                    d[to] = d[v] + len;
                    p[to] = v;
                    q.insert(make_pair(d[to], to));
                }
            }
        }
        cout << d[n-1];

    }

}