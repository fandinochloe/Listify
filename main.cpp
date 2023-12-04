#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include "algorithms.h"
using namespace std;
using namespace std::chrono;

int main() {
  string file_path = "spotify-2023.csv";
  ifstream infile(file_path);

  if (!infile.is_open()) {
      cout << "Error opening file: " << file_path << endl;
      return 1;  // Exit with an error code
  }

  vector<song> songs;
  string line;
  getline(infile, line);
  while (getline(infile, line)) {
    istringstream iss(line);
    vector<string> row;

    // Read each column separated by a comma
    string value;
    while (getline(iss, value, ',')) {
      row.push_back(value);
    }
    song temp;
    temp.title = row[0];
    vector<string> artist_list;
    artist_list.push_back(row[1]);
    int i=2;
    bool shouldContinue = true;
    while(shouldContinue){
      try{
        stoi(row[i]);	
      }
      catch(exception &err)
      {
        artist_list.push_back(row[i]);
        i++;
        continue;
      }
      if(stoi(row[i]) == 21 || stoi(row[i]) == 70 || row[i] == " 2Pac" || stoi(row[i]) == 347){
        artist_list.push_back(row[i]);
        i++;
        continue;
      }
      else{
      shouldContinue = false;}
    }
    // Populate song with values before pushing into song vector
    temp.artists = artist_list;
    temp.bpm = stoi(row[12+i]);
    temp.danceability = stoi(row[15+i]);
    temp.valence = stoi(row[16+i]);
    temp.energy = stoi(row[17+i]);
    temp.acousticness = stoi(row[18+i]);
    temp.instrumentalness = stoi(row[19+i]);
    temp.liveness = stoi(row[20+i]);
    temp.spechiness = stoi(row[21+i]);
    songs.push_back(temp);
  }

  // Close the file
  infile.close();

  // Collect parameters from the user
  cout << "Enter in a starting song:" << endl;
  string start_song;
  getline(cin, start_song);

  cout << "\nThe following values are measures of each song, enter in which value you would like compared" << endl;
  cout << "bpm\ndanceability\nvalence\nenergy\nacousticness"<<endl;
  cout << "instrumentalness\nliveness\nspeechiness" <<endl; 
  cout << "\nIf you would like a description of each value, enter a ?\n";
  //stored in [15]
  string variable;
  cin >> variable;
  
  if(variable == "?"){
    cout << "\nBPM: Also known as temp, BPM (beats per minute) is the speed or pace of a given composition\n";
    cout << "\nDanceability: Measures how suitable a song is for dancing based on a combination of musical elements including tempo, rhythm stability, beat strength, and overall regularity.\n";
    cout << "\nValence: A measure from 0.0 to 1.0 describing the musical positiveness conveyed by a track.\n";
    cout << "\nEnergy: Song energy is the sense of forward motion in music, whatever keeps the listener engaged and listening.\n";
    cout << "\nAcousticness: This value describes how acoustic a song is. A score of 1.0 means the song is most likely to be an acoustic one.\n";
    cout << "\nInstrumentalness: Prediction of whether a track contains no vocals ranked 0.0-1.0.\n";
    cout << "\nLiveness: Detects the presence of an audience in the recording. Higher liveness values represent an increased probability that the track was performed live.\n";
    cout << "\nSpeechiness: The level of spoken words on a track on a scale from 0-1.0\n\n";

    cout << "\nEnter which value you would like compared:\n";
    cin >> variable;
  }

  cout << "\nHow many songs would you like on this playlist?" << endl;
  int playlistLength;
  cin >> playlistLength;

  cout << "\nHow would you like to sort the list of songs?" << endl<<"M: Merge Sort\nQ: Quick Sort"<<endl;
  string sortMethod;
  cin >> sortMethod;

  // Prompt user for sorting method and calculate time alotted
  float timeTotal;
  if(sortMethod == "M"){
    auto start = high_resolution_clock::now();
    mergeSort(songs, 0, songs.size()-1, variable);  
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    timeTotal = float(duration.count());
  }
  else{
    auto start = high_resolution_clock::now();
    quickSort(songs, 0, songs.size()-1, variable);  
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    timeTotal = float(duration.count());
  }

  vector<song> playlist;
  int position;

  // Find specified song in song list
  for(int a=0; a<songs.size();a++){
    if(songs[a].title == start_song){
      position = a;
    }
  }

  // Create playlist of songs both directly above and below variable
  int d = 1;
  for(int a=0;a<playlistLength;a++){
    if(a%2 == 0){
      playlist.push_back(songs[position+d]);
    }
    else{
      playlist.push_back(songs[position-d]);
      d++;
    }
  }

  // Print out all songs
  cout<<"\nPlaylist of songs with "<<variable<<" of approximately " << songs[position].getType(variable)<< endl;
  for(int p=0; p<playlist.size();p++){
    cout<<playlist[p].title<<endl;
  }

  cout << "\nCalculated in " << timeTotal<<" microseconds"<<endl;
  return 0;
}