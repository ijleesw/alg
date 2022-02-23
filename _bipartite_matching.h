/**
 *  @usage: addEdge() -> count(). dfs() is called internally from count().
 */
class BipartiteMatching {
public:
    BipartiteMatching(int N, int M) : graph(N), A(N, -1), B(M, -1), cnt(-1) {}

    void addEdge(int from, int to) {
        graph[from].push_back(to);
    }

    bool dfs(vector<bool>& visited, int cur) {
        visited[cur] = true;
        for (auto to : graph[cur]) {
            if (B[to] == -1 || (!visited[B[to]] && dfs(visited, B[to]))) {
                A[cur] = to;
                B[to] = cur;
                return true;
            }
        }
        return false;
    }

    int count() {
        if (cnt != -1) {
            return cnt;
        }
        cnt = 0;
        for (int i = 0; i < A.size(); ++i) {
            if (A[i] == -1) {
                vector<bool> visited(A.size(), false);
                if (dfs(visited, i)) {
                    ++cnt;
                }
            }
        }
        return cnt;
    }

    vector<vector<int>> graph;
    vector<int> A;
    vector<int> B;
    int cnt;
};
