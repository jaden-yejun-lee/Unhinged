#ifndef _MEMBERDATABASE_H_
#define _MEMBERDATABASE_H_

#include "provided.h"
#include "PersonProfile.h"
#include "RadixTree.h"
#include <vector>
#include <set>

using namespace std;

class MemberDatabase {
public:
	MemberDatabase();
	~MemberDatabase();

	bool LoadDatabase(string filename);
	vector<string> FindMatchingMembers(const AttValPair& input) const;
	const PersonProfile* GetMemberByEmail(string email) const;


private:
	RadixTree<PersonProfile*> m_emails;
	RadixTree<vector<string>> memberVector;
};



#endif
 