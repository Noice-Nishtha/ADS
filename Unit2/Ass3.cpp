#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int rows = 5, cols = 5;

// Directions: Up, Down, Left, Right
int dRow[] = {-1, 1, 0, 0};
int dCol[] = {0, 0, -1, 1};

// Check valid cell
bool isValid(int r, int c, vector<vector<int>> &maze, vector<vector<bool>> &visited)
{
    return (r >= 0 && r < rows && c >= 0 && c < cols &&
            maze[r][c] == 0 && !visited[r][c]);
}

// DFS Function
bool DFS(vector<vector<int>> &maze, vector<vector<bool>> &visited, int r, int c, int goalR, int goalC)
{
    if (r == goalR && c == goalC)
    {
        cout << "(" << r << "," << c << ") ";
        return true;
    }

    visited[r][c] = true;

    for (int i = 0; i < 4; i++)
    {
        int newR = r + dRow[i];
        int newC = c + dCol[i];

        if (isValid(newR, newC, maze, visited))
        {
            if (DFS(maze, visited, newR, newC, goalR, goalC))
            {
                cout << "(" << r << "," << c << ") ";
                return true;
            }
        }
    }
    return false;
}

// BFS Function
void BFS(vector<vector<int>> &maze, int startR, int startC, int goalR, int goalC)
{
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, {-1, -1}));

    queue<pair<int, int>> q;
    q.push({startR, startC});
    visited[startR][startC] = true;

    while (!q.empty())
    {
        auto curr = q.front();
        q.pop();

        if (curr.first == goalR && curr.second == goalC)
            break;

        for (int i = 0; i < 4; i++)
        {
            int newR = curr.first + dRow[i];
            int newC = curr.second + dCol[i];

            if (isValid(newR, newC, maze, visited))
            {
                q.push({newR, newC});
                visited[newR][newC] = true;
                parent[newR][newC] = curr;
            }
        }
    }

    // Reconstruct path
    cout << "BFS Path: ";
    pair<int, int> step = {goalR, goalC};

    while (!(step.first == -1 && step.second == -1))
    {
        cout << "(" << step.first << "," << step.second << ") ";
        step = parent[step.first][step.second];
    }
    cout << endl;
}

int main()
{
    vector<vector<int>> maze = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 0, 0, 0},
        {0, 0, 0, 1, 0}};

    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    cout << "DFS Path: ";
    DFS(maze, visited, 0, 0, 4, 4);
    cout << endl;

    BFS(maze, 0, 0, 4, 4);

    return 0;
}