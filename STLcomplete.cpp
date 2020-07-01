
#include<iostream>
#include<vector>
#include<numeric>
#include<algorithm>
#include<random>
#include<execution>
#include <set>

using namespace std;
#pragma region Utilities
template<typename T>
vector<T> PrepareVector(T init, unsigned size)
{
	vector<T> v(size);
	iota(v.begin(), v.end(), init);
	shuffle(v.begin(), v.end(), std::default_random_engine(static_cast<int>(time(0))));

	return v;
}

template<typename T>
void PrintVector(vector<T> v)
{
	for_each(v.begin(), v.end(), [](int x) {cout << x << ' '; });
	cout << endl;
}
#pragma endregion

void HEAP()
{
	auto v = PrepareVector(0, 10);
	make_heap(begin(v), end(v));
	v.push_back(15);
	push_heap(v.begin(), v.end());
	v.push_back(13);
	v.push_back(17);
	v.push_back(11);
	make_heap(v.begin(), v.end());
	pop_heap(v.begin(), v.end());
	cout << v.back() << endl;
	v.pop_back();
	sort_heap(v.begin(), v.end());
	PrintVector(v);
}

void SORTING()
{
	auto v = PrepareVector(0, 50);
	sort(v.begin(), v.end());
	shuffle(v.begin(), v.end(), std::default_random_engine());
	partial_sort(v.begin(), v.begin() + 25, v.end());
	shuffle(v.begin(), v.end(), std::default_random_engine());
	nth_element(v.begin(), v.begin()+5, v.end());
	PrintVector(v);
}

void PARTITION()
{
	auto v = PrepareVector(0, 50);
	auto itr = partition(v.begin(), v.end(), [](int x) {return !(x % 3); });
	auto pitr = partition_point(v.begin(), v.end(), [](int x) {return !(x % 3); });
	PrintVector(v);
	cout << *pitr << endl;
}

void OTHER_PERMUTATIONS()
{
	auto v = PrepareVector(0, 11);
	sort(v.begin(), v.end());
	PrintVector(v);
	int pick_count = 2;
	int pick_pos = 3;
	int drop_pos = 8 + 1;
	rotate(v.begin() + pick_pos, v.begin() + pick_pos + pick_count, v.begin() + drop_pos);
	PrintVector(v);

	drop_pos = 2 + 1;
	pick_pos = 7;
	rotate(v.begin() + drop_pos, v.begin() + pick_pos, v.begin() + pick_pos + pick_count);
	PrintVector(v);
}

void STABLE_SORT()
{
	typedef std::pair<int, int> iipair;
	vector<iipair> ageWSTable = {
	{25,1456},
	{26,1328},
	{28,4500},
	{30,2342},
	{25,2919},
	{28,4853},
	{27,3478},
	{26,4561},
	{28,5615},
	{30,4657},
	{25,2134},
	{26,2168},
	{28,1615},
	{27,6854},
	{26,5464},
	{30,2131},
	{30,5479},
	{38,3546},
	{37,7941},
	{25,5646}
};

	sort(ageWSTable.begin(), ageWSTable.end(),
		[](iipair p1, iipair p2) { return p1.second < p2.second; });
	stable_sort(ageWSTable.begin(), ageWSTable.end(),
		[](iipair p1, iipair p2) {return p1.first < p2.first; });
	for_each(ageWSTable.begin(), ageWSTable.end(), [](iipair p) {cout << p.first << ' ' << p.second << endl; });
}

void QUERIES_NUMERIC_ALGORITHMS()
{
	//inner_product
	vector<int> v = { 4, 5 };
	vector<int> w = { 2, 3 };
	//cout << inner_product(v.begin(), v.end(), w.begin(), 0) << endl;

	//accumulate
	int init = 0;
	auto vv = PrepareVector(0, 10);
	auto sum = accumulate(vv.begin(), vv.end(), init);
	//cout << sum << endl;

	init = 100;
	auto diff = init - sum;

	auto diff2 = accumulate(vv.begin(), vv.end(), init, std::minus<int>());
	//cout << diff << " == " << diff2 << endl;

	//reduce
	init = 0;
	sum = reduce(std::execution::par, vv.begin(), vv.end(), init);
	//cout << sum << endl;

	//transform_reduce
	//cout << transform_reduce(std::execution::par, v.begin(), v.end(), w.begin(), 0) << endl;

	//adjacent difference
	/*
	y0 = x0
	y1 = x1 - x0
	y2 = x2 - x1
	y3 = x3 - x2
	y4 = x4 - x3
	*/
	vv = PrepareVector(0, 10);
	//sort(vv.begin(), vv.end());
	PrintVector(vv);
	vector<int> uu(10);
	adjacent_difference(vv.begin(), vv.end(), uu.begin());
	//PrintVector(uu);

	partial_sum(vv.begin(), vv.end(), uu.begin());
	//PrintVector(uu);

	inclusive_scan(std::execution::par, vv.begin(), vv.end(), uu.begin());
	PrintVector(uu);

	exclusive_scan(std::execution::par, vv.begin(), vv.end(), uu.begin(), 0);
	PrintVector(uu);

	transform_inclusive_scan(std::execution::par, vv.begin(), vv.end(), uu.begin(),
		std::plus<int>(), [](int x) { return x * 2; });
	PrintVector(uu);
	transform_exclusive_scan(std::execution::par, vv.begin(), vv.end(), uu.begin(), 0,
		std::plus<int>(), [](int x) { return x * 2; });
	PrintVector(uu);
}

void QUERIES_PROPERTY()
{
	//all_of
	auto v = PrepareVector(0, 10);
	cout << "All elements < 10?" << all_of(v.begin(), v.end(), [](int x) {return x < 10; });
	for_each(v.begin(), v.end(), [](int& x) { x *= 2; });
	PrintVector(v);
	//any_of
	cout << "Any element is odd? " << any_of(v.begin(), v.end(), [](int x) {return x % 2; }) << endl;
	//v[4] = 5;
	cout << "Any element is odd? " << any_of(v.begin(), v.end(), [](int x) {return x % 2; }) << endl;
	// none_of
	cout << "All elements are even? " << none_of(v.begin(), v.end(), [](int x) { return x % 2; }) << endl;
}

void QUERIES_PROPERTIES_2RANGES()
{
	// equal, is_permutation
	auto v = PrepareVector(0, 10);
	auto u = PrepareVector(0, 10);
	shuffle(u.begin(), u.end(), default_random_engine());
	cout << "Is equal? " << equal(v.begin(), v.end(), u.begin()) << endl;
	cout << "Is permutation? " << is_permutation(v.begin(), v.end(), u.begin()) << endl;

	//lexicographical_compare
	string str1 = "Albastra Nicoli";
	string str2 = "Aesha M";
	cout << lexicographical_compare(str1.begin(), str1.end(), str2.begin(), str2.end()) << endl;

	// mismatch
	sort(v.begin(), v.end());
	sort(u.begin(), u.end());
	auto result = mismatch(v.begin(), v.end(), u.begin());
	cout << (result.first == v.end() && result.second == u.end() ? "match" : "mismatch") << endl;
	shuffle(u.begin(), u.end(), default_random_engine());
	result = mismatch(v.begin(), v.end(), u.begin());
	cout << (result.first == v.end() && result.second == u.end() ? "match" : "mismatch") << endl;

}

void QUERIES_SEARCH()
{
	// find - non-sorted collection
	auto v = PrepareVector(10, 10);
	int s = 15;
	PrintVector(v);
	auto findItr = find(v.begin(), v.end(), s);
	//cout << "v[" << findItr - v.begin() << "] = " << *findItr << endl;

	//s = v[4] = v[5] = 3;
	auto adjItr = adjacent_find(v.begin(), v.end(), [](int x, int y) {return x == y; });
	//PrintVector(v);
	//cout << adjItr - v.begin() << endl;

	// pre-req: Sorted Collection
	sort(v.begin(), v.end());
	// search
	cout << binary_search(v.begin(), v.end(), s) << endl;
	v[6] = v[7] = v[5] = s;
	PrintVector(v);
	auto eq_pair = equal_range(v.begin(), v.end(), s);
	cout << "v[" << eq_pair.first - v.begin() << "] = " << *eq_pair.first << endl;
	cout << "v[" << eq_pair.second - v.begin() - 1 << "] = " << *(eq_pair.second-1) << endl;
	cout << "v[" << lower_bound(v.begin(), v.end(), s) - v.begin() << "] " << endl;
	cout << "v[" << upper_bound(v.begin(), v.end(), s) - v.begin() << "] " << endl;

	// searching in range
	v = PrepareVector(10, 10);
	auto sub = PrepareVector(12, 3);
	PrintVector(v);
	auto ffo = find_first_of(v.begin(), v.end(), sub.begin(), sub.end());
	cout << ffo - v.begin() << endl;
	sort(v.begin(), v.end());
	sort(sub.begin(), sub.end());
	auto searchItr = search(v.begin(), v.end(), sub.begin(), sub.end());
	cout << (searchItr == v.end()) << endl;

	v[6] = 12;
	v[7] = 13;
	v[8] = 14;
	PrintVector(v);
	searchItr = find_end(v.begin(), v.end(), sub.begin(), sub.end());
	cout << searchItr - v.begin() << endl;

	//searching for relative values
	shuffle(v.begin(), v.end(), default_random_engine());
	cout << *min_element(v.begin(), v.end()) << endl;
	cout << *max_element(v.begin(), v.end()) << endl;
	auto mmp = minmax_element(v.begin(), v.end());
	cout << *mmp.first << ' ' << *mmp.second << endl;
}

void SET_ALGOS()
{
	/*
	data set-index 0	1	2	3	4	5	6	7	8	9
	data		   x    x   x   x   x   x   x   x   x   x

	result of algo 1:
	index->    0	1	2	3	4	5	6	7	8	9 (maps 1-1 to data-set index)
	result->   0	1	1	0	1	0	1	0	0	0

	result of algo 2:
	index->    0	1	2	3	4	5	6	7	8	9 (maps 1-1 to data-set index)
	result->   1	0	1	0	1	1	1	0	1	0
	*/

	auto v = PrepareVector(0, 10);
	for_each(v.begin(), v.end(), [](int& x) { x = x % 2; });
	auto u = PrepareVector(0, 10);
	for_each(u.begin(), u.end(), [](int& x) { x = x % 2; });
	shuffle(u.begin(), u.end(), default_random_engine(static_cast<int>(time(0))));

	typedef pair<int, int>iip;
	set<iip> setA, setB;

	int i = 0;
	for_each(v.begin(), v.end(), [&](int x) {
		if (x == 1)
			setA.insert({ x, i });
		i++;
		});
	i = 0;
	for_each(u.begin(), u.end(), [&](int x) {
		if (x == 1)
			setB.insert({ x, i });
		i++;
		});
	cout << "setA:" << endl;
	for_each(setA.begin(), setA.end(), [](iip p) {cout << p.second << ' '; });
	cout << endl;
	cout << "setB:" << endl;
	for_each(setB.begin(), setB.end(), [](iip p) {cout << p.second << ' '; });
	cout << endl;
	vector<iip> results;

	set_intersection(setA.begin(), setA.end(), setB.begin(), setB.end(), back_inserter(results));
	cout << "Alog 1 & Algo 2 detect numbers at:" << endl;
	for_each(results.begin(), results.end(), [](iip p) { cout << p.second << ' '; });
	cout << endl;

	results.clear();
	set_difference(setA.begin(), setA.end(), setB.begin(), setB.end(), back_inserter(results));
	cout << "numbers detected at indices by only Algo 1:" << endl;
	for_each(results.begin(), results.end(), [](iip p) { cout << p.second << ' '; });
	cout << endl;

	results.clear();
	set_union(setA.begin(), setA.end(), setB.begin(), setB.end(), back_inserter(results));
	cout << "numbers detected at indices by Algo 1 or Ago 2:" << endl;
	for_each(results.begin(), results.end(), [](iip p) { cout << p.second << ' '; });
	cout << endl;

	results.clear();
	set_symmetric_difference(setA.begin(), setA.end(), setB.begin(), setB.end(), back_inserter(results));
	cout << "numbers detected at indices only by Algo 1 + only by Ago 2:" << endl;
	for_each(results.begin(), results.end(), [](iip p) { cout << p.second << ' '; });
	cout << endl;

	auto w = PrepareVector(0, 10);
	auto y = PrepareVector(3, 5);
	sort(w.begin(), w.end());
	sort(y.begin(), y.end());

	cout << includes(w.begin(), w.end(), y.begin(), y.end()) << endl;

	vector<int> merged(w.size() + y.size());
	merge(w.begin(), w.end(), y.begin(), y.end(), merged.begin());
	PrintVector(merged);
}

void MOVERS()
{
	auto v = PrepareVector(0, 10);
	vector<int> u(v);
	copy(v.begin(), v.end(), u.begin());
	PrintVector(v);
	cout << "u copied from v: " << endl;
	PrintVector(u);

	vector<int> w(v);
	move(v.begin(), v.end(), w.begin());
	cout << "v moved to w: showing w, v " << endl;
	PrintVector(w);
	PrintVector(v);

	auto x = PrepareVector(11, 10);
	swap_ranges(u.begin(), u.end(), x.begin());
	cout << "x swapped with u: showing u, x" << endl;
	PrintVector(u);
	PrintVector(x);

	sort(v.begin(), v.end());
	PrintVector(v);
	copy_backward(v.begin() + 1, v.begin() + 5, v.begin() + 8);
	cout << "Copy backwards: " << endl;
	PrintVector(v);

	sort(w.begin(), w.end());
	move_backward(w.begin() + 1, w.begin() + 5, w.begin() + 8);
	cout << "Move backwards: " << endl;
	PrintVector(w);
}

void VALUE_MODIFIERS()
{
	vector<int> v(10);
	fill(v.begin(), v.end(), 55);
	PrintVector(v);

	generate(v.begin(), v.end() - 2, []() {return std::rand() % 50; });
	PrintVector(v);

	replace(v.begin(), v.end(), 24, 55);
	PrintVector(v);
}

void STRUCTURE_CHANGERS()
{
	auto v = PrepareVector(1, 10);
	v[2] = v[4] = v[5] = 99;
	sort(v.begin(), v.end());
	PrintVector(v);

	auto itrEnd = remove(v.begin(), v.end(), 99);
	cout << distance(v.begin(), itrEnd) << endl;
	v.erase(itrEnd, v.end());
	PrintVector(v);

	v = PrepareVector(1, 10);
	v[2] = v[4] = v[5] = 99;
	v[0] = v[9] = 1;
	v[8] = 99;
	//sort(v.begin(), v.end());
	PrintVector(v);
	itrEnd = unique(v.begin(), v.end());
	cout << distance(v.begin(), itrEnd) << endl;
	v.erase(itrEnd, v.end());
	PrintVector(v);
}

void RUNE_COPY()
{
	auto v = PrepareVector(1, 10);
	auto w = PrepareVector(1, 10);
	sort(v.begin(), v.end());
	partial_sort(w.begin(), w.begin() + 5, w.end());
	vector<int>x(5);
	partial_sort_copy(v.begin(), v.begin() + 5, x.begin(), x.end());
	PrintVector(v);
	PrintVector(w);
	PrintVector(x);
}

void RUNE_IF()
{
	auto v = PrepareVector(1, 10);
	sort(v.begin(), v.end());
	auto itr = find_if(v.begin(), v.end(), [](int x) { return !(x % 2); });
	cout << (v.end() == itr) << endl;
	cout << *itr << endl;
	v[1] = v[2] = 3;
	auto evens = count_if(v.begin(), v.end(), [](int x) {return !(x % 2); });
	PrintVector(v);
	cout << "Count of evens is " << evens << endl;
}

void LONELY_ISLANDS()
{
	//transform
	struct point {
		int x;
		int y;
		point() { x = 0; y = 0; }
		point(int a, int b) { x = a; y = b; }
	};

	vector<point> x = { {1,2}, {2,-3}, {-5,8}, {-3,-1} };
	vector<point> mirror(x.size());
	transform(x.begin(), x.end(), mirror.begin(), [](point p) {return point(-p.x, -p.y); });
	for_each(mirror.begin(), mirror.end(), [](point p)
		{
			cout << "{" << p.x << "," << p.y << "},";
		});
	cout << endl;

	auto u = PrepareVector(1, 10);
	auto v = PrepareVector(1, 10);

	vector<int> r(v.size());
	transform(u.begin(), u.end(), v.begin(), r.begin(), [](int x, int y) {return x * y; });
	PrintVector(u);
	PrintVector(v);
	PrintVector(r);

	//for_each
}


