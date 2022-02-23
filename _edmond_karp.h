/**
 *  @usage: addEdge() -> maxFlow(). bfs() is called internally from maxFlow().
 */
class EdmondKarp {
public:
    EdmondKarp(int maxv) : MAXV(maxv), graph(maxv) {}

    struct Edge {
        int to, cap, flow;
        Edge* dual;
        int spare() { return cap - flow; }
        void add(int f) { flow += f; dual->flow -= f; }
    };

    const int MAXV;
    vector<vector<Edge*>> graph;

    void addEdge(int from, int to, int cap, int revcap = 0) {
        auto e = new Edge{to, cap, 0};
        auto ee = new Edge{from, revcap, 0};
        e->dual = ee;
        ee->dual = e;
        graph[from].push_back(e);
        graph[to].push_back(ee);
    }

    int maxFlow(int source, int sink) {
        int maxflow = 0;
        while (true) {
            auto [prev, path] = bfs(source, sink);
            if (prev[sink] == -1) {
                break;
            }
            int minflow = INF;
            for (int v = sink; v != source; v = prev[v]) {
                minflow = min(minflow, path[v]->spare());
            }
            for (int v = sink; v != source; v = prev[v]) {
                path[v]->add(minflow);
            }
            maxflow += minflow;
        }
        return maxflow;
    }

    vector<pair<int, int>> minCut(int source) {
        vector<bool> visited(MAXV, false);
        queue<int> q;
        q.push(source);
        visited[source] = true;
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (auto e : graph[cur]) {
                int to = e->to;
                if (!visited[to] && e->spare() > 0) {
                    visited[to] = true;
                    q.push(to);
                }
            }
        }

        vector<pair<int, int>> res;
        for (int cur = 0; cur < MAXV; ++cur) {
            if (visited[cur]) {
                for (auto e : graph[cur]) {
                    int to = e->to;
                    if (!visited[to] && e->cap > 0) {
                        res.emplace_back(cur, to);
                    }
                }
            }
        }
        return res;
    }

    size_t size() const {
        return MAXV;
    }

private:
    // static constexpr int INF = INT_MAX / 2;

    pair<vector<int>, vector<Edge*>> bfs(int source, int sink) {
        vector<int> prev(MAXV, -1);
        vector<Edge*> path(MAXV, nullptr);
        queue<int> q;
        q.push(source);

        while (!q.empty() && prev[sink] == -1) {
            int cur = q.front();
            q.pop();
            for (auto e : graph[cur]) {
                int to = e->to;
                if (prev[to] == -1 && e->spare() > 0) {
                    prev[to] = cur;
                    path[to] = e;
                    q.push(to);
                }
            }
        }
        return {move(prev), move(path)};
    }
};
