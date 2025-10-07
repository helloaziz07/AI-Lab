#include <iostream>
#include <vector>
using namespace std;

// Function to check if it's safe to assign color c to node
bool isSafe(int node, vector<vector<int>> &adj, vector<int> &color, int c) {
    for (int neighbor = 0; neighbor < adj.size(); neighbor++) {
        if (adj[node][neighbor] == 1 && color[neighbor] == c)
            return false; // adjacent node has same color
    }
    return true;
}

// Backtracking function to solve CSP
bool solveCSP(int node, vector<vector<int>> &adj, vector<int> &color, int totalColors) {
    if (node == adj.size())
        return true; // all regions colored

    for (int c = 1; c <= totalColors; c++) {
        if (isSafe(node, adj, color, c)) {
            color[node] = c; // assign color
            if (solveCSP(node + 1, adj, color, totalColors))
                return true;
            color[node] = 0; // backtrack
        }
    }
    return false;
}

int main() {
    int n;
    cout << "Enter number of regions: ";
    cin >> n;

    vector<vector<int>> adj(n, vector<int>(n));
    cout << "Enter adjacency matrix (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> adj[i][j];
        }
    }

    int totalColors;
    cout << "Enter number of colors: ";
    cin >> totalColors;

    vector<int> color(n, 0); // initially uncolored

    if (solveCSP(0, adj, color, totalColors)) {
        cout << "\n Solution Found:\n";
        for (int i = 0; i < n; i++) {
            cout << "Region " << char('A' + i) << " = ";
            if (color[i] == 1) cout << "Red";
            else if (color[i] == 2) cout << "Green";
            else if (color[i] == 3) cout << "Blue";
            else cout << "Color" << color[i];
            cout << endl;
        }
    } else {
        cout << "\n No solution exists.";
    }

    return 0;
}
