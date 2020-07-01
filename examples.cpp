#include<iostream>
#include<vector>
#include<numeric>
#include<algorithm>
#include<random>
#include<execution>
#include <set>
#include <string>
#include <iomanip>
using namespace std;

#pragma region E1
/*E1
Sort the vector v in descending order
*/
void E1()
{
	vector<int> v = { 23, 17, 41, 53, 83, 18, 72, 84, 50, 12 };

	/* write code here*/
	sort(v.begin(), v.end(), [](int x, int y) {return x > y; });

	for_each(v.begin(), v.end(), [](int x) {cout << x << ' '; });
}
/*output:
84 83 72 53 50 41 23 18 17 12
*/
#pragma endregion

#pragma region E2
/* E2
radii is vector of radius of circles. These circles are drawn on +ve side of x-axis in increasing order of their radii. The smallest circle is drawn such that x=0 falls on the circle. Every subsequent circle is drawn such that the center of previous circle falls on it. Fill up xcoord vector with x-coordinates of the centers of these circles.
*/
void E2()
{
	vector<int> radii{ 10,8,15,9,7,3,12,2 };
	vector<int> xcoord;

	/* write code here*/
	sort(radii.begin(), radii.end());
	inclusive_scan(radii.begin(), radii.end(), back_inserter(xcoord));

	for_each(radii.begin(), radii.end(), [](int x) {cout << setw(2) << x << ' '; });
	cout << endl;
	for_each(xcoord.begin(), xcoord.end(), [](int x) {cout << setw(2) << x << ' '; });
}
/* output:
 2  3  7  8  9 10 12 15
 2  5 12 20 29 39 51 66
*/

#pragma endregion

#pragma region E3
/*E3
All 0's should be in the middle of the vector. Rest of the vector should be sorted. See output.
*/
void E3()
{
	vector<int> mid{ 1,7,2,0,9,4,0,8,6,0,3 };

	/* write code here*/
	sort(mid.begin(), mid.end());
	auto ub = upper_bound(mid.begin(), mid.end(), 0);
	auto nonZero = distance(ub, mid.end());
	rotate(mid.begin(), ub, ub + (nonZero / 2));

	for_each(mid.begin(), mid.end(), [](int x) {cout << x << ' '; });
}
/* output:
1 2 3 4 0 0 0 6 7 8 9
*/
#pragma endregion

#pragma region E4
/*E4
s = ut + ½ at²
Calculate s when u, t and a are given. Put s values in its vector. You should use
corresponding values of u, a and t to calculate s. i.e. s[i] = u[i]t[i] + ½ a[i]t[i]² for ith
element.
*/
void E4()
{
	vector<float> u = { 0.0, 0.0, 3.0, 2.3, 6.4, 3.2, 8.2, 1.5 };
	vector<float> t = { 5.0, 7.0, 9.0, 25.0, 15.0, 1.0, 8.0, 20.0 };
	vector<float> a = { 0.6, 0.8, 1.0, 1.3, 0.4, 0.2, 2.2, 0.5 };
	vector<float> s;

	/* write code here*/
	vector<float> ut;
	transform(u.begin(), u.end(), t.begin(), back_inserter(ut), [](auto x, auto y) {return x * y; });

	vector<float> at;
	transform(a.begin(), a.end(), t.begin(), back_inserter(at), [](auto x, auto y) { return 0.5 * x * y * y; });

	transform(ut.begin(), ut.end(), at.begin(), back_inserter(s), [](auto x, auto y) {return x + y; });

	for_each(s.begin(), s.end(), [](float si) {cout << fixed << setprecision(2) << si << ' '; });
}
/*output:
7.50 19.60 67.50 463.75 141.00 3.30 136.00 130.00
*/
#pragma endregion

#pragma region E5
/*E5
At US airport arrivals, passengers are segregated into two queues - one for US nationals and other for aliens (yes, they call non-US nationals as aliens!).
Simulate this arrangement in the following three vectors. From arrivals vector usn and aliens
vectors should get filled with US and aliens respectively.
*/
void E5()
{
	vector<string> arrivals{ "US", "IN", "US", "UK", "FR", "IN", "US", "US", "GE", "SP" };
	vector<string> usn, aliens;

	/* write code here*/
	auto itr = partition(arrivals.begin(), arrivals.end(), [](auto n) {return n == "US"; });
	//for_each(arrivals.begin(), arrivals.end(), [](auto x) {cout << x << ' '; });
	//cout << endl;
	move(arrivals.begin(), itr, back_inserter(usn));
	move(itr, arrivals.end(), back_inserter(aliens));

	arrivals.clear();
	for_each(usn.begin(), usn.end(), [](string n) {cout << n << ' '; });
	cout << endl;
	for_each(aliens.begin(), aliens.end(), [](string n) {cout << n << ' '; });
}
/*output:
US US US US
FR IN UK IN GE SP
*/
#pragma endregion

#pragma region E6
/*E6
A collection of patients with Covid symptoms comes to a hospital. It needs to decide the priority order in which the ambulance should be sent to patients to pick them for testing and treatment.
Highest priority: least oxygen level, high temperature, diabetic
Arrange the data in priority queue.
*/
void E6()
{
	struct CovidSymptoms {
		int patientID;
		float oxyLevel;
		float temp;
		bool isDiabetic;
		bool operator() (const CovidSymptoms& p1, const CovidSymptoms& p2) const {
			if (p1.oxyLevel < p2.oxyLevel)
				return false;
			else if (p1.oxyLevel == p2.oxyLevel && p1.temp > p2.temp)
				return false;
			else if (p1.oxyLevel == p2.oxyLevel && p1.temp == p2.temp && p1.isDiabetic && !p2.isDiabetic)
				return false;
			return true;
		}
	};

	vector<CovidSymptoms> patients {
		{ 1001, 100.0, 98.4, false},
		{ 1002, 96.0, 98.4, false },
		{ 1003, 80.0, 100.1, true },
		{ 1004, 110.0, 98.4, false },
		{ 1005, 90.0, 101.2, false },
		{ 1006, 100.0, 102.4, true },
		{ 1007, 80.0, 101.3, true },
		{ 1008, 100.0, 98.4, false },
	};
	
	/* write code */
	make_heap(patients.begin(), patients.end(), CovidSymptoms());
	pop_heap(patients.begin(), patients.end(), CovidSymptoms());

	cout << "Send ambulance to patient ID " << (*(patients.end() - 1)).patientID << endl;
	patients.pop_back();

	for_each(patients.begin(), patients.end(), [](CovidSymptoms s) { cout << s.patientID << ' '; });
}
/*output:
Send ambulance to patient ID 1007
1003 1005 1006 1008 1002 1004 1001
*/
#pragma endregion

int main()
{
  E1();
  E2();
  E3();
  E4();
  E5();
	E6();
}
