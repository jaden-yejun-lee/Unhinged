#ifndef _RADIXTREE_H_
#define _RADIXTREE_H_
#include <map>
#include <string>
#include <iostream>
using namespace std;


template <typename ValueType>
class RadixTree {

public:
    RadixTree() {
        root = new Node();
    }
    ~RadixTree() {
        finish(root);
    }
    void insert(string key, const ValueType& value) {
        Node* ptr = root;
        Node* parent;

        ValueType* keyValue = new ValueType(value);
        int index;
        int CIndex;
        int length = key.length();
        for (int i = 0; i < length;) {
            index = map(key, 0);
            // if the slot in the Pair array is empty, just insert
            if (ptr->suffix[index] == nullptr) {
                Node* node = new Node();
                node->prefix = key;
                node->v = keyValue;
                node->hasValue = true;
                ptr->suffix[index] = node;
                return;
            }
            parent = ptr;
            ptr = ptr->suffix[index];
            string compare = ptr->prefix;
            CIndex = differentIndex(key, compare);
            // if index is equal to CIndex, update the value
            if (CIndex == -1) {
                if (ptr->v != nullptr) {
                    delete ptr->v;
                }
                ptr->v = keyValue;
                ptr->hasValue = true;
                return;
            }
            // if compare is a prefix to key repeat until suffix can be inserted
            if (CIndex == -2) {
                key = key.substr(compare.length());
                i += compare.length();
                continue;
            }
            // if they are different, substring both of them and move them to different spots in hash table
            if (CIndex >= 0) {
                string prefix = compare.substr(0, CIndex);
                string sCompare = compare.substr(CIndex);
                string sKey = key.substr(CIndex);
                Node* next = new Node();
                next->prefix = prefix;
                if (sKey.empty()) {
                    next->hasValue = true;
                    next->v = keyValue;
                    parent->suffix[index] = next;
                    ptr->prefix = sCompare;
                    int suffixCompareIndex = map(sCompare, 0);
                    next->suffix[suffixCompareIndex] = ptr;
                    return;
                }
                // if not create a new main node and attach it to the right spot
                else {
                    next->hasValue = false;
                    next->v = nullptr;
                    parent->suffix[index] = next;
                    ptr->prefix = sCompare;
                    int suffixCompareIndex = map(sCompare, 0);
                    next->suffix[suffixCompareIndex] = ptr;
                    Node* keyNode = new Node();
                    keyNode->prefix = sKey;
                    keyNode->hasValue = true;
                    keyNode->v = keyValue;
                    int suffixKeyIndex = map(sKey, 0);
                    next->suffix[suffixKeyIndex] = keyNode;
                    return;
                }
            }
        }
        return;
    }

    ValueType* search(string key) const {
        Node* n = root;
        string copy = key;
        if (key.empty()) {
            return nullptr;
        }
        while (true) {
            int index = map(copy, 0);
            if (n->suffix[index] == nullptr) {
                return nullptr;
            }
            else {
                // iterate through table
                n = n->suffix[index];
                string c = n->prefix;
                // if c is longer than the key, then the key is null
                if (c.length() > copy.length()) {
                    return nullptr;
                }
                // remove prefix
                if (copy.substr(0, c.length()) == c) {
                    copy = copy.substr(c.length());
                }
                else {
                    return nullptr;
                }
                // if the key is empty, return null
                if (copy.empty()) {
                    if (!n->hasValue) {
                        return nullptr;
                    }
                    // return valuetype pointer
                    ValueType* ptr = n->v;
                    return ptr;
                }
            }
        }
    }

    private:
        struct Node {

            string prefix;
            bool hasValue;
            ValueType* v;
            Node* suffix[128];

            Node() {
                prefix = "";
                hasValue = false;
                v = nullptr;
                for (int i = 0; i < 128; ++i) {
                    suffix[i] = nullptr;
                }
            }

            ~Node() {
                if (v != nullptr) {
                    delete v;
                    v = nullptr;
                    hasValue = false;
                }
            }

        };

        int map(string s, int i) const {
            char firstChar = s[i];
            return firstChar % 128;
        }

        void finish(Node* node) {

            if (node == nullptr)
                return;
            for (int i = 0; i < 128; i++) {
                finish(node->suffix[i]);
            }
            if (node->v != nullptr) {
                delete node->v;
                node->v = nullptr;
                node->hasValue = false;
                delete node;
                node = nullptr;
            }
        }

        int differentIndex(const string key, const string comp) {

            int i;

            if (key == comp) {
                return -1;
            }

            for (i = 0; i != key.length(); i++) {

                if (i == comp.length()) {
                    return -2;
                }
                // find first index where they are different
                if (key[i] != comp[i]) {
                    break;
                }
            }
            return i;
        }
      
        Node* root;

};

#endif