#ifndef M_DEQUE_H
#define M_DEQUE_H
#include"../mini_iterator/mini_iter.h"
#include"../mini_memory/mini_memory.h"
#include"../algorithm/m_algo.h"

#define MAX_MAPSIZE 8

namespace mini
{

template <class T,class Ref, class Ptr,size_t  BufSiz>
struct __deque_iterator{

    static inline size_t __deque_buf_size(size_t n, size_t sz){
        return n!=0 ? n:(sz <512 ?size_t(512/sz):size_t(1));
    }

    typedef __deque_iterator<T,T&,T*, BufSiz>   iterator;
    typedef __deque_iterator<T,const T&,const T*, BufSiz>   const_iterator;
    static size_t buffer_size() {return __deque_buf_size(BufSiz,sizeof(T));}//why static
    typedef random_access_iterator_tag iterator_category;
    typedef T   value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T** map_pointer;

    typedef __deque_iterator self;

    T* cur;
    T* first;
    T* last;
    map_pointer node;

    void clear(){
        cur = nullptr;
        first = nullptr;
        last = nullptr;
        node = nullptr;
    }

    void set_node(map_pointer new_node) {
        node = new_node;
        first = *new_node;
        last = first+ difference_type(buffer_size());
    }

    reference operator*() const { return *cur; }
    pointer operator->() const {return &(operator*());}

    difference_type operator-(const self& x)const {
        return difference_type(buffer_size())*(node-x.node-1) + 
            (cur-first) + (x.last - x.cur);
    }

    self& operator++() {
        ++cur;
        if(cur == last){
            set_node(node+1);
            cur = first;
        }
        return * this;
    }
    self operator++(int ){
        self tmp = *this;
        ++*this;
        return tmp;
    }

    self& operator--(){
        if(cur == first) {
            set_node(node-1);
            cur = last;
        }
        --cur;
        return *this;
    }

    self operator--(int){
        self tmp = *this;
        --*this;
        return tmp;
    }

    self& operator+=(difference_type n) {
        difference_type offset = n + (cur - first);
        difference_type node_offset;
        if(offset >= 0 && offset < difference_type(buffer_size()))
            cur += n;
        else{
            node_offset =
                offset > 0 ? offset / difference_type(buffer_size())
                    : -difference_type((-offset - 1)/buffer_size())-1;
            set_node(node+node_offset);
            cur = first + (offset -node_offset*difference_type(buffer_size()));
        }
        return *this;
    }

    self operator+(difference_type n) const {
        self tmp = *this;
        return tmp += n;
    }

    self& operator-=(difference_type n){
        return *this += -n;}

    self operator-(difference_type n)const {//------------------------------re
        self tmp = *this;
        return tmp -= n; 
    }


    reference operator[](difference_type n)const {return *(*this+n);}

    bool operator==(const self& x) const {return cur==x.cur;}
    bool operator!=(const self& x) const {return !(*this==x);}
    bool operator<(const self& x) const {
        return (node == x.node)?(cur <x.cur): (node<x.node);
    }
};








template <class T,class Alloc = __malloc_alloc, size_t BufSiz =0 >
class deque{
public:
    typedef T           value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef size_t      size_type;
    typedef ptrdiff_t   difference_type;
    typedef const reference const_reference;

    typedef __deque_iterator<T,T&,T*,BufSiz> iterator;
    typedef deque<T, Alloc, BufSiz>  self;


protected:
    typedef pointer*  map_pointer;

    map_pointer map;
    size_type map_size;

protected:
    iterator start;
    iterator finish;

public:
    iterator begin() {return start;}
    iterator end() {return finish;}
    size_type buffer_size(){return iterator::buffer_size();}

    reference operator[](size_type n){
        return start[difference_type(n)];
    }
    reference front() {return *start; }
    reference back(){
        return (*(finish-1));
    }

    size_type size() const { return finish - start; }
    size_type max_size() const {return size_type(-1) ;}//??????
    size_type initial_map_size(){return MAX_MAPSIZE;}
    size_type __map_size(){return map_size;}
    bool empty() const {return finish ==start;}

protected:
    typedef simple_alloc<value_type,Alloc> data_allocator;

    typedef simple_alloc<pointer,Alloc> map_allocator;

    void deallocate_node(T* p){
        destroy(p,p+(difference_type(buffer_size())));
        data_allocator::deallocate(p);
    }

    T* allocate_node(){
        T* tmp = data_allocator::allocate(buffer_size());
        return tmp;
    }

    void create_map_and_nodes(size_type num_elements){

        size_type num_nodes = num_elements /buffer_size() + 1;

        map_size = MAX_MAPSIZE>num_nodes+2 ? MAX_MAPSIZE: num_nodes +2;
        map = map_allocator::allocate(map_size);

        map_pointer nstart = map +(map_size - num_nodes) /2;
        map_pointer nfinish = nstart + num_nodes -1;

        map_pointer cur;

        try{
            for(cur=nstart;cur<= nfinish;++cur){
                *cur = allocate_node();
            }
        }
        catch(...){

        }

        start.set_node(nstart);
        finish.set_node(nfinish);
        start.cur = start.first;
        finish.cur = finish.first + num_elements % buffer_size();
    }


    void fill_initialize(size_type n, const value_type& value){
        create_map_and_nodes(n);
        map_pointer cur;
        try{
            for (cur = start.node;cur< finish.node;++cur){
                uninitialized_fill(*cur,*cur+buffer_size(),value);
            }
            uninitialized_fill(finish.first,finish.cur,value);
        }
        catch(...){

        }
    }


public:


template<class InputIterator, class OutputIterator>
    OutputIterator insert(InputIterator first, InputIterator last, OutputIterator result);

    deque():start(),finish(),map(0),map_size(0){
        create_map_and_nodes(1);
        finish.cur-=1;
    }

    deque(int n,const value_type& value)
        : start(),finish(),map(0),map_size(0){
            fill_initialize(n,value);
    }

    deque(const deque& x){
        create_map_and_nodes(1);
        finish.cur-=1;
        insert(x.begin(),x.end(),start);
    }

    self operator =(const deque& x){
        clear();
        create_map_and_nodes(1);
        finish.cur-=1;
        insert(x.begin(),x.end(),start);
        return *this;
    }

// protected:
//     typedef pointer*  map_pointer;

//     map_pointer map;
//     size_type map_size;

// protected:
//     iterator start;
//     iterator finish;


    inline void deliver(self& x) noexcept{
        map = x.map;
        map_size = x.map_size;
        start = x.start;
        finish = x.finish;
        x.map = nullptr;
        x.map_size = 0;
        x.start.clear();
        x.finish.clear();
    }




    deque(deque&& x) noexcept{
        deliver(x);
    }

    operator =(deque&& x) noexcept{
        clear();
        deliver(x);
    }


    void reallocate_map(size_type nodes_to_add,bool add_at_front){
        size_type old_num_nodes = finish.node - start.node+1;
        size_type new_num_nodes = old_num_nodes + nodes_to_add;

        map_pointer new_nstart;
        if(map_size > 2*new_num_nodes) { //前后不平衡
            new_nstart = map+(map_size - new_num_nodes) /2
                + (add_at_front ? nodes_to_add: 0);
            
            if(new_nstart <start.node)
                copy(start.node,finish.node+1,new_nstart);//前闭后开
            else//????
                copy(start.node,finish.node+1,new_nstart);
        }
        else{
            size_type new_map_size = map_size +(map_size>nodes_to_add?map_size:nodes_to_add)+2;
            
            map_pointer new_map = map_allocator::allocate(new_map_size);

            new_nstart = new_map+ (new_map_size - new_num_nodes)/2 + (add_at_front ? nodes_to_add:0);


            copy(start.node,finish.node+1,new_nstart);

            map_allocator::deallocate(map,map_size);//需要迭代？???-----copy过来无需

            map = new_map;
            map_size = new_map_size;
        }
        start.set_node(new_nstart);
        finish.set_node(new_nstart+old_num_nodes-1);
    }






    void reserve_map_at_back(size_type nodes_to_add =1){
        if(nodes_to_add+1>map_size-(finish.node - map) )//尾部一个缓冲区没有（不用）
            reallocate_map(nodes_to_add,false);
    }

    void reserve_map_at_front(size_type nodes_to_add =1){
        if(nodes_to_add>start.node- map)
            reallocate_map(nodes_to_add,true);
    }




    void push_back_aux(const value_type& t){
        value_type t_copy = t;
        reserve_map_at_back();
        *(finish.node+1) = allocate_node();//-----------------------------
        try{
            construct(finish.cur,t_copy);
            finish.set_node(finish.node+1);
            finish.cur = finish.first;
        }
        catch(...){
            finish.set_node(finish.node-1);
            finish.cur = finish.last -1;
            deallocate_node(*(finish.node+1));
            throw;
        }
    }

    void push_back(const value_type& t){
        if (finish.cur !=finish.last -1){
            construct(finish.cur , t);
            ++finish.cur;
        }
        else
            push_back_aux(t);
    }

public:


    void push_front_aux(const value_type& t){
        value_type t_copy =t;
        reserve_map_at_front();
        *(start.node -1 ) = allocate_node();
        try{
            start.set_node(start.node-1);
            start.cur = start.last -1;
            construct(start.cur,t_copy);
        }
        catch(...){
            start.set_node(start.node+1);
            start.cur = start.first;
            deallocate_node(*(start.node-1));
            throw;
        }
    }





    void push_front(const value_type& t) {
        if(start.cur != start.first) {
            construct(start.cur-1,t);
            --start.cur;
        }
        else{
            push_front_aux(t);
        }
    }



    void pop_back_aux(){
        deallocate_node(finish.first);
        finish.set_node(finish.node-1);
        finish.cur = finish.last-1;
        destroy(finish.cur);
    }




    void pop_back(){
        if(empty()){
            return;
        }
        if(finish.cur!= finish.first){
            --finish.cur;
            destroy(finish.cur);
        }
        else{
            pop_back_aux();
        }
    }


    void pop_front_aux(){
        destroy(start.cur);
        deallocate_node(start.first);
        start.set_node(start.node+1);
        start.cur = start.first;
    }


    void pop_front(){
        if(empty()){
            return;
        }
        if(start.cur!=start.last -1){
            destroy(start.cur);
            ++start.cur;
        }
        else{
            pop_front_aux();
        }
    }

    void clear(){
        for(map_pointer node = start.node +1 ;node< finish.node;++node){
            destroy(*node,*node+buffer_size());
            data_allocator::deallocate(*node,buffer_size());
        }

        if(start.node!=finish.node){
            destroy(start.cur,start.last);
            destroy(finish.first,finish.cur);
            data_allocator::deallocate(finish.first,buffer_size());//保留头缓冲区
        }
        else{
            destroy(start.cur,finish.cur);
        }
        finish = start;
    }

    iterator erase(iterator pos){
        iterator next = pos;
        ++next;
        
        difference_type index = pos - start;
        if(index <(size()>>1)){
            copy_backward(start,pos,start+1);//////////////////////
            pop_front();
        }
        else{
            copy(next,finish,pos);
            pop_back();
        }
        return start+index;
    }

    iterator erase(iterator first,iterator last){
        if(first == start&& last == finish){
            clear();
            return finish;
        }
        else{
            difference_type n =last-first;
            difference_type elems_before = first-start;
            if(n==0) return first; 
            if(elems_before<(size()/2)){
                copy(start,first,start+n);
                iterator new_start = start+n;
                destroy(start,new_start);
                for(map_pointer cur = start.node;cur<new_start.node;++cur){
                    data_allocator::deallocate(*cur,buffer_size());
                }
                start = new_start;
            }
            else{
                copy(last,finish,first);
                iterator new_finish = finish -n;
                destroy(new_finish,finish);
                for(map_pointer cur = new_finish.node+1;cur<=finish.node ;++cur){
                    data_allocator::deallocate(*cur,buffer_size());
                }
                finish=new_finish;
            }
            return start+elems_before;//?????

        }
    }


    iterator insert_aux(iterator pos,const value_type& x){//????????
        difference_type index = pos-start;
        value_type x_copy =x;
        if(1){
            push_front(front());
            iterator front1 = start;
            ++front1;
            iterator front2 = front1;
            ++front2;
            pos = start+index;
            iterator pos1= pos;
            ++pos1;
            copy(front2,pos1,front1);
        }
        *pos = x_copy;
        return pos;
    }





    iterator insert(iterator position,const value_type& x){
        if(position.cur == start.cur){
            push_front(x);
            return start;
        }
        else if(position.cur == finish .cur){
            push_back(x);
            iterator tmp = finish;
            --tmp;
            return tmp;
        }
        else{
            return insert_aux(position,x);
        }
    }

//template<class InputIterator, class OutputIterator>
    


};

template <class T,class Alloc, size_t BufSiz>
template<class InputIterator, class OutputIterator>
OutputIterator deque<T,Alloc,BufSiz>::insert(InputIterator first, InputIterator last, OutputIterator result){
        auto dist = last-first;
        for(int i=0;i<dist;++i){
            result = insert(result, *first);
            ++first;
            ++result;
        }
        return result;
    }




















}
#endif