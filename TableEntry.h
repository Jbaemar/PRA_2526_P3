#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

using namespace std;
template <typename V>

class TableEntry {
    public:
        string key;
        V value;

        TableEntry(string key, V value){//Constructor al que se le pasa la clave y el valor
            this->key = key;
            this->value = value;
        }

        TableEntry(string key){//Constructor al que se le pasa solo la clave
            this->key = key;
            this->value = V();
        }

        TableEntry(){//Constructor por defecto
            this->key = "";
            this->value = V();
        }

        friend bool operator==(const TableEntry<V> &te1, const TableEntry<V> &te2){//compara dos TableEntry por su clave
            return te1.key == te2.key;
        }

        friend bool operator!=(const TableEntry<V> &te1, const TableEntry<V> &te2){//compara dos TableEntry por su clave
            return te1.key != te2.key;
        }

        friend ostream& operator<<(ostream &os, const TableEntry<V> &te){//sobrecarga del operador de salida que imprime la clave y el valor
            os << "{" << te.key << ": " << te.value << "}";
            return os;
        }
    
};

#endif