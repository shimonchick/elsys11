#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

int main(int argc, char const *argv[])
{
    bool is_integer_only = false, is_strict = false;
    //cout << "argc: " << argc << endl;
    for(int i = 0; i < argc; i++){
        if(strcmp(argv[i], "--strict") == 0) is_strict = true;
        if(strcmp(argv[i], "--integer-only") == 0) is_integer_only = true;
    }
    ifstream file(argv[1]);

    bool first = true;
    float sum = 0, count = 0;
    float min, max;
    vector<float> nums;
    for(string n; file >> n;){ 
        try{
            float number;
            if(is_integer_only){
                number = (float)stoi(n);
            } else{
                number = stof(n);
            }
            if(first){
                first = false;
                min = number;
                max = number;
            }
            if(number < min) min = number;
            if(number > max) max = number;
            nums.push_back(number);
            sum += number;
            count++;

        }catch(invalid_argument a){
            if(is_strict){
                if(is_integer_only){
                    cout << "ERR: PROVIDE ONLY INTEGERS";
                    return -1;
                }
                cout << "ERR: PROVIDE ONLY NUMBERS";
                return 1;
            }
        }
    }
    if(is_integer_only){
        int min = (int)min;
        int max = (int)max;
      //  cout << "integer only set";
        cout << min << " " << max << " " << (int)sum/count;
    }
    cout << min << " " << max << " " << sum/count;

    return 0;
}
