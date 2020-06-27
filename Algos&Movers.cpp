/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <set>
//#include <execution>

using namespace std;

template < typename T > vector < T > 
PrepareVector (T init, unsigned size){
  vector < T > v (size);
  
  //iota does the same thing as the above for loop is doing 
  iota (v.begin (), v.end (), init);

  //shuffle the collection using random engine
  shuffle (v.begin (), v.end (), std::default_random_engine ());
  return v;
}

template <typename T>
void PrintVector(vector<T> v){
    //using for_each & lambdas rather than simple for loop
    for_each(v.begin(),v.end(),[](int x){cout << x << " ";});
    cout << endl;
}


void SET_ALGOS(){
    auto v1 = PrepareVector(0,10);
    for_each(begin(v1),end(v1),[](int& x){x = x%2;});
    
    auto v2 = PrepareVector(0,10);
    for_each(begin(v2),end(v2),[](int& x){x = x%2;});
    shuffle (v2.begin (), v2.end (), std::default_random_engine());
    // PrintVector(v1);
    // PrintVector(v2);
    
    typedef pair<int,int> iip;
    set<iip> setA,setB;
    
    
    int i=0;
    for_each(begin(v1),end(v1),[&](int x){
        if(x == 1)
        setA.insert({x,i});
        i++;
    });
    
     i=0;
    for_each(begin(v2),end(v2),[&](int x){
        if(x == 1)
        setB.insert({x,i});
        i++;
    });
    
    cout << "SET A :"<< endl;
    for_each(setA.begin(),setA.end(),[](iip p){cout << p.second << " ";});
    cout << "\nSET B :" << endl;
    for_each(setB.begin(),setB.end(),[](iip p){cout << p.second << " ";});
    
    //1. set_intersection 
    vector<iip> result;
    set_intersection(setA.begin(),setA.end(),setB.begin(),setB.end(),back_inserter(result));
    
    cout << "\nintersection of SETA & SETB is :" <<endl;
    for_each(result.begin(),result.end(),[](iip p){cout << p.second << " ";});
    result.clear();
    
    //2. set_difference 
    set_difference(setA.begin(),setA.end(),setB.begin(),setB.end(),back_inserter(result));
    cout << "\ndetected in only SETA and not in SETB :" <<endl;
    for_each(result.begin(),result.end(),[](iip p){cout << p.second << " ";});
    result.clear();
    
    //3. union 
    set_union(setA.begin(),setA.end(),setB.begin(),setB.end(),back_inserter(result));
    cout << "\ndetected in both SETA or SETB :" <<endl;
    for_each(result.begin(),result.end(),[](iip p){cout << p.second << " ";});
    result.clear();
    
    //4. symmetric set difference  
    set_symmetric_difference(setA.begin(),setA.end(),setB.begin(),setB.end(),back_inserter(result));
    cout << "\ndetected in only SETA + only SETB :" <<endl;
    for_each(result.begin(),result.end(),[](iip p){cout << p.second << " ";});
    result.clear();
    
    //5. includes - every element of v2 are present in v1 
    auto v3 = PrepareVector(1,10);
    auto v4 = PrepareVector(1,5);
    
    //both vector should be sorted - precondition 
    sort(begin(v3),end(v3));
    sort(begin(v4),end(v4));
    
    cout << "\nis v4 present in v3 :" << includes(begin(v3),end(v3),begin(v4),end(v4)) << endl;
    
    //6. merged - merge both the vectors
    vector<int> merged;
    merge(begin(v3),end(v3),begin(v4),end(v4),back_inserter(merged));
    cout << "\nMerged V3 & V4 : ";
    PrintVector(merged);
}

void MOVERS(){
    
    //1.copy 
    auto v1 = PrepareVector(0,10);
    vector<int> v1_copy(v1);
    copy(begin(v1),end(v1),begin(v1_copy));
    cout << "original vector : ";
    PrintVector(v1);
    cout << "copied from original vector :";
    PrintVector(v1_copy);
    
    //2. move
    vector<int> move_vector(v1);
    move(begin(v1),end(v1),begin(move_vector));
    cout << "vector moved from v1 to moved_vector : \n";
    PrintVector(v1);
    PrintVector(move_vector);
    
    //3. swap_ranges 
    auto v2 = PrepareVector(10,10);
    swap_ranges(begin(v1),end(v1),begin(v2));
    cout << "swapped v1 and v2 : \n";
    PrintVector(v1);
    PrintVector(v2);
    
    //4.copy_backward
    sort(begin(v2),end(v2));
    PrintVector(v2);
    copy_backward(v2.begin()+1,v2.begin()+5,v2.begin()+8);
    cout << "copy_backward : \n";
    PrintVector(v2);
}

void VALUE_MODIFIERS(){
    auto v = PrepareVector(1,10);
    fill(begin(v),end(v),55);
    PrintVector(v);
    
    generate(begin(v),end(v)-2,[](){return std::rand() % 50;});
    PrintVector(v);
    
    replace(begin(v),end(v),35,99);
    PrintVector(v);
    
}

void STRUCTURE_CHANGERS(){
    
    //1. remove - remove the instances of the element push them to the back 
    // returns the itr to the first of the element that is removed 
    auto v = PrepareVector(1,10);
    v[3] = v[4] = v[5] = 90;
    auto itr = remove(begin(v),end(v),90);
    v.erase(itr,v.end());
    PrintVector(v);
    
    //2. unique - remove only the adjacent duplicates 
    auto v2 = PrepareVector(1,10);
    v[3] = v[4] = 90;
    auto itr2 = unique(begin(v),end(v));
    v.erase(itr2,v.end());
    PrintVector(v);
    
}

int main()
{
    //SET_ALGOS();
    //MOVERS();
    //VALUE_MODIFIERS();
    STRUCTURE_CHANGERS();
    
    return 0;
}
//https://restcountries.eu/rest/v2/all
