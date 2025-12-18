#ifndef DICT_H
#define DICT_H
#include <string>

template <typename V> 

//La interfaz genérica Dict<V>determinará de qué manera se puede gestionar un 
//Diccionario de pares clave→valor, donde clave será de tipo string y valor de tipo V cualquiera.
class Dict {
    public:
        virtual void insert(std::string key, V value) = 0;
        virtual V search(std::string key) = 0;
        virtual V remove(std::string key) = 0;
        virtual int entries() = 0;


};
#endif