#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

struct cell {
  bool clicked;
  bool mine;
  int neighbors;
  cell() : clicked(false), mine(false), neighbors(0) {}
};

class Map {
  private:
    vector<vector<cell>> map;
    int mines;
    int row, col;
    int left;

    vector<int> getMines() {
      vector<int> result;
      int len = row * col - 1;
      vector<int> arr(len);

      for (int i = 0; i < len; i++) {
        arr[i] = i;
      }
      for (int i = 0; i < mines; i++) {
        srand(time(NULL));
        int idx = rand() % (len-1);
        result.push_back(arr[idx]);

        len--;
        int tmp = arr[len];
        arr[len] = arr[idx];
        arr[idx] = tmp;
      }

      return result;
    }

  public:
    Map(int r, int c, int m) {
      vector<cell> tmprow(c);
      vector<vector<cell>> tmp(r, tmprow);
      map = tmp;
      
      mines = m;
      row = r;
      col = c;
      left = row*col;
    }

    void init() { 
      vector<int> pos = getMines();
      for (auto x:pos) {
        cout << x << " ";
        int i = x / row;
        int j = x % row;
        map[i][j].mine = true;
        // cout << i << " " << j << endl;
      }
      cout << endl;
      for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
          for (int ii = -1; ii < 2; ii++) {
            for (int jj = -1; jj < 2; jj++) {
              if (i + ii >= 0 && i + ii < row && j + jj >= 0 && j + jj < col && map[i+ii][j+jj].mine) {
                map[i][j].neighbors++;
              }
            }
          }
        }
      }
      // print();
    }

    int click(int i, int j) {
      if (map[i][j].clicked)
        return 1;
      if (map[i][j].mine) {
        return 2;
      }
      map[i][j].clicked = true;
      left--;
      if (left == mines)
        return 5;

      if (map[i][j].neighbors == 0) {
        for (int ii = -1; ii < 2; ii++) {
          for (int jj = -1; jj < 2; jj++) {
            if (i + ii >= 0 && i + ii < row && j + jj >= 0 && j + jj < col) {
              click(i+ii, j+jj);
            }
          }
        }
        return 3;
      } else {
        return 4;
      }
    }

    void print() {
      for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
          if (map[i][j].clicked)
            cout << map[i][j].neighbors << " ";
          else
            cout << "[]";
        }
        cout << endl;
      }
    cout << left << " cells left unclicked" << endl;
    }
    
};

int main() {
  cout << "type in map dimention and # of mines: r c m" << endl;
  int r=5, c=5, m=8;
  cin >> r >> c >> m;
  Map map(r, c, m);
  map.init();
  map.print();
  int i, j;
  while(1) {
    cin >> i >> j;
    switch (map.click(i, j)) {
      case 1: 
        cout << "cell clicked!" << endl;
        break;
      case 2:
        cout << "game over!" << endl;
        return 0;
      case 5:
        cout << "you win!" << endl;
        return 0;
      default:
        map.print();
        break;
    }
  }
}
