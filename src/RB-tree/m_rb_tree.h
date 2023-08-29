#ifndef M_RB_TREE_H
#define M_RB_TREE_H
#include"../mini_iterator/mini_iter.h"
#include"../mini_memory/mini_memory.h"
#include"../algorithm/m_algo.h"
#include"../pair/m_pair.h"
#include <iostream>
namespace mini
{



typedef bool __rb_tree_color_type;
const __rb_tree_color_type __rb_tree_red = false;
const __rb_tree_color_type __rb_tree_black = true;


struct __rb_tree_node_base{
    typedef __rb_tree_color_type color_type;
    typedef __rb_tree_node_base* base_ptr;

    color_type color;
    base_ptr parent;
    base_ptr left;
    base_ptr right;



static base_ptr minimun(base_ptr x){
    while(x->left !=0) x=x->left;
    return x; 
}

static base_ptr maximum(base_ptr x){
    while (x->right!= 0)x = x->right;
    return x;
}
};

template <class Value>
struct __rb_tree_node : public __rb_tree_node_base
{
    typedef __rb_tree_node<Value>* link_type;
    Value value_field;
};


struct __rb_tree_base_iterator{
    typedef __rb_tree_node_base::base_ptr base_ptr;
    typedef bidirectional_iterator_tag iterator_category;
    typedef ptrdiff_t difference_type;
    base_ptr node;

    void increment()
    {
        if(node->right !=0){
            node = node->right;
            while(node->left !=0)
                node=node->left;
        }
        else{
            base_ptr y = node->parent;
            while(node == y->right) {
                node = y;
                y = y->parent;
            }
            if(node->right !=y)
                node = y;
        }
    }

    void decrement()
    {
        if(node->color == __rb_tree_red && node->parent->parent == node)
            node = node->right;//节点为header时
        else if (node->left !=0){
            base_ptr y = node->left;
            while(y->right != 0)
                y=y->right;
            node=y;
        }
        else{
            base_ptr y = node->parent;
            while(node == y->left) {
                node = y;
                y = y->parent;
            }
            node = y;
        }
    }
};

template <class Value, class Ref, class Ptr>
struct __rb_tree_iterator : public __rb_tree_base_iterator
{
    typedef Value value_type;
    typedef Ref reference;
    typedef Ptr pointer;
    typedef __rb_tree_iterator<Value, Value&, Value*>   iterator;
    typedef __rb_tree_iterator<Value, const Value& ,const Value*> const_iterator;
    typedef __rb_tree_iterator<Value,Ref,Ptr>   self;
    typedef __rb_tree_node<Value>* link_type;

    __rb_tree_iterator() {}
    __rb_tree_iterator(link_type x) { node = x; }
    __rb_tree_iterator(const iterator& it) {node = it.node; }

    reference operator*() const {return link_type(node)->value_field; }
    bool operator!=(const self& x){return node!= x.node; }
    bool operator==(const self& x){return node== x.node; }


    pointer operator->() const {return &(*this); }

    self& operator++() { increment(); return *this; }
    self operator++(int){
        self tmp = *this;
        increment();
        return tmp;
    }

    self& operator--() {decrement(); return *this;}
    self operator--(int) {
        self tmp = *this;
        decrement();
        return tmp;
    }
};







template <class Key, class Value, class KeyOfValue , class Compare,class Alloc = __malloc_alloc>
class rb_tree{
protected:
    typedef void* void_pointer;
    typedef __rb_tree_node_base* base_ptr;
    typedef __rb_tree_node<Value> rb_tree_node;
    typedef simple_alloc<rb_tree_node,Alloc> rb_tree_node_allocator;
    typedef __rb_tree_color_type color_type;

public:
    typedef Key key_type;
    typedef Value value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef __rb_tree_node<Value>* link_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

protected:
    link_type get_node() {return rb_tree_node_allocator::allocate(); }
    void put_node(link_type p) {rb_tree_node_allocator::deallocate(p); }

    link_type create_node(const value_type& x) {
        link_type tmp = get_node();
        try{
            construct(&tmp->value_field ,x);
        }
        catch(...)
        {
            put_node(tmp);
            abort();
        }
        return tmp;
    }

    link_type clone_node(link_type x) {
        link_type tmp = create_node(x->value_field);
        tmp->color = x->color;
        tmp->left = 0;
        tmp->right = 0;
        return tmp;
    }

    void destroy_node(link_type p) {
        destroy(&p->value_field);
        put_node(p);
    }
public:
//protected:
    size_type node_count;
    link_type header;
    Compare key_compare;

    link_type& root() const { return (link_type&) header->parent; }
    link_type& leftmost() const { return (link_type&) header->left; }
    link_type& rightmost() const {return (link_type&) header->right; }

    static link_type& left(link_type x){
        return (link_type&)(x->left);
    }
    static link_type& right(link_type x){
        return (link_type&)(x->right);
    }
    static link_type& parent(link_type x){
        return (link_type&)(x->parent);
    }
    static reference value(link_type x){
        return (x->value_field);
    }
    static const Key& key(link_type x){
        return KeyOfValue()(value(x));
    }
    static color_type& color(link_type x){
        return (color_type&)(x->color);
    }


    static link_type& left(base_ptr x){
        return (link_type&)(x->left);
    }
    static link_type& right(base_ptr x){
        return (link_type&)(x->right);
    }
    static link_type& parent(base_ptr x){
        return (link_type&)(x->parent);
    }
    static reference value(base_ptr x){
        return ((link_type)x)->value_field;
    }
    static const Key& key(base_ptr x){
        return KeyOfValue()(value((link_type)x));
    }
    static color_type& color(base_ptr x){
        return (color_type&)((link_type(x))->color);
    }


    static link_type minimum(link_type x) {
        return (link_type) __rb_tree_node_base::minimun(x);
    }

    static link_type maximun(link_type x) {
        return (link_type) __rb_tree_node_base::maximum(x);
    }


public:
    typedef __rb_tree_iterator<value_type,reference,pointer> iterator;
    typedef const iterator  const_iterator;

private:
    void __copy(link_type x, const link_type& p){
        x->color = p->color;
        x->left = p->left;
        x->right = p->right;
        //x->parent = p->parent;
        x->value_field = p->value_field;
        return;
    }
    




    
    void init() {
        header = get_node();
        color(header) = __rb_tree_red;
        root() = 0;
        leftmost() = header;
        rightmost() = header;
    }


    void postorderdelete(link_type x){
        if(x==0){
            return;
        }
        postorderdelete(link_type(x->left));
        postorderdelete(link_type(x->right));

        destroy_node(x);
        node_count = 0;
        return;
    }




public:




    void clear(){
        if(node_count==0){
            return;
        }

        postorderdelete(link_type(header->parent));

        header->parent = header;
        header->left =header;
        header->right = header;
        node_count = 0;
        return;
    }



    rb_tree(const Compare& comp = Compare())
        : node_count(0),key_compare(comp){init();}

    ~rb_tree() {
        clear();
        put_node(header);
    }

    rb_tree<Key,Value,KeyOfValue,Compare,Alloc>& operator= (const rb_tree<Key,Value,KeyOfValue,Compare,Alloc>& x){}

public:
    Compare key_comp() const {return key_compare;}
    iterator begin() {return leftmost(); }
    iterator end() {return header; }
    bool empty() const {return node_count==0;}
    size_type size() const {return node_count;}
    size_type max_size() const {return size_type(-1);}

public:

    


    inline void __rb_tree_rotate_left(base_ptr x,base_ptr& root){
        base_ptr y =x->right;
        x->right = y->left;
        if(y->left!=0)
            y->left->parent = x;
        y->parent = x->parent;
        if (x==root)
            root = y;
        else if(x==x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    inline void __rb_tree_rotate_right(base_ptr x,base_ptr& root){
        base_ptr y =x->left;
        x->left = y->right;
        if(y->right!=0){
            y->right->parent = x;
        }
        y->parent = x->parent;

        if(x==root)
            root = y;
        else if(x==x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
        y->right = x;
        x->parent = y;
    }





    inline void __rb_tree_rebalance(__rb_tree_node_base* x,__rb_tree_node_base*& root){
        x->color = __rb_tree_red;
        while(x!=root && x->parent->color == __rb_tree_red) {
            if(x->parent == x->parent->parent->left) {
                __rb_tree_node_base* y = x->parent->parent->right;
                if(y&&y->color == __rb_tree_red) {
                    x->parent->color = __rb_tree_black;
                    y->color = __rb_tree_black;
                    x->parent->parent->color = __rb_tree_red;
                    x =x->parent->parent;
                }
                else{
                    if(x==x->parent->right){
                        x=x->parent;
                        __rb_tree_rotate_left(x,root);
                    }
                    x->parent->color = __rb_tree_black;
                    x->parent->parent->color = __rb_tree_red;
                    __rb_tree_rotate_right(x->parent->parent, root);
                }
            }
            else{
                __rb_tree_node_base* y = x->parent->parent->left;
                if(y&&y->color == __rb_tree_red) {
                    x->parent->color = __rb_tree_black;
                    y->color = __rb_tree_black;
                    x->parent->parent->color = __rb_tree_red;
                    x=x->parent->parent;
                }
                else{
                    if(x==x->parent->left){
                        x=x->parent;
                        __rb_tree_rotate_right(x,root);
                    }
                    x->parent->color = __rb_tree_black;
                    x->parent->parent->color = __rb_tree_red;
                    __rb_tree_rotate_left(x->parent->parent, root);
                }
            }
        }
        root->color = __rb_tree_black;
    }
    
    void __erase_case1(link_type x){
            
            if(x==x->parent->left)
                x->parent->left=0;
            else
                x->parent->right=0;
            
            destroy_node(x);
            return;
    } 

    void __erase_case2(link_type x){
        if(x->left!=0&&x->right==0&&x->color==__rb_tree_black){
            link_type tmp = link_type(x->left);
            __copy(x,tmp);
            if (leftmost() == tmp){
                leftmost() = x;
            }
            if (rightmost() == tmp){
                header->right = x;
            }
            x->color = __rb_tree_black;
            destroy_node(tmp);
        }
        else if(x->left==0&&x->right!=0&&x->color==__rb_tree_black){
            link_type tmp = link_type(x->right);
            __copy(x,tmp);

            if (leftmost() == tmp){
                leftmost() = x;
            }
            if (rightmost() == tmp){
                header->right = x;
            }
            x->color = __rb_tree_black;
            destroy_node(tmp);
        }
    }




    void delete_black(link_type x,bool del){
        if(x==root()){
                destroy_node(x);
                leftmost() = header;
                rightmost() = header;
                header->parent = header;
                return;
            }
            link_type bro;
            if(x==link_type(x->parent->left)){
                bro=link_type(x->parent->right);
                if(bro->color==__rb_tree_black && bro->right!=0 && bro->right->color==__rb_tree_red){
                    bro->color = x->parent->color;
                    x->parent->color = __rb_tree_black;
                    bro->right->color = __rb_tree_black;
                    base_ptr tmp1 = x->parent;
                    __rb_tree_rotate_left(x->parent,header->parent);
                    if(del==true)
                    {
                        x->parent->left = 0;
                        destroy_node(x);
                    }
                    return;
                }
                else if(bro->color == __rb_tree_black&& bro->left!=0 &&bro->left->color==__rb_tree_red){
                    bro->color = __rb_tree_red;
                    bro->left->color = __rb_tree_black;
                    __rb_tree_rotate_right(bro,header->parent);
                    return delete_black(x,true);
                }
                else if(bro->color ==__rb_tree_black&&bro->left==0&&bro->right ==0){
                    if(x->parent->color==__rb_tree_red){
                        bro->color = __rb_tree_red;
                        x->parent->color = __rb_tree_black;
                        if(del==true)
                        {
                        x->parent->left = 0;
                        destroy_node(x);
                        }
                        return;
                    }
                    else{
                        bro->color = __rb_tree_red;
                        x->parent->color = __rb_tree_black;
                        link_type farther = link_type(x->parent);
                        if(del==true)
                        {
                        x->parent->left = 0;
                        destroy_node(x);
                        }
                        return delete_black(farther,false);
                    }
                }
                else if(bro->color==__rb_tree_red){
                    x->parent->color = __rb_tree_red;
                    bro->color = __rb_tree_black;
                    __rb_tree_rotate_left(x->parent,header->parent);
                    return delete_black(x,true);
                }
            }
            else{
                bro=link_type(x->parent->left);
                if(bro->color==__rb_tree_black && bro->left!=0 && bro->left->color==__rb_tree_red){
                    bro->color = x->parent->color;
                    x->parent->color = __rb_tree_black;
                    bro->left->color = __rb_tree_black;
                    __rb_tree_rotate_right(x->parent,header->parent);
                    if(del==true)
                    {
                        x->parent->right = 0;
                        destroy_node(x);
                    }
                    return;
                }
                else if(bro->color == __rb_tree_black&& bro->right!=0 &&bro->right->color==__rb_tree_red){
                    bro->color = __rb_tree_red;
                    bro->right->color = __rb_tree_black;
                    __rb_tree_rotate_left(bro,header->parent);
                    return delete_black(x,true);
                }
                else if(bro->color ==__rb_tree_black&&bro->left==0&&bro->right ==0){
                    if(x->parent->color==__rb_tree_red){
                        bro->color = __rb_tree_red;
                        x->parent->color = __rb_tree_black;
                        if(del==true)
                        {
                        x->parent->right = 0;
                        destroy_node(x);
                        }
                        return;
                    }
                    else{
                        bro->color = __rb_tree_red;
                        x->parent->color = __rb_tree_black;
                        link_type farther = link_type(x->parent);
                        if(del==true)
                        {
                        x->parent->right = 0;
                        destroy_node(x);
                        }
                        return delete_black(farther,false);
                    }
                }
                else if(bro->color==__rb_tree_red){
                    x->parent->color = __rb_tree_red;
                    bro->color = __rb_tree_black;
                    __rb_tree_rotate_right(x->parent,header->parent);
                    return delete_black(x,true);
                }
            }
    }


    void __erase(link_type x){
        

        if(x->left==0&&x->right==0&&x->color==__rb_tree_red){
            __erase_case1(x);
            return;
        }
        else if(x->left==0&&x->right==0&&x->color ==__rb_tree_black){
            return delete_black(x,true);
        }
        else if(x->left==0&&x->right!=0&&x->color==__rb_tree_black){
            return __erase_case2(x);   
        }
        else if(x->left!=0&&x->right==0&&x->color==__rb_tree_black){
            return __erase_case2(x);
        }
        else if(x->left!=0&&x->right!=0){
            link_type next = link_type((iterator(x).operator++()).node);
            if(header->right==next){
                header->right = x;
            }
            x->value_field = next->value_field;
            return __erase(next);
        }
        else{
            abort();
        }
        
    }


    void erase(iterator x){
        iterator tmp = x;
        if(rightmost()==x.node){
            header->right=(--tmp).node;
        }
        if(leftmost()==x.node){
            header->left=(++tmp).node;
        }

        __erase(link_type(x.node));
        node_count-=1;
        return;
    }


    iterator __insert(base_ptr x_, base_ptr y_, const Value& v){
        link_type x=(link_type) x_;
        link_type y = (link_type) y_;
        link_type z;

        if(y==header || x!=0 ||key_compare(KeyOfValue()(v), key(y))) {
            z=create_node(v);
            left(y)=z;
            if(y==header) {
                root() =z;
                rightmost() = z;
            }
            else if(y==leftmost())
                leftmost() =z;
        }
        else{
            z = create_node(v);
            right(y) =z;
            if(y == rightmost())
                rightmost() =z;
        }
        parent(z) = y;
        left(z) = 0;
        right(z) = 0;

        __rb_tree_rebalance(z,header->parent);
        ++node_count;
        return iterator(z);
    }



    pair<iterator,bool> insert_equal(const value_type& v){
        link_type y=header;
        link_type x= root();
        while(x!=0){
            y = x;
            x = key_compare(KeyOfValue()(v),key(x))?left():right();
        }
        return __insert(x,y,v);
    }
    pair<iterator,bool> insert_unique(const value_type& v){
        link_type y=header;
        link_type x=root();
        bool comp = true;
        while(x!=0){
            y=x;
            comp = key_compare(KeyOfValue()(v), key(x));
            x=comp? left(x):right(x);
        }

        iterator j = iterator(y);
        if(comp)
            if(j==begin())
                return pair<iterator,bool>(__insert(x,y,v), true);
            else    
                --j;
        
        if(key_compare(key(j.node),KeyOfValue()(v)))//------------------------------
            return pair<iterator,bool>(__insert(x,y,v),true);

        return pair<iterator,bool>(j,false);
    }

    
    iterator find(const Key& k) {
        link_type y = header;
        link_type x = root();

        while(x!=0)
        {
            if(!key_compare(key(x),k)){
                y=x;
                x=left(x);
            }
            else{
                x = right(x);
            }
        }
        iterator j = iterator(y);
        return(j==end()|| key_compare(k,key(j.node))) ? end() :j;
    }

    










};


}
#endif