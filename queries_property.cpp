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

void QUERIES_PROPERY(){
    auto vv = PrepareVector(1,10);
    
    // 1. return true if every element is less than 10
    cout << "is every element in vv less than 10 ? " << all_of(begin(vv),end(vv),
    [](int x){return x<10;}) << endl;

    // output - 0 because 10 is not less than 10
    
    for_each(begin(vv),end(vv),[](int& x){x*=2;});
    PrintVector(vv);
    
    //2. return false if any of the element is odd  
    cout << "\nis any element is odd ? " << any_of(begin(vv),end(vv),
    [](int x){return x%2 ;});
    //output - 0 because all are even elements
    
    //3. check if none of the element is odd 
     cout << "\nall elements are even or none of the element is odd? " << none_of(begin(vv),end(vv),
    [](int x){return x%2 ;});
}

void QUERIES_PROPERY_2RANGES(){
    
    //1. equal , is_permutate;
    auto v1 = PrepareVector(1,10);
    auto v2 = PrepareVector(1,10);
    shuffle (v1.begin (), v1.end (), std::default_random_engine ());
    
    cout << "are both vectors equal? " << equal(begin(v1),end(v1),begin(v2)) << endl;
    cout << "are both vectors permutation of each other? " << is_permutation(begin(v1),end(v1),begin(v2))<< endl;
    
    //output equal - 0 , is_permutation - 1
    
    //2. lexo compare 1 - if s1 comes first in dictionary, 0 if s2 comes first in dictionary
    string s1 = "hello";
    string s2 = "hello";
    cout << "lexi order " << lexicographical_compare(begin(s1),end(s1),begin(s2),end(s2)) << endl;
    
    //mismatch
    auto res = mismatch(begin(v1),end(v1),begin(v2));
    cout << (res.first == v1.end() && res.second == v2.end() ? "match" : "mismatch") << endl;
    
    
}

void QUERIES_SEARCH(){
    
    //1. find - non sorted collection 
    auto v = PrepareVector(10,10);
    PrintVector(v);
    auto itr = find(begin(v),end(v),15);
    cout << "index of the target - " << itr-begin(v) << endl;
    
    //2. adjacent find 
    v[3]=v[4]=v[5]=9;
    PrintVector(v);
    //this shows first adj. occurence of any two number withour any predicate
    auto it = adjacent_find(begin(v),end(v));
    
    //to give predicates 
    auto it1 = adjacent_find(begin(v),end(v),[](int x, int y){return x == y;});
    cout << "adjacent_find - " << it1-begin(v) << endl;
    
    //3. equal_range 
    
    auto eq_pair = equal_range(begin(v),end(v),9);
    cout << eq_pair.first - v.begin() << " " <<  eq_pair.second - v.begin()-1 << endl;
    
    
}

int main()
{
    //QUERIES_PROPERY();
    // QUERIES_PROPERY_2RANGES();
    QUERIES_SEARCH();
    return 0;
}
//https://restcountries.eu/rest/v2/all
