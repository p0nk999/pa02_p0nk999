#ifndef MOVIES_H
#define MOVIES_H

#include <string>
#include <vector>

using namespace std;

struct Movie{
    string name;
    double rating;
};

bool cmpName(const Movie& a, const Movie& b);
bool cmpRating(const Movie& a, const Movie& b);
void printAlpha(vector<Movie>& movies);

#endif 