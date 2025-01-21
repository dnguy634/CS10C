#include <iostream>

using namespace std;

#include "Playlist.h"

PlaylistNode::PlaylistNode() { // default constructor sets values to 0
    uniqueID = "none";
    songName = "none";
    artistName = "none";
    songLength = 0;
    nextNodePtr = nullptr;
}

PlaylistNode::PlaylistNode(const string & id, const string & song, const string & artist, int length) { // constructor initializes values from parameter variables
    uniqueID = id;
    songName = song;
    artistName = artist;
    songLength = length;
    nextNodePtr = nullptr;
}

void PlaylistNode::InsertAfter(PlaylistNode* node) { // inputs new song to playlist
    node->nextNodePtr = this->nextNodePtr;  // node points to the variable that the implicit node is pointing to, implicit node updated
    this->nextNodePtr = node;   
}

void PlaylistNode::SetNext(PlaylistNode* node) { 
    this->nextNodePtr = node;  // implicit nextNodePtr points to explicit node 
}

const string & PlaylistNode::GetID() const { return uniqueID; }

const string & PlaylistNode::GetSongName() const { return songName; }

const string & PlaylistNode::GetArtistName()const { return artistName; }

int PlaylistNode::GetSongLength() const { return songLength; }

PlaylistNode* PlaylistNode::GetNext() const { return nextNodePtr; } 

void PlaylistNode::PrintPlaylistNode() const { // Print data of each node
    cout << "Unique ID: " << uniqueID << endl;
    cout << "Song Name: " << songName << endl;
    cout << "Artist Name: " << artistName << endl;
    cout << "Song Length (in seconds): " << songLength << endl;
}

// Playlist class function definitions

Playlist::Playlist() { // head and tail set to null
    head = tail = nullptr;
}

Playlist::~Playlist() { // destructor to clear playlist
    PlaylistNode* curr = head;
    while (curr != nullptr) {
        PlaylistNode* next = curr->GetNext();
        delete curr;
        curr = next;
    }
}

void Playlist::AddSong(const string & id, const string & song, const string & artist, int length) { // add song to playlist
    PlaylistNode* curr = new PlaylistNode(id, song, artist, length);
    if (head == nullptr) { // if playlist is empty, head and tail point to curr node
        head = tail = curr;
    }
    else { // tail's nextNodePtr points to curr and tail to updated to point to curr
        tail->SetNext(curr);
        tail = curr;
    }
}

void Playlist::RemoveSong(const string & id) { // remove song from playlist
    PlaylistNode* curr = head;
    PlaylistNode* prev = nullptr;

    while (curr != nullptr) { // iterate through playlist if list is not empty
        if (curr->GetID() == id) {
            if (prev == nullptr) { // if first song is removed, update head to point to the node that its pointing to (next node)
                head = curr->GetNext();
                cout << "\"" << curr->GetSongName() << "\"" << " removed." << endl;
                delete curr;
                if (head == nullptr) { // if head points to null, update tail (deal with dangling ptr)
                    tail = nullptr;
                }
                return;
            }
            else {
                prev->SetNext(curr->GetNext()); // update prev to point to the node after curr
                cout << "\"" << curr->GetSongName() << "\"" << " removed." << endl;
                delete curr; // delete curr (song)
                if (prev->GetNext() == nullptr) { // update tail if prev next node is pointing to null (deal with dangling ptr)
                    tail = nullptr;
                }
                return;
            }
        }
        prev = curr; // iterate through list if songID comparison is not met
        curr = curr->GetNext();
    }
}

void Playlist::ChangePosition(int oldPos, int newPos) { // update song position
    PlaylistNode* curr = head;
    PlaylistNode* prev = nullptr;
    int count = 1;

    while (count < oldPos) { // iterate through list to reach old position
        if (curr != nullptr) {
            prev = curr;
            curr = curr->GetNext();
            count++; 
        }
    }

    string song = curr->GetSongName(); // retrieve song name from desired node (oldPos)

    if (prev == nullptr) { // skip first node if oldPos is 1
        head = curr->GetNext();
    }
    else {
        prev->SetNext(curr->GetNext());
    }
    if (curr->GetNext() == nullptr) { // update tail to deal with dangling ptr 
        tail = prev;
    }

    if (newPos <= 1) { // if new position is less than 1, move node to the front
        if (head == nullptr) {
            tail = curr;
        }
        curr->SetNext(head);
        head = curr;
        cout << "\"" << song << "\"" << " moved to position " << 1 << endl;
    }
    else { // iterate through list until new position is reached
        count = 2;
        PlaylistNode* _prev;
        PlaylistNode* _succ;
        _prev = head;
        _succ = head->GetNext();
        while (count < newPos && _succ != nullptr) {
            _prev = _succ;
            _succ = _succ->GetNext();
            count++;
        }
        _prev->SetNext(curr); 
        curr->SetNext(_succ);
        if (_succ != nullptr) { // if new position is at the end, update tail to point to curr node
            tail = curr;
        }
        cout << "\"" << song << "\"" << " moved to position " << count << endl;
        }
    }

void Playlist::OutputSongsByArtist(const string & artist) { // output songs by desired artist
    PlaylistNode* curr = head;
    int count = 1;

    while (curr != nullptr) { // iterate through list
        if (curr->GetArtistName() == artist) { // if comparison is met, print data of node
            cout << count << "." << endl;
            curr->PrintPlaylistNode();
            cout << endl;
        }
        curr = curr->GetNext(); // update curr node and count
        count++;
    }
}

int Playlist::OutputTotalTime() { // output total time of playlist
    PlaylistNode* curr = head;
    int totalTime = 0;

    while (curr != nullptr) { // iterate through list
        totalTime += curr->GetSongLength(); // update total time
        curr = curr->GetNext();
    }
    return totalTime;
}

void Playlist::OutputFullPlaylist() { // output full playlist
    if (head == nullptr) { // check if playlist is empty
        cout << "Playlist is empty" << endl;
        cout << endl;
    }
    else { // iterate through playlist
        PlaylistNode* curr = head;
        int counter = 1;

        while (curr != nullptr) { // print data of each song
            cout << counter << "." << endl;
            curr->PrintPlaylistNode();
            cout << endl;
            curr = curr->GetNext();
            counter++;
        }
    }
}











