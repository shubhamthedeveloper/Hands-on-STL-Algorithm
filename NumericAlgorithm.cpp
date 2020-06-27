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

template < typename T > vector < T > PrepareVector (T init, unsigned size)
{
  vector < T > v (size);

  // for(auto i = v.begin(); i != v.end();i++){
  //     *i = init++;
  // }

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


//stable sort sorting collection of data 
void
STABLE_SORT ()
{
  typedef std::pair < int, int >iipair;
  vector < iipair > data
  {
    {
    25, 1455},
    {
    26, 1328},
    {
    28, 4500},
    {
    25, 1455},
    {
    28, 4853},
    {
    27, 3478},
    {
    26, 4561},
    {
    28, 1888},
    {
  30, 3999},};

  sort (begin (data), end (data),[](iipair p1, iipair p2)
	{
	return p1.second < p2.second;}
  );
  stable_sort (begin (data), end (data),[](iipair p1, iipair p2)
	       {
	       return p1.first < p2.first;}
  );

  for_each (data.begin (), data.end (),[](iipair p)
	    {
	    cout << p.first << " " << p.second << endl;}
  );
}


void
NUMERIC_ALGORITHM ()
{
  //auto v1 = PrepareVector(1,5);
  //auto v2 = PrepareVector(5,10);
  vector < int >v1 = { 2, 3 };
  vector < int >v2 = { 3, 4 };
  vector < int >ans;

  int n = count (begin (v1), end (v1), 6);
  // cout << n << endl; // 0

  //inner_product = 2x3 + 3x4
  cout << "inner_product : " << inner_product (begin (v1), end (v1),
					       begin (v2), 0) << endl;

  //accumulate
  auto vv = PrepareVector (1, 10);
  int sum = accumulate (begin (vv), end (vv), 0);
  cout << "accumulate : " << sum << endl;

  //accumulate version 2
  int init = 100;
  int diff = init - sum;

  //functor minus is given which is by default addition 
  int diff2 = accumulate (begin (vv), end (vv), init, std::minus < int >());
  //cout << diff << " " << diff2 << endl;       // both should be same 

  //reduce similar to accumulate ->
  //reduce can be execued in parallel but acc. executes in sequence 
  // we provide execution policy to the reduce par - parallel

  init = 0;
  sum = reduce (std::execution::par, begin (vv), end (vv), init);
  //cout << sum << endl;


  //same as inner_product but its a parallel execution
  /*
     cout << "transform_reduce : " << transform_reduce (std::execution::par,
     begin (v1), end (v1),
     begin (v2), 0) << endl;
   */

  //Adjacent difference -> creates a new collection 
  vector < int >uu (10);
  sort (begin (vv), end (vv));
  adjacent_difference (begin (vv), end (vv), begin (uu));
  PrintVector(uu);
  
  //partial_sum 
  partial_sum(begin(vv),end(vv),begin(uu));
  PrintVector(uu);
  
  //inclusive_scan no diff. with partial_sum 
  inclusive_scan(std::execution::par, begin(vv), end(vv), begin(uu));
  PrintVector(uu);
  
  //exclusive_scan 
  exclusive_scan(std::execution::par, begin(vv), end(vv), begin(uu),0);
  PrintVector(uu);
  
  //transform_inclusive_scan
  transform_inclusive_scan(std::execution::par, begin(vv), end(vv), 
    begin(uu),std::plus<int>,[](int x){
        return x*2;
    });
  PrintVector(uu);
  
  //transform_exclusive_scan
  transform_inclusive_scan(std::execution::par, begin(vv), end(vv), 
    begin(uu),0,std::plus<int>,[](int x){
        return x*2;
    });
  PrintVector(uu);
}

int
main ()
{
  NUMERIC_ALGORITHM ();
  //STABLE_SORT();
  return 0;
}
