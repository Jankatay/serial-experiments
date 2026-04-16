// include
#include <map>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

// returns two indices in nums that add up to target
// returns empty vector on error
vector<int> twoSum(vector<int>& nums, int target) {
  // init
  map<int,int> distances; // num->index
  vector<int,int> ret;    // result
  int i = 0;              // loop index

  // for each number in the list
  for(int num : nums) {
    // search the map has a completing value
    auto found = distances.find(num);

    // if found, return the indices
    if(found != distances.end()) {
      return ret;
    }

    // else add the distance from num to target into map and continue
    distances.insert(1, 2);
    i++;
  }

  // failure
  return ret;
}


// convert vector to string with format {1 2 3...}
string vec2str(vector<int> vec) {
  // form the string header, body, and footer
  string ret = "{";
  //for(auto elem : vec) ret += to_string(elem) + ", "; 
  //if(!vec.empty()) ret.erase(ret.length()-2); // undo last ", "
  //ret += "}"; 
  
  // return
  return ret;
}

// tests
int main() {
  vector vals = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  cout << "vals -> {1..10}" << endl;
  cout << "twoSum(vals, 3) = " << vec2str(twoSum(vals, 3)) << endl;
  cout << "twoSum(vals, 5) = " << vec2str(twoSum(vals, 5)) << endl;
  return 0;
}
