//============================================================================
// Name        : 150160223.cpp
// Author      : Selin Eylul Bilen
//============================================================================
#include <iostream>
#include <fstream>
#include <cmath>
#include <stdio.h>
#include <string>
#include <math.h>
//#include <stdlib.h>
using namespace std;

// Utility function for  
// converting degrees to radians 
float toRadians(float degree)
{ 
    // cmath library in C++  
    // defines the ant 
    // M_PI as the value of 
    // pi accurate to 1e-30 
    float one_deg = (M_PI) / 180; 
    return (one_deg * degree); 
} 
  void heapify(float arr[], string cty[], int a, int b)
  {
      int lrgst = b;
      int left = 2*b + 1;
      int right = 2*b + 2;
   
      if (left < a && arr[left] > arr[lrgst]){lrgst = left;}
      if (right < a && arr[right] > arr[lrgst]){lrgst = right;}
      if (lrgst != b){
          swap(arr[b], arr[lrgst]);
          swap(cty[b], cty[lrgst]);
          heapify(arr, cty, a, lrgst);
      }
  }

  void heapSort(float arr[], string cty[], int x){
      int a = x / 2 - 1;
      while(a >= 0){
          heapify(arr, cty, x, a);
          a--;
      }
      int c=x-1;
      while(c>=0){
          swap(arr[0], arr[c]);
          swap(cty[0], cty[c]);
          heapify(arr, cty, c, 0);
          c--;
      }
  }
float distance(float lat1, float long1, float lat2, float long2){

    lat1 = toRadians(lat1); 
    long1 = toRadians(long1); 
    lat2 = toRadians(lat2); 
    long2 = toRadians(long2);
    float dlong = long2 - long1; 
    float dlat = lat2 - lat1; 
  
    float ans = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlong / 2), 2);
    ans = 2 * asin(sqrt(ans)); 
  
    // Radius of Earth in  
    // Kilometers, R = 6371 
    // Use R = 3956 for miles 
    float R = 6371; 
      
    // Calculate the result 
    ans = ans * R; 
  
    return ans; 
}

using std::strtol;
int main(int argc, char* argv[]){
    clock_t t;
    t=clock();
if (argc == 5){
	string line;
    ifstream myfile("location.txt");
	int N;
	int K;
	float lat;
	float lon;
	N = atof(argv[1]);
	K = atof(argv[2]);
	lat = atof(argv[3]);
	lon = atof(argv[4]);
	string cty[N];
	float dis[N];
	float *arr = new float[N];
	int i = 0;

  int j= 0;
  if(myfile.is_open()){
	  while (getline(myfile, line)){
          if(j<N){
            unsigned pos = line.find("\t");
              string city = line.substr(0,pos);
              line = line.substr(pos+1);
              pos = line.find("\t");
              float latitude = atof(line.substr(0,pos).c_str());
              arr[i] = latitude;
              line = line.substr(pos+1);
              float longitude = atof(line.substr(0,pos).c_str());
              arr[i + 1] = longitude;
              cty[i] = city;
              i++;
          }
          j++;
	  }
	  myfile.close();	
	  int sz = N;
	  cout << setprecision(15) << fixed;
      for (int i = 0; i < sz; i++){
          dis[i] = distance(arr[i], arr[i+1],  lat, lon);
      }
      heapSort(dis, cty, N);
	  string outName= "sorted.txt";
      ofstream Out;
      Out.open(outName.c_str());
      for (int i = 0; i < K; i++){
          Out<<cty[i];
          Out<<"\t";
          Out<<dis[i]<<endl;
      }
      Out.close();
      t = clock()+t;
      cout<<(float(t)/CLOCKS_PER_SEC)<<endl;
    }
    else
	  cout << "File could not be opened." << endl; 
    return 0;
    }
    else{cout << "invalid input" << endl;}
}

