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

        BSNode<T>* search(BSNode<T>* n, T e) const{

            if(n==nullptr){
                throw runtime_error("Arbol vacio");
            }else if(n->elem < e){
                return search(n->right, e);
            }else if(n->elem > e){
                return search(n->left, e);
            }else{
                return n;
            }

        }

        BSNode<T>* insert(BSNode<T>* n, T e) const{

            if(n==nullptr){
                n = new BSNode<T>(e);
            }else if(n->elem == e){
                throw runtime_error("Duplicated element");
            }else if(n->elem < e){
                return insert(n->right, e);
            }else{
                return insert(n->left, e);
            }

        }

        void print_inorder(std::ostream &out, BSNode<T>* n) const{
            if(n != nullptr){
                print_inorder(out, n->left);
                out << n->elem << " ";
                print_inorder(out, n->right);
            }

        }

        T max(BSNode<T>* n) const{
            if(n == nullptr){
                throw runtime_error("Elemento no encontrado");
            }else if(n->right != nullptr){
                return max(n->right);
            }else{
                return n->elem;
            }

        }

        T remove_max(BSNode<T>* n) const{
            if(n->right != nullptr){
                return n->left;
            }else{
                n->right = remove_max(n->right);
                return n;
            }
        }

        BSNode<T>* remove(BSNode<T>* root,T e) const{
            if(root == nullptr){
                throw runtime_error("Elemento no encontrado");
            }else if(root->elem < e){
                root->right = remove(root->right, e);
            }else if(root->elem > e){
                root->left = remove(root->left, e);
            }else{
                if(root->left != nullptr && root->right != nullptr){
                    root->elem = max(root->left);
                    root.left = remove_max(root.left);
                }else{
                    root = root.left != nullptr ? root.left : root.right;
                }
            }
            return root;
        }

        void delete_cascade(BSNode<T>* n){
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
            return search(root, e).elem;

        }

        T operator[](T e) const{
            return search(e);
        }


        void insert(T e){
            root = insert(root,e);
            return;
        }


        friend ostream& operator<<(ostream &out, const BSTree<T> &bst){
            bst.print_inorder(out, bst.root);
            return out;
        }

        void remove(T e){
            root = remove(root,e);
            return;
        }
    
};

#endif