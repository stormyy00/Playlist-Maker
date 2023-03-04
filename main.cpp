#include <iostream>
#include "Playlist.h"
using namespace std;

int main() {
  Playlist playlist1;
  string playlistTitle;
  cout << "Enter playlist's title:" << endl << endl;
  getline(cin, playlistTitle);

  while (true) {
    playlist1.PrintMenu(playlistTitle);
  }
}