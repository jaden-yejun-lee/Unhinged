#include "MemberDatabase.h"
#include "PersonProfile.h"
#include <fstream>
#include <iostream>
#include <sstream>

MemberDatabase::MemberDatabase() {
	
}

MemberDatabase::~MemberDatabase() {
	
}


bool MemberDatabase::LoadDatabase(string filename) {
	
	ifstream file;
	file.open(filename);

	if (file) {
		string curLine;
		string name;
		string email;
		string pair;
		string attribute;
		string value;
		vector<AttValPair> v;
		int numPairs = 0;
		int lineNum = 1;
		while (getline(file, curLine)) {
  
			if (curLine == "") {
				lineNum = 0;
				lineNum++;
			}
			else {
				
				switch (lineNum) {
				case 0:
					lineNum++;
					break;
				case 1:
					name = curLine;
					lineNum++;
					break;
				case 2:
					email = curLine;
					lineNum++;
					break;
				case 3:
					numPairs = stoi(curLine);
					lineNum++;
					break;			
				default: // default is rest of attribute value pairs
					PersonProfile* a = new PersonProfile(name, email);

					if (numPairs > 0)
					{
						stringstream ss(curLine);
						getline(ss, attribute, ',');
						getline(ss, value, '\n');
						pair = attribute + "," + value;
						a->AddAttValPair(AttValPair(attribute, value));			
						auto itr = memberVector.search(pair);
						if (itr == nullptr) {
							vector<string> temp;
							temp.push_back(email);
							memberVector.insert(pair, temp);
						}

						else {
							itr->push_back(email);
						}
						// cerr << "Name: " << name << ", Email: " << email << ", Number: " << numPairs << ", Attribute: " << attribute << ", Value: " << value << endl;
					}


					for (int i = 0; i < numPairs - 1; i++) {
						if (getline(file, curLine)) {
							stringstream s(curLine);
							getline(s, attribute, ',');
							getline(s, value, '\n');
							pair = attribute + "," + value;
							a->AddAttValPair(AttValPair(attribute, value));
							auto itr = memberVector.search(pair);
							
							if (itr == nullptr) {
								vector<string> temp;
								temp.push_back(email);
								memberVector.insert(pair, temp);
							}

							else {
								itr->push_back(email);
							}
							// cerr << "Name: " << name << ", Email: " << email << ", Number: " << numPairs << ", Attribute: " << attribute << ", Value: " << value << endl;

						}
					}

					m_emails.insert(a->GetEmail(), a);
					lineNum++;
					break;
				}
			}

		}
		
		return true;
	}
	else {
		cerr << "unable to open";
		return false;
	}
	
}


vector<string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const {
	string pair = input.attribute + "," + input.value;

	if (memberVector.search(pair) == nullptr) {
		cerr << "empty vector returned" << endl;
		vector<string> empty;
		return empty;
	}
	vector <string>* test = memberVector.search(pair);
	for (int i = 0; i != (*test).size(); i++) {
		 //cerr << (*memberVector.search(pair))[i] << endl;
	}
	return *memberVector.search(pair);	
}

const PersonProfile* MemberDatabase::GetMemberByEmail(string email) const {

	if ((m_emails.search(email)) == nullptr) {
		 cerr << "no member with that email - returned nullptr" << endl;
		return nullptr;
	}
	// cerr << "Number of AttValPairs: " << (*m_emails.search(email))->GetNumAttValPairs() << endl;

	return (*m_emails.search(email));


}

