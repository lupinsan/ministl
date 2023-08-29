#ifndef M_VECTOR_H
#define M_VECTOR_H

#include"../mini_iterator/mini_iter.h"
#include"../mini_memory/mini_memory.h"
#include"../algorithm/m_algo.h"

namespace mini
{
template <class T,  class Alloc = __malloc_alloc>
class vector{
public:
    typedef T           value_type;
    typedef value_type* pointer;
    typedef value_type* iterator;
    typedef value_type& reference;
    typedef size_t      size_type;
    typedef ptrdiff_t   difference_type;
protected:
    typedef simple_alloc<value_type,Alloc> data_allocator;
    iterator start;
    iterator finish;
    iterator end_of_storage;

public:
    iterator begin() const {return start;}
    iterator end() const {return finish;}
    size_type __tatol() const {return size_type(end_of_storage-start);}
    size_type size() const {return size_type(end()-begin());}//const 只可访问const函数
    bool empty() const {return begin()==end();}

    reference operator[] (size_type n) {return *(begin()+n); }
    reference front() {return *begin(); }
    reference back() {return *(end()-1); }


    iterator allocate_and_fill(size_type n, const T& value){
        iterator res = data_allocator::allocate(n);
        uninitialized_fill_n(res,n,value);
        return res;
    }


    void fill_initialize(size_type n,const T& value){
        start = allocate_and_fill(n,value);
        finish = start + n;
        end_of_storage = finish;
    }

    vector(size_type n,const T& value){
        fill_initialize(n,value);
    }

    vector(){
        fill_initialize(1,0);
        finish-=1;
    }


    void reserve(size_type n){
        if(size()!=0){
            //abort();
            destroy(start,finish);
            data_allocator::deallocate(start);
        }
        iterator res;
        try{
                res = data_allocator::allocate(n);
                start = res;
                finish =start;
                end_of_storage+=n;
                }
        catch(...){
                data_allocator::deallocate(res);
                abort();
        }
        
        return;

    }



    ~vector(){
        destroy(start,finish);
        data_allocator::deallocate(start);
    }

    vector(const vector& v){
        start = data_allocator::allocate(v.__tatol());
        finish = start + v.size();
        end_of_storage = start + v.__tatol();

        uninitialized_copy(v.begin(),v.end(),start);
    }

    vector& operator= (const vector& v){
        if(this->__tatol()>=v.__tatol()){
            uninitialized_copy(v.begin(),v.end(),start);
            finish = start + v.size();
        }
        else{
            destroy(start,finish);
            data_allocator::deallocate(start);
            
            start = data_allocator::allocate(v.__tatol());
            finish = start + v.size();
            end_of_storage = start + v.__tatol();
            uninitialized_copy(v.begin(),v.end(),start);
        }
        return *this;
    }

    vector(vector&& v) noexcept{
        start = v.begin();
        finish = v.end();
        end_of_storage = start+v.__tatol();
        v.start = NULL;
        v.finish = NULL;
        v.end_of_storage = NULL;
    }

    vector& operator=(vector&& v) noexcept{
        destroy(start,finish);
        data_allocator::deallocate(start);
        start = v.begin();
        finish = v.end();
        end_of_storage = start+v.__tatol();
        v.start = NULL;
        v.finish = NULL;
        v.end_of_storage = NULL;
        return *this;
    }
    





    void push_back(const T& x){
        if(finish!=end_of_storage){
            construct(&*finish,x);
            ++finish;
        }
        else{
            insert_aux(end(), x);
        }
    }


    void insert_aux(iterator position, const T& x){
        if(finish != end_of_storage) {
            construct(finish,*(finish-1));
            ++finish;
            T x_copy =x;
            copy_backward(position, finish -2, position +1);///////-----re
            *position = x_copy;
        }
        else{
            const size_type old_size = size();
            const size_type len = old_size !=0 ? 2*old_size : 1;
            iterator new_start = data_allocator::allocate(len);
            iterator new_finish = new_start;

            try{
                new_finish = uninitialized_copy(start, position,new_start);
                construct(new_finish,x);
                new_finish++;
                new_finish = uninitialized_copy(position,finish,new_finish);
            }

            catch(...){
                destroy(new_start,new_finish);
                data_allocator::deallocate(new_start,len);
            }

            destroy(begin(),end());
            data_allocator::deallocate(begin());


            //adjust
            start = new_start;
            finish = new_finish;
            end_of_storage = new_start +len;
        }
    }


    void pop_back(){
        --finish;
        destroy(&*finish);
    }

    iterator erase(iterator first,iterator last){
        
        iterator i =copy(last,finish,first);
        destroy(i,finish);

        finish = finish -(last - first);
        return first;
    }

    iterator erase(iterator position){
        if(position+1!=end())
            copy(position+1,finish,position);
        --finish;
        destroy(finish);
        return position;
    }


void insert(iterator position, size_type n, const T& x){
    if(n!=0){
        if(size_type(end_of_storage - finish)>= n){
            T x_copy =x;
            const size_type elems_after = finish -position;
            iterator old_finish = finish;
            if(elems_after >n){
                uninitialized_copy(finish-n,finish,finish);
                finish+=n;
                copy_backward(position,old_finish-n,old_finish);
                uninitialized_fill(position,position+n,x_copy);
            }
            else{
                uninitialized_fill_n(finish,n-elems_after,x_copy);
                finish+= n-elems_after;
                uninitialized_copy(position, old_finish,finish);
                finish += elems_after;
                uninitialized_fill(position,old_finish,x_copy);
            }
        }
        else{
            const size_type old_size = size();
            const size_type len = old_size + (old_size>n?old_size:n);
            iterator new_start = data_allocator::allocate(len);
            iterator new_finish = new_start;
            try{
                new_finish = uninitialized_copy(start,position,new_start);
                new_finish = uninitialized_fill_n(new_finish,n,x);
                new_finish = uninitialized_copy(position,finish,new_finish);
            }

            //???????
            catch(...){
                destroy(new_start,new_finish);
                data_allocator::deallocate(new_start,len);
            }

            destroy(begin(),end());
            data_allocator::deallocate(&*start);

            start = new_start;
            finish = new_finish;
            end_of_storage = new_start + len;
        }


    }




}


void swap(vector &x){
    iterator tmp;
    tmp =start;
    start = x.start;
    x.start = tmp;
    tmp =finish;
    finish = x.finish;
    x.finish = tmp;
    tmp =end_of_storage;
    end_of_storage = x.end_of_storage;
    x.end_of_storage = tmp;
    return;
}



};

}



#endif