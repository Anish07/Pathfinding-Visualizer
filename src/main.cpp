
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <cmath>
#include <string>

struct Node { int r, c; };

struct NodeHash {
    size_t operator()(const Node& n) const noexcept {
        return (n.r * 73856093) ^ (n.c * 19349663);
    }
};
struct NodeEq {
    bool operator()(const Node& a, const Node& b) const noexcept {
        return a.r == b.r && a.c == b.c;
    }
};

int main() {
    // ASCII grid input from stdin; S=start, G=goal, #=wall, .=open
    // Example:
    // 5 7
    // S..#..G
    // .##.#..
    // ....#..
    // ##..#..
    // .......
    int R, C; 
    if (!(std::cin >> R >> C)) { std::cerr << "Provide R C then grid lines.\n"; return 1; }
    std::string line;
    std::vector<std::string> grid;
    grid.reserve(R);
    Node S{-1,-1}, G{-1,-1};
    for (int i=0;i<R;++i) {
        std::cin >> line;
        grid.push_back(line);
        for (int j=0;j<C;++j) {
            if (grid[i][j]=='S') S={i,j};
            if (grid[i][j]=='G') G={i,j};
        }
    }
    if (S.r<0||G.r<0){ std::cerr << "Missing S or G.\n"; return 1; }

    auto h = [&](const Node& n){
        return std::abs(n.r-G.r) + std::abs(n.c-G.c);
    };

    using PQItem = std::pair<int, Node>;
    std::priority_queue<PQItem, std::vector<PQItem>, std::greater<PQItem>> open;
    std::unordered_map<Node, int, NodeHash, NodeEq> gscore;
    std::unordered_map<Node, Node, NodeHash, NodeEq> parent;

    gscore[S] = 0;
    open.push({h(S), S});
    const int INF = std::numeric_limits<int>::max()/4;
    auto in_bounds = [&](int r,int c){ return r>=0&&c>=0&&r<R&&c<C; };

    const int dr[4]={1,-1,0,0};
    const int dc[4]={0,0,1,-1};

    while (!open.empty()) {
        auto [f, u] = open.top(); open.pop();
        if (u.r==G.r && u.c==G.c) break;
        int gu = gscore.count(u)? gscore[u] : INF;
        for (int k=0;k<4;++k){
            int nr=u.r+dr[k], nc=u.c+dc[k];
            if (!in_bounds(nr,nc) || grid[nr][nc]=='#') continue;
            Node v{nr,nc};
            int alt = gu + 1;
            int gv = gscore.count(v)? gscore[v]: INF;
            if (alt < gv) {
                gscore[v]=alt;
                parent[v]=u;
                open.push({alt + h(v), v});
            }
        }
    }

    // reconstruct
    Node cur = G;
    if (!parent.count(cur) && !(S.r==G.r && S.c==G.c)) {
        std::cerr << "No path.\n";
        return 0;
    }
    while (!(cur.r==S.r && cur.c==S.c)) {
        if (grid[cur.r][cur.c]=='.') grid[cur.r][cur.c] = '*';
        cur = parent[cur];
    }
    grid[S.r][S.c]='S'; grid[G.r][G.c]='G';

    for (auto& row : grid) std::cout << row << "\n";
    return 0;
}
