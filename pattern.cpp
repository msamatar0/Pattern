/*
 * Mohamed Samatar - 101848
 * Assignment 13 - Pattern Matching
 * Description - Compares the 3 pattern-matching algorithms
 */
#include <iostream>
#include <string>
#include <functional>
using namespace std;

//Returned by search-type functions
//indicates found index and # of comparisons used
struct search{
	int idx, comparisons;
};

void searchFunc(function<search(string, string)> func, string text, string pattern);
search bruteForceSearch(string t, string p);
search bmMatch(string t, string p);
search kmpMatch(string t, string p);

int main(){
	cout << "/*\n * Mohamed Samatar - 101848\n * Assignment 13 - Pattern Matching\n"
		<< " * Description - Compares the 3 pattern-matching algorithms\n */\n\n";
	string text = "aaabcaadaabaaa", pattern = "aabaaa";
	cout << "P1 - Brute Force:\n";
	searchFunc(bruteForceSearch, text, pattern);
	cout << "P2 - Boyer-Moore:\n";
	searchFunc(bmMatch, text, pattern);
	cout << "P3 - KMP:\n";
	searchFunc(kmpMatch, text, pattern);
}

//Calls search function and outputs results
void searchFunc(function<search(string, string)> func, string text, string pattern){
	search result = func(text, pattern);
	cout << text << (result.idx != -1 ? " contains" : " does not contain")
		<< " " << pattern<< " starting at index #" << result.idx << ": "
		<< result.comparisons << " comparisons used\n\n";
}

//Brute Force Matching algorithm
search bruteForceSearch(string t, string p){
	int comps = 0;
	int n = t.length(), m = p.length();
	for(int i = 0; i < n; ++i){
		int j = 0;
		while(t[i + j] == p[j]){
			if(j == m)
				return{ i, comps };
			j++;
			comps++;
		}
		comps++;
	}
	return{ -1, comps };
}

//Boyer-Moore Matching Algorithm
search bmMatch(string t, string p){
	int comps = 0;
	int n = t.length(), m = p.length();
	int i = m - 1, j = m - 1;;
	do{
		if(t[i] == p[j]){
			if(j == 0)
				return{ i, ++comps };
			else{
				i--;
				j--;
			}
		}
		else{
			int x = 1 + p.find_last_of(t[i]);
			i += m - (j < 1 + x? j : x);
			j = m - 1;
		}
		comps++;
	}while(!(i > n - 1));
	return{ -1, comps };
}

//Boyer-Moore Matching Algorithm
search kmpMatch(string t, string p){
	int comps = 0;
	int n = t.size(), m = p.size();
	int *fail = new int[m];
	fail[0] = 0;
	int i = 1, j = 0;
	while(i < m){
		if(p[i] == p[j])
			fail[i++] = ++j;
		else if(j > 0)
			j = fail[j - 1];
		else
			fail[i++] = 0;
	}
	while(i < n){
		if(t[i] == p[j]){
			if(j == m - 1){
				delete[] fail;
				return{i - m + 1, ++comps};
			}
			i++;
			j++;
		}
		else if(j > 0)
			j = fail[j - 1];
		else
			i++;
		comps++;
	}
	delete[] fail;
	return{ -1, comps };
}
