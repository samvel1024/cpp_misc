#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
const bool debug = true;
#define ifd(x) x
#define log(x) cout << #x << "=" << x << endl;
#define logc(container) cout << #container << "={ ";    for(auto i : container) cout << i << " ";  ; cout << "}" << endl;

void *init() {
    return freopen("../std.in", "r", stdin);
}

void *___p_t_r = init();
#else
const bool debug = false;
#define ifd(x)
#define log(x)
#define logc(container)
#endif

ostream &operator<<(ostream &os, const pair<int, int> &a) {
    os << "<" << a.first << "," << a.second << ">";
    return os;
}

vector<pair<int, int>> points;
vector<int> cost;

struct cmp {
    bool operator()(const int &l, const int &r) {
        return cost[l] == cost[r] ? l < r : cost[l] < cost[r];
    }
};

set<pair<int, int>> x; // X, index
set<pair<int, int>> y; // Y, index


set<pair<int, int>> q; // cost , index


set<int> find_adjacent_by_axis(int current, int coord, set<pair<int, int>> &s) {
    auto iter = s.find(make_pair(coord, current));
    assert(iter != s.end());
    set<int> ans;
    if (iter != s.begin()) {
        auto prev = iter;
        ans.insert((*(--prev)).second);
    }
    ++iter;
    if (iter != s.end()) {
        ans.insert((*(iter)).second);
    }
    return ans;
}

set<int> find_adjacent(int current) {
    int curr_x, curr_y;
    tie(curr_x, curr_y) = points[current];
    set<int> x = find_adjacent_by_axis(current, curr_x, ::x);
    set<int> y = find_adjacent_by_axis(current, curr_y, ::y);
    x.insert(y.begin(), y.end());
    return x;
}

int dist(int i, int j) {
    auto &a = points[i];
    auto &b = points[j];
    return min(abs(a.first - b.first), abs(a.second - b.second));
}


int main() {
    {
        int a, b, n;
        cin >> n;
        cost.resize(n, INT_MAX); //TODO
        cost[0] = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d %d", &a, &b);
            points.emplace_back(a, b);
            x.emplace(a, i);
            y.emplace(b, i);
            q.emplace(cost[i], i);
            logc(q);
        }
        logc(points);
    }
    {

        while (!q.empty()) {
            int curr = (*q.begin()).second;
            q.erase(q.begin());
            set<int> adjacent = find_adjacent(curr);
            x.erase(make_pair(points[curr].first, curr));
            y.erase(make_pair(points[curr].second, curr));

            ifd(cout << "Adjacency list for " << curr << " ");
            logc(adjacent);
            for (int adj: adjacent) {
                assert(adj != curr);
                int old_cost = cost[adj];
                cost[adj] = min(cost[adj], cost[curr] + dist(curr, adj));
                log(adj);
                ifd(cout << "Relaxed cost for " << adj << " to " << cost[adj] << endl);
                auto itr = q.find(make_pair(old_cost, adj));
                assert(itr != q.end());
                q.erase(itr);
                q.emplace(cost[adj], adj);
            }

            logc(cost);

        }

        cout << cost[points.size() - 1];

    }

    return 0;
}


