// Winter'24
// Instructor: Diba Mirza
// Student name: Fengxun Li
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <sstream>
using namespace std;

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if(argc < 2){
        cerr<<"Not enough arguments provided (need at least 1 argument)."<<endl;
        cerr<<"Usage: "<<argv[ 0 ]<<" moviesFilename prefixFilename "<<endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if(movieFile.fail()){
        cerr<<"Could not open file "<<argv[1];
        exit(1);
    }
  
    // Create an object of a STL data-structure to store all the movies
    vector<Movie> movies;
    string line, movieName;
    double movieRating;
    
    // Read each file and store the name and rating
    while(getline (movieFile, line) && parseLine(line, movieName, movieRating)){
            // Use std::string movieName and double movieRating
            // to construct your Movie objects
            // cout<<movieName<<" has rating "<<movieRating<<endl;
            // insert elements into your data structure
            movies.push_back({movieName, movieRating});
    }

    movieFile.close();


    // Sort
    sort(movies.begin(), movies.end(), cmpName);

    // Part 1
    if(argc == 2){
        for(const auto& m : movies){
            cout << m.name << ", " << m.rating << "\n";
        }
        return 0;
    }



    ifstream prefixFile (argv[2]);

    if(prefixFile.fail()){
        cerr<<"Could not open file "<<argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while(getline (prefixFile, line)){
        if(!line.empty()){
            prefixes.push_back(line);
        }
    }
    prefixFile.close();

    
    //clock_t tStart=clock();

    //store the best movie of each prefix
    vector<string> bestMoviesOutput;

    //  For each prefix,
    for(const string& prefix : prefixes){
        vector<Movie> matches;
        
        Movie dummy;
        dummy.name = prefix;
        
        // (O(log N))  find the first movie with given prefix
        auto it = lower_bound(movies.begin(), movies.end(), dummy, cmpName);
        
        while(it != movies.end() && startsWith(it->name, prefix)){
            matches.push_back(*it);
            ++it;
        }

        //  If no movie with that prefix exists print the following message
        if(matches.empty()){
            cout<<"No movies found with prefix "<<prefix<<endl;
        } else {
            sort(matches.begin(), matches.end(), cmpRating);
            
            for(const auto& m : matches){
                cout << m.name << ", " << m.rating << endl;
            }

            stringstream ss;
            ss << "Best movie with prefix " << prefix << " is: " << matches.front().name 
               << " with rating " << fixed << setprecision(1) << matches.front().rating;
            bestMoviesOutput.push_back(ss.str());
        }
    }


    for(const string& bestMsg : bestMoviesOutput){
        cout << bestMsg << endl;
    }





    //clock_t tEnd=clock();
    //double duration=(double)(tEnd-tStart) / CLOCKS_PER_SEC * 1000.0;
    
    //cout<<"\n[Run Time for Part 2: "<<(int)duration<<" ms]\n";

    return 0;
}










/*
 * 3A:
 * Time Complexity: O(m * l * (n + k log k))
 * m prefix in total, For each prefix the code perform a linear scan through all 'n' movies. 
 * Checking if a movie string starts with a prefix takes up to 'l' comparisons in the worst case, 
 * making the scan O(n * l). After finding up to 'k' matches, the code sort them. 
 * Sorting 'k' elements takes O(k log k) comparisons, 
 * and each string comparison takes up to 'l' operations, making the sort O(k log k * l). 
 * Multiplying by 'm' prefixes gives O(m * (n * l + k log k * l)).
 *-input_20_random.csv: 48 ms
 *-input_100_random.csv: 61 ms
 *-input_1000_random.csv: 189 ms
 *-input_76920_random.csv: 8295 ms
 * 
 * 3B:
 * Space Complexity: O(k * l)
 * For each prefix query, the code create a temporary vector to hold up to 'k' matching Movie objects.
 * Since each movie name can be up to 'l' characters long, 
 * the additional space required to hold these matches in memory is O(k * l).
 *
 * 3C:
 * I designed my algorithm primarily for a low space complexity. I kept the dataset in a vector.
 * I was not able to achieve a low time complexity. Because the vector has unsorted prefixes, 
 * the algorithm is forced to do a full O(n) linear scan for every single time. 
 * While this saves space, it makes the time complexity high.
 */

bool parseLine(string &line, string &movieName, double &movieRating){
    int commaIndex=line.find_last_of(",");
    movieName=line.substr(0, commaIndex);
    movieRating=stod(line.substr(commaIndex+1));
    if(movieName[0] == '\"'){
        movieName=movieName.substr(1, movieName.length()-2);
    }
    return true;
}