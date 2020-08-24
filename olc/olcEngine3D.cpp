/****************************************************************
 *   CHEFSTR1 Problem from codechef.com July 2020 Challenge Div 2
 *   https://www.codechef.com/JULY20B/problems/CHEFSTR1
 *   Solution by: Remi Coussement
 ***************************************************************/
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int num_testcases, num_strings_plucked;
    vector<int> results;

    // enter the test case
    cin >> num_testcases;

    // iterate through test cases
    for(int i=0; i<num_testcases; i++){
        // get the number of strings plucked for current test case
        cin >> num_strings_plucked;

        // holds the strings for current test case
        int strings[num_strings_plucked];

        // input and error check values from standard input
        for(int j=0; j<num_strings_plucked; j++){
            cin >> strings[j];
        }

        // holds current result
        int sum = 0;

        // solve for current case
        for(int j=1; j<num_strings_plucked; j++){
            sum += abs(strings[j] - strings[j-1]) - 1;
            cout << abs(strings[j] - strings[j-1]) - 1 << "\t" << sum << endl;
        }

        // stores the results
        results.push_back(sum);
    }

    cout << endl << endl;

    for(int i=0; i<results.size(); i++){
        cout << results[i] << endl;
    }

    return 0;
}