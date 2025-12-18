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
//Esta clase implementará la interfaz Dict<V> mediante una tabla hash con encadenamiento. 
//Más concretamente, la tabla hash se implementará como un array de punteros a listas de tipo ListLinked<T>
class HashTable: public Dict<V> {

    private:

        int n; //numero actual de entradas
        int max;//capacidad máxima de la tabla
        ListLinked<TableEntry<V>>* table;//array de listas enlazadas

        int h(std::string key){//Cáulcula el índice de la tabla hash para una clave dada.

            int sum = 0;
            for(int i = 0; i < key.length(); i++){
                sum += int(key[i]);
            }
            return sum % max;
        }

        

    public:
        HashTable(int size){//constructor que inicializa la tabla hash
            max = size;
            n = 0;
            table = new ListLinked<TableEntry<V>>[max];
        }
        
        ~HashTable(){
            delete[] table;
        }
        

        V search(std::string key) override{//busca un par clave→valor por su clave y devuelve el valor asociado.
            int index = h(key);
            TableEntry<V> te(key);
            int pos = table[index].search(te);
            if(pos == -1){
                throw runtime_error("Clave no encontrada");
            }
            return table[index].get(pos).value;

        }

        void insert(std::string key, V value) override{//inserta un par clave→valor en la tabla hash
            int index = h(key);
            TableEntry<V> te(key, value);
            int pos = table[index].search(te);
            if(pos != -1){
                throw runtime_error("Clave ya existente");
            }
            table[index].append(te);
            n++;
            
        }

        V remove(std::string key) override{//elimina un par clave→valor por su clave y devuelve el valor asociado.
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

        friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){//sobrecarga para imprimir toda la tabla hash
            for(int i = 0;i < th.max; i++){
                out << "Indice " << i << ": " << th.table[i] << "\n";
            }
            return out;
        }
        
        V operator[](std::string key){//sobrecarga del operador[] para buscar un valor por su clave
            return search(key);
        }

        /* HashTable<V> rehash_1(){
            ListLinked<TableEntry<V>>* table = new ListLinked<TableEntry<V>>[max * 2];
            for(int i = 0; i < max; i++){
                for(int j = 0; j < this->table[i].size();j++){
                    TableEntry<V> te = this->table[i].get(j);
                    int index = h(te.key);
                    table[index].append(te);
                }
            }

        } */

        HashTable<V> rehash(){
            HashTable<V> Table_2(max*2);
            for(int i = 0; i<max; i++){
                for(int j = 0; j < table[i].size(); j++){
                    TableEntry<V> te = table[i].get(j);
                    Table_2.insert(te.key, te.value);
                }
            }
            return Table_2;
        }

        /* HashTable<V> rehash_2(){
            HashTable<V> newTable(max * 2);
            for(int i = 0; i < max; i++){
                for(int j = 0; j < table[i].size(); j++){
                    TableEntry<V> te = table[i].get(j);
                    newTable.insert(te.key, te.value);
                }
            }
            return newTable;
        } */
};

#endif