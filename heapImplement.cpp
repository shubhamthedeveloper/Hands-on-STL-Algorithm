#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>

using namespace std;

template<typename T>
vector<T> PrepareVector(T init, unsigned size){
    vector<T> v(size);
    
    // for(auto i = v.begin(); i != v.end();i++){
    //     *i = init++;
    // }
    
    //iota does the same thing as the above for loop is doing 
    iota(v.begin(),v.end(),init); 
    
    //shuffle the collection using random engine
    shuffle(v.begin(),v.end(),std::default_random_engine());
    return v;
}

template <typename T>
void PrintVector(vector<T> v){
    //using for_each & lambdas rather than simple for loop
    for_each(v.begin(),v.end(),[](int x){cout << x << " ";});
    cout << endl;
}

void HEAP(){
    auto v = PrepareVector(1,10);
    make_heap(begin(v),end(v));
    PrintVector(v); // 10 9 5 8 4 1 2 7 6 3 
   
    v.push_back(15);
    PrintVector(v); // 10 9 5 8 4 1 2 7 6 3 15
   
    push_heap(begin(v),end(v));
    PrintVector(v); // 15 10 5 8 9 1 2 7 6 3 4
   
    v.push_back(20);
    v.push_back(13);
    v.push_back(14);
    make_heap(begin(v),end(v));  
    PrintVector(v); // 20 10 15 8 9 13 14 7 6 3 4 1 5 2 
    
    //swap the first and the last element
    pop_heap(begin(v),end(v));
    v.pop_back();
    PrintVector(v); // 15 10 14 8 9 13 2 7 6 3 4 1 5 
    
    //sort in ascending order
    sort_heap(begin(v),end(v));
    PrintVector(v); // 1 2 3 4 5 6 7 8 9 10 13 14 15 20 
}


int main()
{
    HEAP();
    return 0;
}