/*
 * Problem for Testing Template : https://www.acmicpc.net/problem/5052
 * Test : Accepted
 * Last Updated : 2023.04.01 10:40 PM (KST)
 */
namespace Trie{
    struct Node{
        char data;
        map<char, Node*> _next;
        Node() { }
        ~Node() { for(auto &i: _next) delete i.second; }
        Node* insert(char x){ if(!find(x)) _next[x] = new Node(); return _next[x]; }
        Node* next(char x){ return _next.count(x) ? _next[x] : nullptr; }

        bool find(char x){ return _next.count(x) != 0; }
        bool end(){ return _next.count(0); }
    } *root = new Node();
    int words = 0;

    bool insert(const string &word){
        bool prefix_exist = false;
        Node *cursor = root;
        for (int i = 0; i < (int)word.size(); i++) {
            cursor = cursor->insert(word[i]);
            if(cursor->end()) prefix_exist = true;
        }
        if(!cursor->end()) {
            cursor->insert(0);
            ++words;
            if(cursor->_next.size() > 1) prefix_exist = true;
        }
        return prefix_exist;
    }
    
    bool find(const string &str) {
        Node *cursor = root;
        for (int i = 0; i < (int)str.size(); i++) {
            if(!cursor->find(str[i])) return false;
            cursor = cursor->next(str[i]);
        }
        return cursor->end();
    }

    void clear() {
        delete root;
        root = new Node();
        words = 0;
    }
}