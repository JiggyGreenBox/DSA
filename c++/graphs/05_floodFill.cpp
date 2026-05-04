#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {

    // visited matrix
    int m = image.size();
    int n = image[0].size();

    int old_pixel = image[sr][sc];
    if(old_pixel == newColor) return image; // early exit

    vector<vector<int>> newImage = image;

    // vector<vector<int>> visited(m, vector<int>(n, 0));

    int dx[] = {0, 0, 1,-1};
    int dy[] = {1,-1, 0, 0};

    

    // iterate from starting point    
    // visited[sr][sc] = 1;    
    newImage[sr][sc] = newColor;
    queue<pair<int, int>> q;    
    q.push({sr,sc});


    while(!q.empty()) {
        auto p = q.front();
        q.pop();

        int x = p.first;
        int y = p.second;

        for(int k=0; k<4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            // assign new color
            if(nx>=0 && nx<m && ny>=0 && ny<n && image[nx][ny] == old_pixel && newImage[nx][ny] != newColor) {
                // visited[nx][ny] = 1;
                newImage[nx][ny] = newColor;
                q.push({nx,ny});
            }
        }
    }
    
    return newImage;
}

void print(const vector<vector<int>>& image) {
    cout << "[ ";
    for(auto& v : image) {
        cout << "[ ";
        for(int x : v) cout << x << " ";
        cout << "] ";    
    }
    cout << "]\n";
}

class Solution{
private:
    void dfs(int x, int y, 
            vector<vector<int>> &image,
            vector<vector<int>> &newImage,
            int newColor)
    {
        int m = image.size();
        int n = image[0].size();

        int old_pixel = image[x][y];

        newImage[x][y] = newColor;

        int dx[] = {0, 0, 1,-1};
        int dy[] = {1,-1, 0, 0};

        for(int k=0; k<4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if( nx>=0 && nx<m && ny>=0 && ny<n && 
                image[nx][ny] == old_pixel && newImage[nx][ny] != newColor) 
            {
                dfs(nx, ny, image, newImage, newColor);
            }
        }
    }

public:
    vector<vector<int>> floodFill(vector<vector<int>> &image,
                                  int sr, int sc, int newColor) {
        vector<vector<int>> newImage = image;

        if(image[sr][sc] == newColor) return image;

        dfs(sr, sc, image, newImage, newColor);

        return newImage;
    }
};


int main() {
    vector<vector<int>> image = {{0, 1, 0}, {1, 1, 0}, {0, 0, 1}};
    int newColor = 3;
    int sr = 2;
    int sc = 2;
    print(floodFill(image, sr, sc, newColor));


    image = {{1, 1, 1}, {1, 1, 0}, {1, 0, 1}};
    sr = 1;
    sc = 1; 
    newColor = 2;
    print(floodFill(image, sr, sc, newColor)); // Output: [[2, 2, 2], [2, 2, 0], [2, 0, 1]]


    return 0;
}