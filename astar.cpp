#include<iostream>
#include<cmath>
#include<cstring>
#include<Stack>
#include<cfloat>
#include<set>
#include<vector>
using namespace std;

#define ROW 9
#define COL 10

typedef pair<int , int> Pair;
typedef pair<double, pair<int, int>> pPair;

struct Cell {
    int parent_i, parent_j;
    double f, g, h;
};

// Function to check whether row, col is valid
bool isValid(int row, int col) {
    return ((row >= 0) && (row < ROW) && (col >= 0) &&
            (col < COL));
}

// Function to check if cell is blocked
bool isUnblocked(int grid[][COL], int row, int col){
    if (grid[row][col] == 1) return true;
    return false;
}

// check if a cell is destination
bool isDestination(int row, int col, Pair dest){
    if (dest.first == row && dest.second == col) return true;
    return false;
} 

// Calc heu
double heu(int row, int col, Pair dest) {
    return (double)sqrt((row-dest.first)*(row-dest.first) 
            + (col-dest.second)*(col-dest.second));
}

// function to print the answer
void tracePath(Cell cellDetails[][COL], Pair dest){
    cout << "\nThe path is: ";
    int row = dest.first;
    int col = dest.second;

    stack<Pair> path;

    while(!(cellDetails[row][col].parent_i == row
            && cellDetails[row][col].parent_j == col)) {
        path.push({row, col});
        int temp_row = cellDetails[row][col].parent_i;
		int temp_col = cellDetails[row][col].parent_j;
		row = temp_row;
		col = temp_col;
    }

    path.push({row, col});

    while(!path.empty()){
        Pair temp = path.top();
        path.pop();
        cout << temp.first << "," << temp.second << " -> "; 
    }

    return;
}

void sol(int grid[][COL], Pair src, Pair dest) {
    if (!isValid(src.first, src.second)) {
        cout << "\nSource invalid";
        return;
    }
    if (!isValid(dest.first, dest.second)) {
        cout << "\nDestination invalid";
        return;
    }

    if (!isUnblocked(grid, src.first, src.second)
        || !isUnblocked(grid, dest.first, dest.second)) {
        cout << "\nSource or destination invalid";
        return;
    } 

    if (isDestination(src.first, src.second, dest)) {
        cout << "\nThis was the destination itself!!!";
        return;
    }

    // list of done vertices
    bool closedList[ROW][COL];
    memset(closedList, false, sizeof(closedList));

    Cell cellDetails[ROW][COL];

    int i, j;

    // initialize with maxed out intial values
    for (int i=0; i<ROW; i++){
        for(int j=0; j<COL; j++){
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;

            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    // For the starting node
    i = src.first, j = src.second;
    cellDetails[i][j].f = 0;
    cellDetails[i][j].g = 0;
    cellDetails[i][j].h = 0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    set<pPair> openList;

    // starting node is put into openList
    openList.insert({0.0,{i,j}});

    bool foundDest = false;

    // to check if dest is found
    while(!openList.empty()){
        pPair p = *openList.begin();

        // remove the element
        openList.erase(openList.begin());

        // Get the details of current cell
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        double gnew, hnew, fnew;

        vector<pair<int, int>> sides = {
            {0,1}, {0,-1}, {1,0}, {-1,0}, 
            {1,1}, {-1,1}, {-1,-1}, {1,-1}
        };

        // 1
        for (auto it: sides){
            int new_i = i+it.first;
            int new_j = j+it.second;

            if (isValid(new_i, new_j)) {
                if (isDestination(new_i, new_j, dest)) {
                    cellDetails[new_i][new_j].parent_i = i;
                    cellDetails[new_i][new_j].parent_j = j;

                    cout << "\nDestination found!!!" << endl;
                    tracePath(cellDetails, dest);
                    
                    foundDest = true;
                    return;
                }
                else if (!closedList[new_i][new_j] && 
                        isUnblocked(grid, new_i, new_j)){
                    gnew = cellDetails[i][j].g + 1;
                    hnew = heu(new_i,new_j,dest);
                    fnew = gnew + hnew;

                    if (cellDetails[new_i][new_j].f == FLT_MAX
                        || cellDetails[new_i][new_j].f > fnew) {
                            openList.insert({fnew, {new_i, new_j}});

                            cellDetails[new_i][new_j].f = fnew;
                            cellDetails[new_i][new_j].g = gnew;
                            cellDetails[new_i][new_j].h = hnew;
                            cellDetails[new_i][new_j].parent_i = i;
                            cellDetails[new_i][new_j].parent_j = j;
                    }
                }
            }
        }

    }



    if (!foundDest) cout << "Failed to reach the destination!!!";

    return;
}

int main() {

    int grid[ROW][COL]
        = { { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
            { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
            { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
            { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
            { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
            { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
            { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
            { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
            { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } };
 
    // Source is the left-most bottom-most corner
    Pair src = make_pair(8, 0);
 
    // Destination is the left-most top-most corner
    Pair dest = make_pair(0, 0);
 
    sol(grid, src, dest);

    return 0;
}