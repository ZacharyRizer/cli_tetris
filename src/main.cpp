#include <iostream>
#include <string>
using namespace std;

wstring tetromino[7]; // array of wide strings -- tetris pieces
// game board
int nFieldWidth = 12;
int nFieldHeight = 18;
unsigned char *pField = nullptr;

int Rotate(int pos_x, int pos_y, int rotation) {
  // manipulate the tetris piece-string based on rotation
  switch (rotation % 4) {
  case 0:
    return pos_y * 4 + pos_x; // 0 degrees
  case 1:
    return 12 + pos_y - (pos_x * 4); // 90 degrees
  case 2:
    return 15 - (pos_y * 4) - pos_x; // 180 degrees
  case 3:
    return 3 - pos_y + (pos_x * 4); // 270 degrees
  }
  return 0;
}

int main() {
  // create tetris shapes - each shape is a 4x4 grid of chars
  tetromino[0].append(L"..X...X...X...X.");
  tetromino[1].append(L"..X..XX...X.....");
  tetromino[2].append(L".....XX..XX.....");
  tetromino[3].append(L"..X..XX..X......");
  tetromino[4].append(L".X...XX...X.....");
  tetromino[5].append(L".X...X...XX.....");
  tetromino[6].append(L"..X...X..XX.....");

  // initialize the board
  pField = new unsigned char[nFieldWidth * nFieldHeight];
  for (int x = 0; x < nFieldWidth; x++) // board boundary
    for (int y = 0; y < nFieldWidth; y++)
      // either set value to 9 for border or 0 for empty space
      pField[y * nFieldWidth + x] =
          (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;
}
