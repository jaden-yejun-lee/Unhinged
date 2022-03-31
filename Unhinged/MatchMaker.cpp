#include "MatchMaker.h"
#include "provided.h"
#include <vector>
#include <unordered_set>
#include <iostream>
#include <algorithm>

using namespace std;

MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at) {
	m_mdb = new MemberDatabase(mdb);
	m_at = new AttributeTranslator(at);
}

MatchMaker::~MatchMaker() {

}


vector<EmailCount> MatchMaker::IdentifyRankedMatches(string email, int threshold) const {

	// retrieve person's PersonProfile from email 
	const PersonProfile* p = m_mdb->GetMemberByEmail(email);


	// obtain person's attribute-value pairs
	// push unique compatible attribute-value pairs into pairVectors
	vector<AttValPair> pairVectors;
	if (p != nullptr) {
		for (int i = 0; i < p->GetNumAttValPairs(); i++) {
			AttValPair pair;
			p->GetAttVal(i, pair);
			vector<AttValPair>tempVector = m_at->FindCompatibleAttValPairs(pair);
			for (int j = 0; j != tempVector.size(); j++) {
				auto itr = find(pairVectors.begin(), pairVectors.end(), tempVector[j]);
				if (itr == pairVectors.end()) {
					pairVectors.push_back(tempVector[j]);
				}
			}
		}
	}

	// iterate through compatible attributes and match attribute with
	// collection of members that have each compatible attribute-value pair

	auto it = pairVectors.begin();
	
	map<string, int> m_map;
	vector<EmailCount> emailCollection;

	while (it != pairVectors.end()) {

		AttValPair find(it->attribute, it->value);
		vector<string> matchingEmails = m_mdb->FindMatchingMembers(find);

		for (int i = 0; i != matchingEmails.size(); i++) {

			string s = matchingEmails[i];

			if (s == email) {
				continue;
			}

			auto found = m_map.find(s);
			if (found == m_map.end()) {
				m_map.insert(pair<string, int>(s, 1));

			}
			else {
				found->second++;
			}
		}

		it++;
	}


	// create a collection of members that have at least the 
	// threshold number of compatible attribute-value pairs
	for (auto it = m_map.begin(); it != m_map.end(); it++) {

		EmailCount tempEC(it->first, it->second);
		emailCollection.push_back(tempEC);

	}

	// sort in descending order with ties broken by ascending alphabetical order
	sort(emailCollection.begin(), emailCollection.end(), [](EmailCount x, EmailCount y) {
		if (x.count == y.count) {
			return x.email < y.email;
		}
		else {
			return x.count > y.count;
		}
		});

	vector<EmailCount> v;
	for (int i = 0; i != emailCollection.size(); i++) {
		if (emailCollection[i].count >= threshold) {
			//insert
			v.push_back(emailCollection[i]);
		}
	}

	return v;
}

