#include "Playlist.h"
#include <algorithm>
#include <iostream>

using namespace std;

PlaylistNode::PlaylistNode() {
  uniqueID = "none";
  songName = "none";
  artistName = "none";
  songLength = 0;
  nextNodePtr = 0;
}

PlaylistNode::PlaylistNode(string uniqueID, string songName, string artistName,
                           int songLength, PlaylistNode *nextNodePtr) {
  this->uniqueID = uniqueID;
  this->songName = songName;
  this->artistName = artistName;
  this->songLength = songLength;
  this->nextNodePtr = nextNodePtr;
}

void PlaylistNode::InsertAfter(PlaylistNode *node) {
  PlaylistNode *tmpNext = this->nextNodePtr;
  this->nextNodePtr = node;
  node->nextNodePtr = tmpNext;
} // insert the node which is passed inside the parameter after the node which
  // is calling this function

void PlaylistNode::SetNext(PlaylistNode *node) {
  this->nextNodePtr = node;
} // set the current next node ptr to node

string PlaylistNode::GetID() { return uniqueID; }

string PlaylistNode::GetSongName() { return songName; }

string PlaylistNode::GetArtistName() { return artistName; }

int PlaylistNode::GetSongLength() { return songLength; }

PlaylistNode *PlaylistNode::GetNext() { return nextNodePtr; }

void PlaylistNode::PrintPlaylistNode() {
  cout << "Unique ID: " << uniqueID << endl;
  cout << "Song Name: " << songName << endl;
  cout << "Artist Name: " << artistName << endl;
  cout << "Song Length (in seconds): " << songLength << endl << endl;
}

void Playlist::PrintMenu(string title) {
  char menuChoice;
  cout << title << " PLAYLIST MENU" << endl;
  cout << "a - Add song" << endl;
  cout << "d - Remove song" << endl;
  cout << "c - Change position of song" << endl;
  cout << "s - Output songs by specific artist" << endl;
  cout << "t - Output total time of playlist (in seconds)" << endl;
  cout << "o - Output full playlist" << endl;
  cout << "q - Quit" << endl << endl;
  cout << "Choose an option:" << endl;

  cin >> menuChoice;

  if (menuChoice == 'q') {
    exit(0);
  } else if (menuChoice == 'a') {
    AddSong();
  } else if (menuChoice == 'd') {
    RemoveSong();
  } else if (menuChoice == 'c') {
    ChangePosition();
  } else if (menuChoice == 's') {
    OutputSpecificSongs();
  } else if (menuChoice == 't') {
    OutputTotalTime();
  } else if (menuChoice == 'o') {
    cout << title << " - OUTPUT FULL PLAYLIST" << endl;
    OutputFullPlaylist();
  } else {
    PrintMenu(title);
  }
}

void Playlist::OutputFullPlaylist() {
  PlaylistNode *tmpNode = head;
  int count = 1;

  if (!head) {
    cout << "Playlist is empty" << endl << endl;
  } else {
    while (tmpNode) {
      cout << count << "." << endl;
      count++;
      tmpNode->PrintPlaylistNode();
      tmpNode = tmpNode->GetNext();
    }
  }
}

void Playlist::AddSong() {
  string ID = "";
  string songName = "";
  string artistName = "";
  int songLength = 0;

  cin.ignore();
  cout << "ADD SONG" << endl;
  cout << "Enter song's unique ID:" << endl;
  getline(cin, ID);
  cout << "Enter song's name:" << endl;
  getline(cin, songName);
  cout << "Enter artist's name:" << endl;
  getline(cin, artistName);
  cout << "Enter song's length (in seconds):" << endl;
  cin >> songLength;
  cout << endl;

  PlaylistNode *newNode =
      new PlaylistNode(ID, songName, artistName, songLength);

  if (tail) {
    tail->SetNext(newNode); // sets the new node to be after tail
    tail = tail->GetNext(); // points tail to the next node
  } else {
    head = newNode;
    tail = newNode;
  }
}

void Playlist::RemoveSong() {
  string ID;
  PlaylistNode *prevNode;
  PlaylistNode *currNode;
  PlaylistNode *tmpNode = head;
  string songName;

  cout << "REMOVE SONG" << endl;
  cout << "Enter song's unique ID:";
  cin >> ID;

  if (head == nullptr) {
    cout << "Playlist is empty";
  } else if (head == tail && head != nullptr) {
    currNode = tmpNode;
    delete currNode;
    currNode = nullptr;
  } else {
    if (tail->GetID() == ID) {
      currNode = tail;
    }

    while (tmpNode->GetNext()) {
      if (tmpNode->GetNext()->GetID() == ID) {
        prevNode = tmpNode;
      }
      if (tmpNode->GetID() == ID) {
        currNode = tmpNode;
      }
      tmpNode = tmpNode->GetNext();
    }

    if (tail->GetID() == ID) {
      tail = prevNode;
    }
    // if theres only one node, remove that node and set head and tail to null
    // if it is at the tail, just remove that node and set tail to previous node

    songName = currNode->GetSongName();
    prevNode->SetNext(currNode->GetNext());

    delete currNode;
    currNode = nullptr;

    cout << endl;
    cout << "\"" << songName << "\""
         << " removed." << endl
         << endl;
  }
}

void Playlist::RemoveSong(string ID) {
  PlaylistNode *prevNode;
  PlaylistNode *currNode;
  PlaylistNode *tmpNode = head;
  string songName;

  if (head == nullptr) {
    cout << "Playlist is empty";
  } else if (head == tail && head != nullptr) {
    currNode = tmpNode;
    delete currNode;
    currNode = nullptr;
  } else if (head->GetID() == ID) {
    head = head->GetNext();
    delete tmpNode;
  } else {
    if (tail->GetID() == ID) {
      currNode = tail;
    }

    while (tmpNode->GetNext()) {
      if (tmpNode->GetNext()->GetID() == ID) {
        prevNode = tmpNode;
      }
      if (tmpNode->GetID() == ID) {
        currNode = tmpNode;
      }
      tmpNode = tmpNode->GetNext();
    }

    if (tail->GetID() == ID) {
      tail = prevNode;
    }
    // if theres only one node, remove that node and set head and tail to null
    // if it is at the tail, just remove that node and set tail to previous node

    songName = currNode->GetSongName();
    prevNode->SetNext(currNode->GetNext());

    delete currNode;
    currNode = nullptr;
  }
}
//
/*
keep one pointer to point to the node after the one ur deleting (previous)
keep another pointer to delete the node (current)
iterate through to find node before the node ur removing, set to prev
set curr to the node being removed
set prev next to curr next
set curr to null
*/

void Playlist::ChangePosition() {
  int currPos;
  int newPos;
  int numNodes = 0;
  PlaylistNode *tmpNode = head;
  PlaylistNode *currNode = new PlaylistNode;
  PlaylistNode *prevNode = head;
  string tmpID;
  string tmpSongName;
  string tmpArtistName;
  int tmpSongLength;
  PlaylistNode *tmpNextNodePtr;

  cout << "CHANGE POSITION OF SONG" << endl;
  cout << "Enter song's current position:" << endl;
  cin >> currPos;
  cout << "Enter new position for song:" << endl;
  cin >> newPos;
  // use InsertAfter and RemoveSong
  while (tmpNode) {
    numNodes++;
    tmpNode = tmpNode->GetNext();
  }
  if (newPos < 1) {
    newPos = 1; // move pos to head
  }
  if (newPos > numNodes) {
    // move pos to tail
    newPos = numNodes;
  }
  if (newPos > currPos) {
    newPos -= 1;
  }
  tmpNode = head;
  for (int i = 1; i < currPos; i++) {
    tmpNode = tmpNode->GetNext();
  }
  currNode = tmpNode;

  /*
  moving the head node
    moving the tail node
    moving a node to the head
    moving a node to the tail
    moving a node up the list
    moving a node down the list
  */
  tmpID = currNode->GetID();
  tmpSongName = currNode->GetSongName();
  tmpArtistName = currNode->GetArtistName();
  tmpSongLength = currNode->GetSongLength();
  tmpNextNodePtr = currNode->GetNext();

  PlaylistNode *CurrNodeCopy = new PlaylistNode(
      tmpID, tmpSongName, tmpArtistName, tmpSongLength, tmpNextNodePtr);
  RemoveSong(currNode->GetID());
  prevNode = head;
  if (newPos != 1) {
    if(currPos < newPos){
      for (int i = 1; i < newPos; i++) {
        prevNode = prevNode->GetNext();
      }
    }else{
      for (int i = 1; i < newPos-1; i++) {
        prevNode = prevNode->GetNext();
      }
    }
    
    prevNode->InsertAfter(CurrNodeCopy);
  } else {
    CurrNodeCopy->SetNext(head);
    head = CurrNodeCopy;
  }

  if (newPos >= currPos) {
    newPos += 1;
  }
  if (newPos <= currPos) {
    newPos += 1;
  }
  cout << "\"" << CurrNodeCopy->GetSongName() << "\"" << " moved to position " << newPos << endl << endl;
}

void Playlist::OutputSpecificSongs() {
  PlaylistNode *tmpNode = head;
  int count = 1;
  string name;

  cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
  cout << "Enter artist's name:" << endl;
  cin.ignore();
  getline(cin, name);
  cout << endl;

  while (tmpNode) {
    if (tmpNode->GetArtistName() == name) {
      cout << count << "." << endl;
      tmpNode->PrintPlaylistNode();
    }
    count++;
    tmpNode = tmpNode->GetNext();
  }
}

void Playlist::OutputTotalTime() {
  PlaylistNode *tmpNode = head;
  int sum = 0;

  cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
  while (tmpNode) {
    sum += tmpNode->GetSongLength();
    tmpNode = tmpNode->GetNext();
  }
  cout << "Total time: " << sum << " seconds" << endl << endl;
}
