#include <iostream>
#include <vector>
#include <set>
#include <climits>

#ifdef INPUTFILE

void *__h_c_t() {
    return freopen(INPUTFILE, "r", stdin);
}

void *___i_k_ct = __h_c_t();
#endif
#ifdef DEBUG
const bool debug = true;
#define DBG(x) x
#else
const bool debug = false;
#define DBG(x)
#endif


using namespace std;


class point {
public:
    int x, y;
    int cost = INT_MAX;

    point(int x, int y) : x(x), y(y) {}

    point(const point &p) = default;

    bool operator==(const point &rhs) const {
        return x == rhs.x &&
               y == rhs.y;
    }

    bool operator!=(const point &rhs) const {
        return !(rhs == *this);
    }

    friend ostream &operator<<(ostream &os, const point &point1) {
        os << "P{x: " << point1.x << " y: " << point1.y << " cost: " << point1.cost << "}";
        return os;
    }
};


vector<point> points;


struct ByX {
    bool operator()(const int &i, const int &j) {
        auto &l = points[i];
        auto &r = points[j];
        return l.x == r.x ? l.y < r.y : l.x < r.x;
    }
};


struct ByY {
    bool operator()(const int &i, const int &j) {
        auto &l = points[i];
        auto &r = points[j];
        return l.y == r.y ? l.x < r.x : l.y < r.y;
    }
};

int dist(int i, int j) {
    auto &l = points[i];
    auto &r = points[j];
    return min(abs(l.x - r.x), abs(l.y - r.y));
}


set<int, ByX> x_set;
set<int, ByY> y_set;
constexpr int JPU = 2000;
vector<int> temp;

#define ADD_IF_NOT_END(x, s) if (x != s.end()) temp.push_back(*x);

template<typename S>
void add_iter(typename S::iterator it, S &set) {
    if (it == set.end()) {
        if (!set.empty())
            ADD_IF_NOT_END(--it, set);
    } else if (it == set.begin()) {
        ADD_IF_NOT_END(it, set);
        ADD_IF_NOT_END(++it, set);
    } else {
        ADD_IF_NOT_END(it, set);
        ADD_IF_NOT_END(++it, set);
        ADD_IF_NOT_END(--it, set);
    }
}


template<typename Set>
void relax(Set &s, int curr_index) {
    int curr_cost = points[curr_index].cost;
    for (auto it = s.begin(); it != s.end(); it++) {
        if (*it == curr_index) continue;
        DBG(cout << "relaxing2 " << *it << endl);
        points[*it].cost = min(points[*it].cost, curr_cost + dist(*it, curr_index));
    }
}


template<typename S>
void add_between(typename S::iterator from, typename S::iterator to, S &set) {
    if (from != set.begin())
        from--;
    for (auto i = from; i != set.end(); ++i) {
        temp.push_back(*i);
        if (i == to) break;
    }
}

int next(int curr) {
    add_between(x_set.lower_bound(curr), x_set.upper_bound(curr), x_set);
    add_between(y_set.lower_bound(curr), y_set.upper_bound(curr), y_set);
    int cost = INT_MAX;
    int ans = curr;
    for (auto i: temp) {
        int d = dist(i, curr);
        if (d <= cost && i != curr) {
            cost = d;
            ans = i;
        }
    }
    temp.clear();
    return ans;
}

void print_costs() {
    for (int i = 0; i < points.size(); ++i) {
        DBG(cout << points[i] << endl);
    }
}

template<typename S>
void print_set(S &s) {
    for (auto it = s.begin(); it != s.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

int main() {
    int n;
    {
        int a, b;
        cin >> n;
        points.reserve(n);
        for (int i = 0; i < n; ++i) {
            cin >> a >> b;
            const int j = i;
            if (i == n - 1 || (x_set.find(j) == x_set.end() && y_set.find(j) == y_set.end())) {
                points.emplace_back(a, b);
                x_set.insert(i);
                y_set.insert(i);
            }
        }
    }
    {

        if (points[0] == points[n - 1]) {
            cout << 0;
            return 0;
        }
        points[0].cost = 0;
        int curr_index = 0;
        int JPU_INDEX = 1000;
        while (curr_index != n - 1) {
            DBG(cout << "curr_index = " << curr_index << " curr_point=" << points[curr_index] << endl);
            relax(x_set, curr_index);
            relax(y_set, curr_index);
            DBG(cout << "before X=");
            DBG(print_set(x_set));
            DBG(cout << "before Y=");
            DBG(print_set(y_set));
            x_set.erase(x_set.find(curr_index));
            y_set.erase(y_set.find(curr_index));

            DBG(cout << "after X=");
            DBG(print_set(x_set));
            DBG(cout << "after Y=");
            DBG(print_set(y_set));

            curr_index = next(curr_index);
            DBG(print_costs());
        }
        cout << points[curr_index].cost;
    }

}


