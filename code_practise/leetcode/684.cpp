class Solution {
  class disjoint_set {
    vector<int> p, rank;

   public:
    disjoint_set(int n) : rank(n, 0), p(n, 0) {
      for (int i = 0; i < n; ++i) {
        p[i] = i;
      }
    }
    int find(int x) {
      if (p[x] == x) return x;
      return p[x] = find(p[x]);
    }
    int join(int x, int y) {
      int px = find(x);
      int py = find(y);
      if (px == py) return px;
      if (rank[px] > rank[py]) {
        p[py] = px;
        return px;
      } else {
        p[px] = py;
        if (rank[px] == rank[py]) {
          rank[py]++;
        }
        return py;
      }
    }
  };

 public:
  vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    int n = edges.size();
    disjoint_set uf(n);
    for (int i = 0; i < edges.size(); ++i) {
      int x = edges[i][0] - 1;
      int y = edges[i][1] - 1;
      if (uf.find(x) == uf.find(y)) return edges[i];
      uf.join(x, y);
    }
    assert(0);
  }
};
