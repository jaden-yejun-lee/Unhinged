#ifndef _MATCHMAKER_H_
#define _MATCHMAKER_H_

#include <iostream>
#include "provided.h"
#include "AttributeTranslator.h"
#include "MemberDatabase.h"

class MatchMaker {
public:
	MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
	~MatchMaker();
	vector<EmailCount> IdentifyRankedMatches(string email, int threshold) const;

private:
	MemberDatabase* m_mdb;
	AttributeTranslator* m_at;
};


#endif