class Solution {
public:

    bool dfs(string src, string dst,
             unordered_map<string, vector<pair<string, double>>>& graph,
             unordered_set<string>& visited,
             double &ans,
             double current) {

        if (visited.count(src)) return false;

        visited.insert(src);

        if (src == dst) {
            ans = current;
            return true;
        }

        for (auto &next : graph[src]) {
            string node = next.first;
            double val = next.second;

            if (dfs(node, dst, graph, visited, ans, current * val)) {
                return true;
            }
        }

        return false;
    }

    vector<double> calcEquation(
        vector<vector<string>>& equations,
        vector<double>& values,
        vector<vector<string>>& queries) {

        unordered_map<string, vector<pair<string, double>>> graph;

        // 1. Build graph
        for (int i = 0; i < equations.size(); i++) {
            string a = equations[i][0];
            string b = equations[i][1];
            double val = values[i];

            graph[a].push_back({b, val});
            graph[b].push_back({a, 1.0 / val});
        }

        vector<double> result;

        // 2. Answer queries
        for (auto &q : queries) {
            string src = q[0];
            string dst = q[1];

            if (!graph.count(src) || !graph.count(dst)) {
                result.push_back(-1.0);
                continue;
            }

            unordered_set<string> visited;
            double ans = -1.0;

            dfs(src, dst, graph, visited, ans, 1.0);

            result.push_back(ans);
        }

        return result;
    }
};