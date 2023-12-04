#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "songs.h"
using namespace std;

void merge(int left, int mid, int right, vector<song>& songs, string type){
  int const sub1 = mid - left + 1;
  int const sub2 = right - mid;

  vector<song> templ;
  vector<song> tempr;

  for(int i = 0; i < sub1; i++){
    templ.push_back(songs[left + i]);
  }
  for(int j = 0; j < sub2;j++){
    tempr.push_back(songs[mid + 1 + j]);
  }

  int sub1index = 0;
  int sub2index = 0;
  int indexMerge = left;

  while(sub1index < sub1 && sub2index < sub2){
    if(templ[sub1index].getType(type) <= tempr[sub2index].getType(type)){
      songs[indexMerge] = templ[sub1index];
      sub1index++;
    }
    else{
      songs[indexMerge] = tempr[sub2index];
      sub2index++;
    }
    indexMerge++;
  }

  while(sub1index < sub1){
    songs[indexMerge] = templ[sub1index];
    sub1index++;
    indexMerge++;
  }

  while(sub2index < sub2){
    songs[indexMerge] = tempr[sub2index];
    sub2index++;
    indexMerge++;
  }
}

void mergeSort(vector<song> &songs, int start, int finish, string type){
  if(start<finish){
  int mid = (start + finish) / 2;
  mergeSort(songs, start, mid, type);
  mergeSort(songs, mid+1, finish, type);
  merge(start, mid, finish, songs, type);
  }
}

int partition(vector<song> &songs, int left, int right, string type) {
    int pivotIndex = left + (right - left) / 2;
    song pivotValue = songs[pivotIndex];
    int i = left, j = right;
    while(i <= j) {
        while(songs[i].getType(type) < pivotValue.getType(type)) {
            i++;
        }
        while(songs[j].getType(type) > pivotValue.getType(type)) {
            j--;
        }
        if(i <= j) {
          //Swap values
            song temp = songs[i];
            songs[i] = songs[j];
            songs[j] = temp; 
            i++;
            j--;
        }
    }
    return i;
}

void quickSort(vector<song> &songs, int left, int right, string type) {
    if(left < right) {
        int pivotIndex = partition(songs, left, right, type);
        quickSort(songs, left, pivotIndex - 1, type);
        quickSort(songs, pivotIndex, right, type);
    }
}