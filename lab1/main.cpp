#include <iostream>

using namespace std;

#include "Playlist.h"

void PrintMenu(const string & input);

int main() {
    Playlist list;
    string title;
    char option;
    string _uniqueID;
    string _songName;
    string _artistName;
    int _songLength;
    int _old;
    int _new;
    
    cout << "Enter playlist's title:" << endl;
    cout << endl;
    getline(cin, title);

    while (option != 'q') {
        PrintMenu(title);
        cin >> option;
        
        if (option == 'a') {
            cout << "ADD SONG" << endl;
            cout << "Enter song's unique ID:" << endl;
            cin >> _uniqueID;   // read ID, song, artist, length and ignore newline character
            cin.ignore();
            cout << "Enter song's name:" << endl;
            getline(cin, _songName);
            cout << "Enter artist's name:" << endl;
            getline(cin, _artistName);
            cout << "Enter song's length (in seconds):" << endl;
            cin >> _songLength;
            list.AddSong(_uniqueID, _songName, _artistName, _songLength);
            cout << endl;
        }
        else if (option == 'd') {
            cout << "REMOVE SONG" << endl;
            cout << "Enter song's unique ID:" << endl;
            cin >> _uniqueID;   // read ID and ignore newline character
            cin.ignore();
            list.RemoveSong(_uniqueID);
            cout << endl;
        }
        else if (option == 'c') {
            cout << "CHANGE POSITION OF SONG" << endl;
            cout << "Enter song's current position:" << endl; // read in new and old positions
            cin >> _old;    
            cout << "Enter new position for song:" << endl;
            cin >> _new;
            list.ChangePosition(_old, _new);
            cout << endl;
        }
        else if (option == 's') {
            cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
            cout << "Enter artist's name:" << endl;     // read in artist and ignore newline character
            cin.ignore();
            getline(cin, _artistName);
            cout << endl;
            list.OutputSongsByArtist(_artistName);
        }
        else if (option == 't') {
            cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
            cout << "Total time: " << list.OutputTotalTime();   // output total time of playlist
            cout << " seconds" << endl;
            cout << endl;
        }
        else if (option == 'o') {
            cout << title << " - OUTPUT FULL PLAYLIST" << endl; // output full playlist
            list.OutputFullPlaylist();
        }
        else if (option == 'q') {
            return -1;      // quit when user enter q
        }
        else {
            cout << "Invalid option, try again" << endl;   // any other character is invalid
        }
    }
    return 0;
}

void PrintMenu(const string & input) {  // print menu
    cout << input << " PLAYLIST MENU" << endl;
    cout << "a - Add song" << endl;
    cout << "d - Remove song" << endl;
    cout << "c - Change position of song" << endl;
    cout << "s - Output songs by specific artist" << endl;
    cout << "t - Output total time of playlist (in seconds)" << endl;
    cout << "o - Output full playlist" << endl;
    cout << "q - Quit" << endl;
    cout << endl;
    cout << "Choose an option:" << endl;
}