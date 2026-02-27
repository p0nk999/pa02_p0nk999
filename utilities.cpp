#include "utilities.h"

using namespace std;

bool startsWith(const string& str, const string& prefix){
    if(prefix.length()>str.length())return false;
    return str.compare(0,prefix.length(), prefix)==0;
}