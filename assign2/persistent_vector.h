#ifndef PERSISTENT_VECTOR_H
#define PERSISTENT_VECTOR_H

#include <algorithm>
#include <bitset>
#include <cmath>
#include <memory>
#include <stdexcept>
#include <vector>
#include <iostream>

template <typename T>
class persistent_vector {
private:
    class node { 
    public: 
        virtual ~node() {} 
        virtual void print_details() = 0;
        virtual void traverse(int cur, int height, std::bitset<8> bits, T** val) = 0;
    };
    class internal_node : public node { 
    public:
        int bit;
        int height;
        void print_details() {
           if (this -> left)
               std::cout << "node " << this << " : " << &(this -> left) << " " << &(this -> right) << std::endl;
           else
               return;
           (this -> left) -> print_details();
           if (this -> right)
               (this -> right) -> print_details();
        }
        std::shared_ptr<node> left;
        std::shared_ptr<node> right;
        void traverse(int cur, int height, std::bitset<8> bits, T** val) {
           if (bits[height - cur] == 0)
               (this -> left) -> traverse(++cur, height, bits, val);
           else
               (this -> right) -> traverse(++cur, height, bits, val);
        }
    };
    class leaf_node : public node { 
    public:
        int bit;
        T vall;
        T valr;
        bool rexists;
        void print_details() {
           std::cout << "leaf " << this << " : " << vall;
           if (rexists)
               std::cout << " " << valr;
           std::cout << std::endl;
        }
        void traverse(int cur, int height, std::bitset<8> bits, T** val) {
           if (bits[height - cur] == 0)
               *val = &(this -> vall);
           else
               *val = &(this -> valr);
        }
    };

public:

    //constructor
    persistent_vector(const std::vector<T>& v) {
        vec = v;
        if (v.size() > 1)
           std::reverse(vec.begin(), vec.end());
        m_size = v.size();
        if (m_size > 2)
           m_height = std::ceil(log2(std::ceil(m_size/2)));
        else
           m_height = 1;
        std::shared_ptr<internal_node> head(new internal_node);
        root = head;
        root -> bit = 0;
        root -> height = 0;
        addNodes(0, root);
        m_head = root;
    }

    //copy constructor
    persistent_vector(const persistent_vector& other) {
       this.m_size = other.m_size;
       this.m_height = other.m_height;
       this.m_head = other.m_head;
       this.root = other.root;
       
       for (int x = m_size-1; x >= 0; x--)
           vec.insert(other[x]);
       
       addNodes(0, root);
    }

    //copy assignment operator
    const persistent_vector& operator=(const persistent_vector& other) {
       this.m_size = other.m_size;
       this.m_height = other.m_height;
       this.m_head = other.m_head;
       this.root = other.root;
       
       for (int x = m_size-1; x >= 0; x--)
           vec.insert(other[x]);
       
       addNodes(0, root);
       
       return *this;
    }

    //lookup operator
    const T& operator[](size_t index) const {
       if (index >= m_size || index < 0)
          throw std::out_of_range ("Index bounds violated"); 
       T *val = NULL;
       std::bitset<8> bits(index);
       root -> traverse(0, (int)m_height, bits, &val);
       return *val;
    }
    

    void print_details() const {
       std::cout << "persistent_vector of " << m_size << " elements with height " << m_height << std::endl;
	    if(m_size) {
	        m_head->print_details();
	    }
    }

    private:
	std::shared_ptr<node> m_head;
   std::shared_ptr<internal_node> root;
	size_t m_size;
	size_t m_height;
   std::vector<T> vec;
   
   void addNodes(int cur, std::shared_ptr<internal_node> node) {
        if (vec.empty()) {
            return;
        }
        if (cur == m_height - 1) {
            if (!vec.empty()) {
                std::shared_ptr<leaf_node> t3(new leaf_node);
                t3 -> rexists = false;
                t3 -> bit = 0;
                t3 -> vall = vec.back();
                vec.pop_back();
                if (!vec.empty()) {
                   t3 -> valr = vec.back();
                   vec.pop_back();
                   t3 -> rexists = true;
                }
                //else
                   //t3 -> valr = NULL;
                node -> left = t3;
            }
            if (!vec.empty()) {
                std::shared_ptr<leaf_node> t4(new leaf_node);
                t4 -> rexists = false;
                t4 -> bit = 1;
                t4 -> vall = vec.back();
                vec.pop_back();
                if (!vec.empty()) {
                   t4 -> valr = vec.back();
                   vec.pop_back();
                   t4 -> rexists = true;
                }
                //else
                   //t4 -> valr = NULL;
                node -> right = t4;
            }
            return;
        }
        
        std::shared_ptr<internal_node> t1(new internal_node);
        t1 -> bit = 0;
        t1 -> height = node -> height + 1;
        node -> left = t1;
        std::shared_ptr<internal_node> t2(new internal_node);
        t2 -> bit = 1;
        t2 -> height = node -> height + 1;
        node -> right = t2;
        addNodes(t1 -> height, t1);
        addNodes(t2 -> height, t2);
   }
};

#endif // defined PERSISTENT_VECTOR_H
