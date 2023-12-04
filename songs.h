#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class song{
public:
  string title;
  vector<string> artists;
  int bpm;
  int danceability;
  int valence;
  int energy;
  int acousticness;
  int instrumentalness;
  int liveness;
  int spechiness;
  string getName(){return title;};

  int getType(string type){
    if (type == "bpm"){
      return bpm;
    }else if(type == "danceablility"){
      return danceability;
    }else if(type == "valence"){
      return valence;
    }else if(type == "energy"){
      return energy;
    }else if(type == "acousticness"){
      return acousticness;
    }else if(type == "instrumentalness"){
      return instrumentalness;
    }else if(type == "liveness"){
      return liveness;
    }else if(type == "spechiness"){
      return spechiness;
    }else{
      return 0; 
    }
  }
};