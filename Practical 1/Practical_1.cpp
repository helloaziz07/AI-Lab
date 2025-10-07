#include <bits/stdc++.h>
using namespace std;

// Goal state
vector<vector<int>> goal(3, vector<int>(3));

// Directions (up, down, left, right)
int dx[] = {-1, 1, 0, 0};
int dy[] = { 0, 0,-1, 1};

// Check if a state is the goal
bool isGoal(vector<vector<int>> state) {
    return state == goal;
}

// Print a 3x3 state with state number
void printState(const vector<vector<int>>& state, int stateNum) {
    cout << "S" << stateNum << ":\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) cout << state[i][j] << ' ';
        cout << '\n';
    }
    cout << "------\n";
}

// Find coordinates of the blank (0)
pair<int,int> findZero(const vector<vector<int>>& state) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (state[i][j] == 0) return {i, j};
    return {-1, -1}; // should never happen for valid input
}

// Breadth-First Search
void BFS(vector<vector<int>> start) {
    queue<vector<vector<int>>> q;
    set<vector<vector<int>>> visited;
    int stateCount = 0;

    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        vector<vector<int>> curr = q.front();
        q.pop();

        stateCount++;
        printState(curr, stateCount);

        if (isGoal(curr)) {
            cout << "Goal reached using BFS!\n";
            return;
        }

        auto p = findZero(curr);
        int x = p.first, y = p.second;

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
                vector<vector<int>> next = curr;
                swap(next[x][y], next[nx][ny]);

                if (visited.find(next) == visited.end()) {
                    q.push(next);
                    visited.insert(next);
                }
            }
        }
    }
    cout << "Goal not reachable.\n";
}

// Depth-First Search
void DFS(vector<vector<int>> start) {
    stack<vector<vector<int>>> st;
    set<vector<vector<int>>> visited;
    int stateCount = 0;

    st.push(start);
    visited.insert(start);

    while (!st.empty()) {
        vector<vector<int>> curr = st.top();
        st.pop();

        stateCount++;
        printState(curr, stateCount);

        if (isGoal(curr)) {
            cout << "Goal reached using DFS!\n";
            return;
        }

        auto p = findZero(curr);
        int x = p.first, y = p.second;

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
                vector<vector<int>> next = curr;
                swap(next[x][y], next[nx][ny]);

                if (visited.find(next) == visited.end()) {
                    st.push(next);
                    visited.insert(next);
                }
            }
        }
    }
    cout << "Goal not reachable.\n";
}

int main() {
    vector<vector<int>> start(3, vector<int>(3));

    cout << "Enter the start state (3x3, use 0 for blank):\n";
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cin >> start[i][j];

    cout << "Enter the goal state (3x3, use 0 for blank):\n";
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cin >> goal[i][j];

    cout << "\nBFS traversal:\n";
    BFS(start);

    cout << "\nDFS traversal:\n";
    DFS(start);

    return 0;
}
