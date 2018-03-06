#ifndef redBlackTree_
#define redBlackTree_

#include<iostream>
#include"bsTree.h"
using namespace std;
template <class K,class E>
class redBlackTree :public bsTree<K,E>{
public:
	pair<const K, E>* find(const K& theKey) const;
	void insert(const pair<const K,E>& thePair);
	void erase(const K& theKey);
};

template<class K,class E>
pair<const K, E>* redBlackTree<K,E>::find(const K& theKey) const {
	
}

template<class K,class E>
void redBlackTree<K,E>::insert(const pair<const K, E>& thePair) {

}

template<class K,class E>
void redBlackTree<K, E>::erase(const K& theKey) {

}
#endif