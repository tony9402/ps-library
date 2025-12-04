/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/3763
 * Test : Accepted
 * Last Updated : 2023.01.04 01:10 AM (KST)
 * Tag : dlx, knuthx
 */
template<const int dlx_siz> struct DLX {
    struct Node { int row, size, column, up, down, left, right; };
    vector<Node> node;
    int node_siz, head;

    DLX() { }

    void dlx_cover(int idx) {
        node[node[idx].right].left = node[idx].left;
        node[node[idx].left].right = node[idx].right;
        for (int it = node[idx].down; it != idx; it = node[it].down) {
            for (int jt = node[it].right; jt != it; jt = node[jt].right) {
                node[node[jt].down].up = node[jt].up;
                node[node[jt].up].down = node[jt].down;
                --node[node[jt].column].size;
            }
        }
    }

    void dlx_uncover(int idx) {
        for (int it = node[idx].up; it != idx; it = node[it].up) {
            for (int jt = node[it].left; jt != it; jt = node[jt].left) {
                node[node[jt].down].up = jt;
                node[node[jt].up].down = jt;
                ++node[node[jt].column].size;
            }
        }
        node[node[idx].right].left = idx;
        node[node[idx].left].right = idx;
    }

    bool dlx_search(vector<int> &solution) {
        if (node[head].right == head) return true;
        int ptr = -1;
        int low = 1 << 30;
        for (int it = node[head].right; it != head; it = node[it].right) {
            if (node[it].size < low) {
                if (node[it].size == 0) return false;
                low = node[it].size;
                ptr = it;
            }
        }
        dlx_cover(ptr);
        for (int it = node[ptr].down; it != ptr; it = node[it].down) {
            solution.push_back(node[it].row);
            for (int jt = node[it].right; jt != it; jt = node[jt].right) dlx_cover(node[jt].column);
            if (dlx_search(solution)) return true;
            solution.pop_back();
            for (int jt = node[it].left; jt != it; jt = node[jt].left) dlx_uncover(node[jt].column);
        }
        dlx_uncover(ptr);
        return false;
    }

    vector<int> dlx_solve(const vector<vector<int>> &matrix, int n, int skip = -1) {
        node_siz = 0;
        node.reserve(dlx_siz);
        node.resize(dlx_siz);
        head = dlx_siz - 1;
        node[head].right = 0;
        node[head].left = n - 1;
        for (int i = 0; i < n; ++i) {
            node[node_siz].size = 0;
            node[node_siz].up = i;
            node[node_siz].down = i;
            if (i == 0) node[node_siz].left = head;
            else node[node_siz].left = i - 1;
            if (i == n - 1) node[node_siz].right = head;
            else node[node_siz].right = i + 1;
            ++node_siz;
        }
        for (int i = 0; i < (int)matrix.size(); ++i) {
            int last = -1;
            for (int j = 0; j < (int)matrix[0].size(); ++j) {
                if(matrix[i][j] == skip) continue;
                node[node_siz].row = i;
                node[node_siz].column = j;
                node[node_siz].up = node[j].up;
                node[node_siz].down = j;
                if (last != -1) {
                    node[node_siz].left = last;
                    node[node_siz].right = node[last].right;
                    node[node[last].right].left = node_siz;
                    node[last].right = node_siz;
                }
                else {
                    node[node_siz].left = node_siz;
                    node[node_siz].right = node_siz;
                }
                node[node[j].up].down = node_siz;
                node[j].up = node_siz;
                ++node[j].size;
                last = node_siz++;
            }
        }
        vector<int> solution;
        dlx_search(solution);
        return solution;
    }
};
