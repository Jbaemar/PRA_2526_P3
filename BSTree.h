#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"
using namespace std;

template <typename T> 
class BSTree {
    private:
        int nelem;
        BSNode<T>* root;

        BSNode<T>* search(BSNode<T>* n, T e) const{//busca un elemento en el árbol y devuelve el nodo que lo contiene

            if(n==nullptr){
                throw runtime_error("Elemento no encontrado");
            }else if(n->elem < e){
                return search(n->right, e);
            }else if(n->elem > e){
                return search(n->left, e);
            }else{
                return n;
            }

        }

        BSNode<T>* insert(BSNode<T>* n, T e){//inserta un elemento en el árbol

            if(n==nullptr){
                nelem++;
                return new BSNode<T>(e);
            }else if(n->elem == e){
                throw runtime_error("Duplicated element");
            }else if(n->elem < e){
                n->right = insert(n->right, e);
            }else{
                n->left = insert(n->left, e);
            }
            return n;

        }

        void print_inorder(std::ostream &out, BSNode<T>* n) const{//imprime el árbol en orden desde la rama de la izquierda hacia la derecha
            if(n != nullptr){
                print_inorder(out, n->left);
                out << n->elem << " ";
                print_inorder(out, n->right);
            }

        }

        T max(BSNode<T>* n) const{//devuelve el máximo elemento del árbol
            if(n == nullptr){
                throw runtime_error("Elemento no encontrado");
            }else if(n->right != nullptr){
                return max(n->right);
            }else{
                return n->elem;
            }

        }

        BSNode<T>* remove_max(BSNode<T>* n){//elimina el máximo elemento del árbol
            if(n == nullptr){
                return nullptr;
            }
            if(n->right == nullptr){
                return n->left;
            }
            n->right = remove_max(n->right);
            return n;
        }

        BSNode<T>* remove(BSNode<T>* root,T e){//elimina un elemento del árbol y 
            if(root == nullptr){
                throw runtime_error("Elemento no encontrado");
            }else if(root->elem < e){
                root->right = remove(root->right, e);
            }else if(root->elem > e){
                root->left = remove(root->left, e);
            }else{
                if(root->left != nullptr && root->right != nullptr){
                    root->elem = max(root->left);
                    root->left = remove_max(root->left);
                    nelem--;
                }else{
                    if(root->left != nullptr){
                        root = root->left;
                    }else{
                        root = root->right;
                    }
                    nelem--;
                }
            return root;
            }
        }

        void delete_cascade(BSNode<T>* n){//elimina todos los nodos del árbol de forma recursiva
            if(n != nullptr){
                delete_cascade(n->left);
                delete_cascade(n->right);
                delete n;
            }
        }

    public:
        BSTree(){
            this->nelem = 0;
            this->root = nullptr;
        }
        
        ~BSTree(){
            delete_cascade(root);
        }

        int size() const {
            return this->nelem;
        }

        T search (T e) const{
            return search(root, e)->elem;

        }

        T operator[](T e) const{
            return search(e);
        }


        void insert(T e){
            root = insert(root,e);
            return;
        }


        friend ostream& operator<<(ostream &out, const BSTree<T> &bst){//sobrecarga para imprimir el árbol  
            bst.print_inorder(out, bst.root);
            return out;
        }

        void remove(T e){
            root = remove(root,e);
            return;
        }
    
};

#endif