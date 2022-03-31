#ifndef _PERSONPROFILE_H_
#define _PERSONPROFILE_H_

#include "provided.h"
#include "RadixTree.h"
#include <vector>
#include <set>

using namespace std;

class PersonProfile {
public:
	PersonProfile(string name, string email);
	~PersonProfile();
	string GetName() const;
	string GetEmail() const;
	void AddAttValPair(const AttValPair& attval);
	int GetNumAttValPairs() const;
	bool GetAttVal(int attribute_num, AttValPair& attval) const;

	

private:
	string m_name;
	string m_email;
	RadixTree<string> m_tree;	
	vector<AttValPair> m_personVector;
};

#endif