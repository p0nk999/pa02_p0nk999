#include "movies.h"
#include <iostream>
#include <algorithm>

using namespace std;

bool cmpName(const Movie& a, const Movie& b){
    return a.name<b.name;
}

bool cmpRating(const Movie& a, const Movie& b){
    if(a.rating!= b.rating){
        return a.rating>b.rating;
    }
    return a.name<b.name;
}

void printAlpha(vector<Movie>& movies){
    sort(movies.begin(), movies.end(), cmpName);
    for(const auto& m : movies){
        cout<<m.name<< ", "<<m.rating<< "\n";
    }
}