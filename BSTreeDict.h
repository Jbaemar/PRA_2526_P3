#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"
using namespace std;

template <typename V>
class BSTreeDict: public Dict<V> {

    private:
        
        BSTree<TableEntry<V>>* tree;


    public:

        BSTreeDict(){
            tree = new BSTree<TableEntry<V>>();
        }

        ~BSTreeDict(){
            delete tree;
        }

        void insert(string key, V value) override{
            TableEntry<V> te(key, value);
            tree->insert(te);
        }

        V search(string key) override{
            TableEntry<V> te(key);
            return tree->search(te).value;
        }

        V remove(string key) override{
            TableEntry<V> te(key);
            V val = tree->search(te).value;
            tree->remove(te);
            return val;
        }

        int entries() override{
            return tree->size();
        }

        friend ostream& operator<<(ostream &out, const BSTreeDict<V> &bs){
            out << *(bs.tree);
            return out;
        }

        V operator[](string key){
            TableEntry<V> te(key);
            return tree->search(te).value;
        }


        
        
};

#endif