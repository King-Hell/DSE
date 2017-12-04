// functions to convert from type K to nonnegative integer
// derived from similar classes in SGI STL


#ifndef hash_
#define hash_

#include <iostream>
#include <string>

using namespace std;

template <class K> class mHash;

template<>
class mHash<string>
{
   public:
      size_t operator()(const string theKey) const
      {// Convert theKey to a nonnegative integer.
         unsigned long hashValue = 0; 
         int length = (int) theKey.length();
         for (int i = 0; i < length; i++)
            hashValue = 5 * hashValue + theKey.at(i);
    
         return size_t(hashValue);
      }
};

template<>
class mHash<int>
{
   public:
      size_t operator()(const int theKey) const
      {return size_t(theKey);}
};

template<>
class mHash<long>
{
   public:
      size_t operator()(const long theKey) const
      {return size_t(theKey);}
};

#endif
