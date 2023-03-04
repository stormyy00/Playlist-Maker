
#ifndef PLAYLIST_H
#define PLAYLIST_H

#include<iostream>
using namespace std;

struct PlaylistNode {
  public:
    PlaylistNode();
    //parameterized constructor
    PlaylistNode(string uniqueID, string songName, string artistName, int songLength, PlaylistNode* nextNodePtr = nullptr);
    //public member funcs
    void InsertAfter(PlaylistNode* node);
    void SetNext(PlaylistNode* node);
    string GetID();
    string GetSongName();
    string GetArtistName();
    int GetSongLength();
    PlaylistNode* GetNext();
    void PrintPlaylistNode();

  private:
    string uniqueID;
    string songName;
    string artistName;
    int songLength;
    PlaylistNode* nextNodePtr;
};

class Playlist {
  public: 
    Playlist(){
      head = nullptr;
      tail = nullptr;
    }
    void PrintMenu(string title);
    void OutputFullPlaylist();
    void AddSong();
    void RemoveSong();
    void RemoveSong(string ID);
    void ChangePosition();
    void OutputSpecificSongs();
    void OutputTotalTime();

  private: 
    PlaylistNode* head;
    PlaylistNode* tail;
};

#endif