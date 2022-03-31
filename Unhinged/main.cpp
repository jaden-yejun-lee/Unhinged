//main.cpp

#define _CRT_MAP_ALLOC
#include <stdlib.h>
#include "PersonProfile.h"
#include "AttributeTranslator.h"
#include "RadixTree.h"
#include "MemberDatabase.h"
#include "MatchMaker.h"
#include "provided.h"
#include <iostream>
#include <string>
#include <vector>

const std::string MEMBERS_FILE = "members.txt";
const std::string TRANSLATOR_FILE = "translator.txt";

bool findMatches(const MemberDatabase& mdb, const AttributeTranslator& at);

int main() {
    MemberDatabase mdb;
    if (!mdb.LoadDatabase(MEMBERS_FILE))
    {
        std::cout << "Error loading " << MEMBERS_FILE << std::endl;
        return 1;
    }
    AttributeTranslator at;
    if (!at.Load(TRANSLATOR_FILE))
    {
        std::cout << "Error loading " << TRANSLATOR_FILE << std::endl;
        return 1;
    }

    while (findMatches(mdb, at))
        ;

    std::cout << "Happy dating!" << std::endl;
}

bool findMatches(const MemberDatabase& mdb, const AttributeTranslator& at)
{
    // Prompt for email
    std::string email;
    const PersonProfile* pp;
    for (;;) {
        std::cout << "Enter the member's email for whom you want to find matches: ";
        std::getline(std::cin, email);
        if (email.empty())
            return false;
        pp = mdb.GetMemberByEmail(email);
        if (pp != nullptr)
            break;
        std::cout << "That email is not in the member database." << std::endl;
    }

    // Show member's attribute-value pairs
    std::cout << "The member has the following attributes:" << std::endl;
    for (int k = 0; k != pp->GetNumAttValPairs(); k++) {
        AttValPair av;
        pp->GetAttVal(k, av);
        std::cout << av.attribute << " --> " << av.value << std::endl;
    }

    // Prompt user for threshold
    int threshold;
    std::cout << "How many shared attributes must matches have? ";
    std::cin >> threshold;
    std::cin.ignore(10000, '\n');

    // Print matches and the number of matching translated attributes
    MatchMaker mm(mdb, at);
    std::vector<EmailCount> emails = mm.IdentifyRankedMatches(email, threshold);
    if (emails.empty())
        std::cout << "No member was a good enough match." << std::endl;
    else {
        std::cout << "The following members were good matches:" << std::endl;;
        for (const auto& emailCount : emails) {
            const PersonProfile* pp = mdb.GetMemberByEmail(emailCount.email);
            std::cout << pp->GetName() << " at " << emailCount.email << " with "
                << emailCount.count << " matches!" << std::endl;
        }
    }
    std::cout << std::endl;
    return true;
}


//void listCompatiblePairs(const AttributeTranslator& translator) {
//	AttValPair att("favorite_food", "del taco");
//	std::vector<AttValPair> result =
//		translator.FindCompatibleAttValPairs(att);
//	if (!result.empty()) {
//		std::cout << "Compatible attributes and values:" << std::endl;
//		for (const auto& p : result)
//			std::cout << p.attribute << " -> " << p.value << std::endl;
//	}
//}

void findMatches(const MatchMaker& mm,
	const std::string& member_email,
	int threshold) {
	std::vector<EmailCount> results =
		mm.IdentifyRankedMatches(member_email, threshold);
	if (results.empty())
		std::cout << "We found no one who was compatible :-(" << std::endl;
	else {
		for (const auto& match : results) {
			std::cout << match.email << " has " << match.count
				<< " attribute-value pairs in common with "
				<< member_email << std::endl;
		}
	}
}

//int main() {
//	//PersonProfile bob("bob", "bob@gmail.com");
//	//AttValPair a("hobby", "rock climbing");
//	//AttValPair b("hobby", "shitting");
//	//AttValPair c("hobby", "shitting");
//	//AttValPair d("job", "plumber");
//	//bob.AddAttValPair(a);
//	//bob.AddAttValPair(b);
//	//bob.AddAttValPair(c);
//	//bob.AddAttValPair(d);
//
//	//bob.GetAttVal(0, a);
//
//	 //MemberDatabase mdb;
//	 //mdb.LoadDatabase("test.txt");
//	 //AttValPair ab("hobby", "canyoneering");
//	 //AttValPair cd("likes", "reviewing code");
// 	 // mdb.FindMatchingMembers(ab);
//	 //mdb.FindMatchingMembers(cd);
//	 //cerr << endl;
//	 //mdb.GetMemberByEmail("anisha@gmail.com");
//
//	// AttributeTranslator adb;
//	// adb.Load("translatortest.txt");
//	// AttValPair abc("job", "lawyer");
//	// adb.FindCompatibleAttValPairs(abc);
//
//
//	//MemberDatabase mdb;
//	//mdb.LoadDatabase("members.txt");
//	//AttValPair ab("hobby", "slacklining");
//	//mdb.FindMatchingMembers(ab);
//
//
//	MemberDatabase m;
//	m.LoadDatabase("test.txt");
//	AttributeTranslator a;
//	a.Load("translatortest.txt");
//	MatchMaker k(m, a);
//	findMatches(k, "anisha@gmail.com", 2);
//
//	
//}