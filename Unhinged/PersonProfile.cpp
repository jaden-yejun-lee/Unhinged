#include "PersonProfile.h"
#include <iostream>
PersonProfile::PersonProfile(string name, string email) {
	m_name = name;
	m_email = email;

}

string PersonProfile::GetName() const{
	return m_name;
}

string PersonProfile::GetEmail() const {
	return m_email;
}



void PersonProfile::AddAttValPair(const AttValPair& attval) {

	m_tree.insert(attval.attribute, attval.value);


		bool isDuplicate = false;
		auto it = m_personVector.begin();
		while (it != m_personVector.end()) {
			if (attval.attribute == (it->attribute) && attval.value == (it->value)) {
				isDuplicate = true;
			}
			it++;
		}

		if (isDuplicate == false) {
			m_personVector.push_back(attval);
		}

}


int PersonProfile::GetNumAttValPairs() const {

	// cerr << "Number of AttValPairs: " << m_personVector.size() << endl << endl;
	return m_personVector.size();
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const {
	
	int x = m_personVector.size();
	if (attribute_num < 0 || attribute_num >= x) {
		return false;
	}

	if (m_personVector[attribute_num].attribute != "" && m_personVector[attribute_num].value != "") {
		attval = m_personVector[attribute_num];
		// cerr << "GetAttVal: Attribute = " << m_personVector[attribute_num].attribute << endl;
		// cerr << "GetAttVal: Value = " << m_personVector[attribute_num].value << endl << endl;
		return true;
	}
	// cerr << "no att val pair here";
	return false;

}

PersonProfile::~PersonProfile() {

}

