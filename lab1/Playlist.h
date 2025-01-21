#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <iostream>

using namespace std;

class PlaylistNode {
    public:
    PlaylistNode();
    PlaylistNode(const string & id, const string & song, const string & artist, int length);
    void InsertAfter(PlaylistNode* node);
    void SetNext(PlaylistNode* node);
    const string & GetID() const;
    const string & GetSongName() const;
    const string & GetArtistName() const;
    int GetSongLength() const;
    PlaylistNode* GetNext() const ;
    void PrintPlaylistNode() const;

    private:
    string uniqueID;
    string songName;
    string artistName;
    int songLength;
    PlaylistNode* nextNodePtr;
};

class Playlist {
    public: 
    Playlist(); // rule of three (destructor, copy constructor, assignment operator)
    ~Playlist();
    Playlist(const Playlist &) = delete;
    Playlist & operator=(const Playlist &) = delete;
    void AddSong(const string & id, const string & song, const string & artist, int length);
    void RemoveSong(const string & id);
    void ChangePosition(int oldPos, int newPos);
    void OutputSongsByArtist(const string & artist);
    int OutputTotalTime();
    void OutputFullPlaylist();   

    private:
    PlaylistNode* head;
    PlaylistNode* tail; 
};

#endif