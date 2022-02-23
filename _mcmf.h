/**
 *  @usage: addEdge() -> run(). bfs() is called internally from run().
 */
class MCMF {
public:
    MCMF(int maxv) : MAXV(maxv), graph(maxv) {}

    struct Edge {
        int to, cost, cap, flow;
        Edge* dual;
        int spare() { return cap - flow; }
        void add(int f) { flow += f; dual->flow -= f; }
    };

    const int MAXV;
    vector<vector<Edge*>> graph;

    void addEdge(int from, int to, int cost, int cap, int revcap = 0) {
        auto e = new Edge{to, cost, cap, 0};
        auto ee = new Edge{from, -cost, revcap, 0};
        e->dual = ee;
        ee->dual = e;
        graph[from].push_back(e);
        graph[to].push_back(ee);
    }

    // Returns (min cost, max flow).
    pair<int, int> run(int source, int sink) {
        int mincost = 0;
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
                mincost += path[v]->cost * minflow;
                path[v]->add(minflow);
            }
            maxflow += minflow;
        }
        return {mincost, maxflow};
    }

    // NOTE: not verified
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
    // Uses SPFA.
    pair<vector<int>, vector<Edge*>> bfs(int source, int sink) {
        vector<int> cost(MAXV, INF);
        vector<int> prev(MAXV, -1);
        vector<Edge*> path(MAXV, nullptr);
        vector<bool> inqueue(MAXV, false);

        queue<int> q;
        q.push(source);
        cost[source] = 0;
        inqueue[source] = true;

        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            inqueue[cur] = false;

            for (auto e : graph[cur]) {
                int to = e->to;
                if (e->spare() > 0 && cost[cur] + e->cost < cost[to]) {
                    cost[to] = cost[cur] + e->cost;
                    prev[to] = cur;
                    path[to] = e;
                    if (!inqueue[to]) {
                        q.push(to);
                        inqueue[to] = true;
                    }
                }
            }
        }
        return {move(prev), move(path)};
    }
};
