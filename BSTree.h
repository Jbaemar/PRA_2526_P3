#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
        int nelem;
        BSNode<T>* root;

        BSNode<T>* search(BSNode<T>* n, T e) const{

            if(n==nullptr){
                throw runtime_error("Arbol vacio");
            }else if(n.elem < e){
                return search(n.right, e);
            }else if(n.elem > e){
                return search(n.left, e);
            }else{
                return n;
            }

        }

        BSNode<T>* insert(BSNode<T>* n, T e) const{

            if(n==nullptr){
                n = new BSNode(e);
            }else if(n.elem == e){
                throw runtime_error("Duplicated element");
            }else if(n.elem < e){
                return insert(n.right, e);
            }else{
                return insert(n.left, e);
            }

        }

        void print_inorder(std::ostream &out, BSNode<T>* n) const{
            if(n != nullptr){
                print_inorder(out, n->left);
                out << n->elem << " ";
                print_inorder(out, n->right);
            }

        }

    public:
        BSTree(){
            this->nelem = 0;
            this->root = nullptr;
        }

        int size() const {
            return this->nelem;
        }

        T search (T elem) const{
            return search(root, e).elem;

        }

        T operator[](T e) const{
            return search(e);
        }


        void insert(T e){
            root = insert(root,e);
            return;
        }


        friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst){
            bst.print_inorder(out, bst.root);
            return out;
        }
    
};

#endif