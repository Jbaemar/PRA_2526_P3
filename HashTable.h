#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2526_P1/ListLinked.h"  

using namespace std;
template <typename V>

class HashTable: public Dict<V> {

    private:

        int n;
        int max;
        ListLinked<TableEntry<V>>* table;

        int h(std::string key){//Cáulcula el índice de la tabla hash para una clave dada.

            int sum = 0;
            for(int i = 0; i < key.length(); i++){
                sum += int(key[i]);
            }
            return sum % max;
        }

        

    public:
        HashTable(int size){
            max = size;
            n = 0;
            table = new ListLinked<TableEntry<V>>[max];
        }
        
        ~HashTable(){
            delete[] table;
        }
        

        V search(std::string key) override{
            int index = h(key);
            TableEntry<V> te(key);
            int pos = table[index].search(te);
            if(pos == -1){
                throw runtime_error("Clave no encontrada");
            }
            return table[index].get(pos).value;

        }

        void insert(std::string key, V value) override{
            int index = h(key);
            TableEntry<V> te(key, value);
            int pos = table[index].search(te);
            if(pos != -1){
                throw runtime_error("Clave ya existente");
            }
            table[index].append(te);
            n++;
            
        }

        V remove(std::string key) override{
            int index = h(key);
            TableEntry<V> te(key);
            int pos = table[index].search(te);
            if(pos == -1){
                throw runtime_error("Clave no encontrada");
            }
            return table[index].remove(pos).value;
        }

        int entries() override{
            return n;
        }

        int capacity(){
            return max;
        }

        friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
            for(int i = 0;i < th.max; i++){
                out << "Indice " << i << ": " << th.table[i] << "\n";
            }
            return out;
        }
        
        V operator[](std::string key){
            return search(key);
        }
};

#endif