#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <climits>
#include <io.h>
#include <fcntl.h>
#include <functional>
#include <clocale>

using namespace std;

// Directions for 4 connected cells (Up, Down, Left, Right)
const int dx[] = { -1, 1, 0, 0 };
const int dy[] = { 0, 0, -1, 1 };

// Print grid
void Grid(const vector<vector<int>>& grid) {
    wcout << L"   ";
    for (size_t j = 0; j < grid[0].size(); ++j) {
        wcout << j << L" ";
    }
    wcout << endl << endl;

    for (size_t i = 0; i < grid.size(); ++i) {
        wcout << i << L"  ";
        for (size_t j = 0; j < grid[i].size(); ++j) {
            switch (grid[i][j]) {
            case -1: wcout << L"# "; break; // Wall
            case 0:  wcout << L". "; break; // Path
            case 2:  wcout << L"S "; break; // Start point
            case 3:  wcout << L"E "; break; // End point
            case 4:  wcout << L"o "; break; // User path
            }
        }
        wcout << endl;
    }
}

// Generate random point in a different quadrant
pair<int, int> randomPt(int gridS, int quadrant) {
    int halfS = gridS / 2;
    int x = rand() % halfS;
    int y = rand() % halfS;

    switch (quadrant) {
    case 1: return { x, y };
    case 2: return { x, y + halfS };
    case 3: return { x + halfS, y };
    case 4: return { x + halfS, y + halfS };
    default: return { 0, 0 }; // Should never reach here
    }
}

// Dijkstra algorithm to find all *Hidden* paths
vector<vector<pair<int, int>>> dijkstra(const vector<vector<int>>& grid, pair<int, int> start, pair<int, int> end) {
    size_t n = grid.size();
    size_t m = grid[0].size();

    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
    dist[start.first][start.second] = 0;

    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    pq.push({ 0, start });

    vector<vector<vector<pair<int, int>>>> previous(n, vector<vector<pair<int, int>>>(m));

    while (!pq.empty()) {
        auto current = pq.top();
        pq.pop();
        int currentDist = current.first;
        pair<int, int> currentNode = current.second;

        if (currentNode == end) break;

        for (int i = 0; i < 4; ++i) {
            int nx = currentNode.first + dx[i];
            int ny = currentNode.second + dy[i];

            if (nx >= 0 && ny >= 0 && nx < static_cast<int>(n) && ny < static_cast<int>(m) && grid[nx][ny] != -1) {
                int newDist = currentDist + 1;
                if (newDist < dist[nx][ny]) {
                    dist[nx][ny] = newDist;
                    pq.push({ newDist, {nx, ny} });
                    previous[nx][ny] = { currentNode };
                }
                else if (newDist == dist[nx][ny]) {
                    previous[nx][ny].push_back(currentNode);
                }
            }
        }
    }

    vector<vector<pair<int, int>>> allP;    // Store all *Hidden* paths
    vector<pair<int, int>> path;
    std::function<void(pair<int, int>)> buildP = [&](pair<int, int> node) {
        if (node == start) {
            path.push_back(node);
            reverse(path.begin(), path.end());
            allP.push_back(path);
            reverse(path.begin(), path.end());
            path.pop_back();
            return;
        }
        path.push_back(node);
        for (auto& prev : previous[node.first][node.second]) {
            buildP(prev);
        }
        path.pop_back();
        };

    buildP(end);
    return allP;
}

void Hidden(const wstring& name) {

    wcout << L"You Did It! Your inputs match the shortest path calculated by the algorithm!\n";
    wcout << L"Hidden Achievement Unlocked: Heart Shape  ^ \x1D17 ^  \n\n\n";
    double x, y, size = 5;
    wchar_t s = L'*';
    wstring message = name;
    int print_line = 4;

    if (message.length() % 2 != 0) message += L" ";

    for (x = 0; x < size; x++)
    {
        for (y = 0; y <= 4 * size; y++)
        {
            double dist1 = sqrt(pow(x - size, 2) + pow(y - size, 2));
            double dist2 = sqrt(pow(x - size, 2) + pow(y - 3 * size, 2));

            if (dist1 < size + 0.5 || dist2 < size + 0.5) {
                wcout << s;
            }
            else wcout << L" ";
        }
        wcout << L"\n";
    }

    for (x = 1; x < 2 * size; x++)
    {
        for (y = 0; y < x; y++)
            wcout << L" ";

        for (y = 0; y < 4 * size + 1 - 2 * x; y++)
        {
            if (x >= print_line - 1 && x <= print_line + 1) {
                int idx = y - (4 * size - 2 * x - static_cast<int>(message.length())) / 2;
                if (idx >= 0 && idx < static_cast<int>(message.length())) {
                    if (x == print_line) wcout << message[idx];
                    else wcout << L" ";
                }
                else wcout << s;
            }

            else wcout << s;

        }
        wcout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "en_US.UTF-8");

    if (_setmode(_fileno(stdout), _O_U16TEXT) == -1) {
        cerr << "Error setting console mode to UTF-16" << endl;
        return 1;
    }

    wcout << L"\x2736 \x2022\x2508 \x2736  Welcome to the Pathfinding Game! \x2736 \x2508\x2022\x2736\n";
    wcout << L"Enter your name: ";
    wstring name;
    wcin >> name;
    wcin.get();
    wcout << L"------------------------------------\n";
    wcout << L"Hello " << name << L"! Let's play a game ^ \x1D17 ^ \n";
    wcout << L"Please read the following instructions carefully before playing:\n";
    wcout << L"1. You are given a grid with walls, start point (S), and end point (E).\n";
    wcout << L"2. You need to find a path between both points.\n";
    wcout << L"3. Enter the path step by step by providing the next point inputs (x y). You can use the border coordinates as your guide.\n";
    wcout << L"4. The path must be consecutive (left, right, up, down).\n";
    wcout << L"Write your path carefully you may hit a wall or unlock a hidden achievement  ^ \x1D17 ^  \n";
    wcout << L"Press any key to continue...\n";
    wcin.get();
    wcout << L"------------------------------------\n";

    srand(static_cast<unsigned int>(time(NULL)));

    int gridS = 10;
    vector<vector<int>> grid(gridS, vector<int>(gridS, 0));

    pair<int, int> start = randomPt(gridS, 1);
    pair<int, int> end = randomPt(gridS, 4);

    grid[start.first][start.second] = 2; // Start point (S)
    grid[end.first][end.second] = 3; // End point (E)

    for (int i = 0; i < gridS; ++i) {
        for (int j = 0; j < gridS; ++j) {
            if (rand() % 4 == 0 && make_pair(i, j) != start && make_pair(i, j) != end) {
                grid[i][j] = -1; // Wall
            }
        }
    }

    Grid(grid);
    wcout << L"------------------------------------\n";
    wcout << L"Start Point: (" << start.first << ", " << start.second << ")\n";
    wcout << L"End Point: (" << end.first << ", " << end.second << ")\n";
    wcout << L"------------------------------------\n";

    vector<vector<pair<int, int>>> allHP = dijkstra(grid, start, end);  // Find all *Hidden* paths
    if (allHP.empty()) {
        wcout << L"No valid path found. Please restart the program (\x00AC_\x00AC\")\n";
        return 1;
    }

    wcout << L"Enter the path you think connects the start and end point (enter points as x y) " << endl;
    wcout << endl;

    vector<pair<int, int>> userP;  // Store user path
    userP.push_back(start);

    while (true) {
        int x, y;
        wcout << L"Enter next point (x y): \n";
        if (!(wcin >> x >> y)) {
            wcout << L"Invalid Input! Please enter integer values (\x00AC_\x00AC\")\n";
            wcin.clear();
            wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
            continue;
        }
        wcout << endl;

        if (x < 0 || x >= static_cast<int>(grid.size()) || y < 0 || y >= static_cast<int>(grid[0].size()) || grid[x][y] == -1) {
            wcout << L"Invalid Input! Try to avoid walls (\x00AC_\x00AC\") \n";
            continue;
        }

        if (make_pair(x, y) == start) {
            wcout << L"Invalid Input! You can't go back to the start point (\x00AC_\x00AC\")\n";
            continue;
        }
        pair<int, int> lastPt = userP.back();
        bool Con = false;   // Check if the points are consecutive
        for (int i = 0; i < 4; ++i) {
            if (lastPt.first + dx[i] == x && lastPt.second + dy[i] == y) {
                Con = true;
                break;
            }
        }
        if (!Con) {
            wcout << L"Invalid Input! Points must be consecutive (\x00AC_\x00AC\")\n";
            continue;
        }

        userP.push_back({ x, y });
        grid[x][y] = 4;

        Grid(grid);
        wcout << L"------------------------------------\n";

        // Check if current point is adjacent to end point
        bool adj = false;
        for (int i = 0; i < 4; ++i) {
            if (x + dx[i] == end.first && y + dy[i] == end.second) {
                adj = true;
                break;
            }
        }

        if (adj) {
            wcout << L"Great Job! \x2736\x20 " << name << L"\x20\x2736 . You've reached your destination :) \n";
            userP.push_back(end);
            break;
        }
    }

    bool Correct = false;     // Check if user path is the same as the *Hidden* path
    for (const auto& path : allHP) {
        if (userP == path) {
            Correct = true;
            break;
        }
    }

    if (Correct) {
        Hidden(name);
    }
    else {
        wcout << L"Sadly you haven't unlocked the hidden achievement ^ \x1D17 ^ \n";
    }

    return 0;
}

