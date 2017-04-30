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
	int index, comparisons;
};

string getSearch(search (*fxn)(string, string), string text, string pattern);
search bruteForceSearch(string t, string p);
search bmMatch(string t, string p);
search kmpMatch(string t, string p);

int main(){
	cout << "/*\n * Mohamed Samatar - 101848\n * Assignment 13 - Pattern Matching\n"
		<< " * Description - Compares the 3 pattern-matching algorithms\n */\n\n";

	string text = "aaabcaadaabaaa", pattern = "aabaaa";
	cout << "P1 - Brute Force:\n" << getSearch(bruteForceSearch, text, pattern);
	cout << "P2 - Boyer-Moore:\n" << getSearch(bmMatch, text, pattern);
	cout << "P3 - KMP:\n" << getSearch(kmpMatch, text, pattern);
	cout << '\n' << getSearch(bruteForceSearch, text, "777777");
}

//Takes search function and returns string based on results of executing search function
string getSearch(search (*fxn)(string, string), string text, string pattern){
	search result = fxn(text, pattern);
	bool found = result.index != -1;
	return text + (found? " contains" : " does not contain") + " "
		+ pattern + (found? " starting at index #" + to_string(result.index) : "")
		+ ": " + to_string(result.comparisons) + " comparisons used\n\n";
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

//Knutt-Morris-Pratt Matching Algorithm
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
		comps++;
		if(t[i] == p[j]){
			if(j == m - 1){
				delete[] fail;
				return{i - m + 1, comps};
			}
			i++;
			j++;
			comps++;
		}
		else if(j > 0)
			j = fail[j - 1];
		else
			i++;
	}
	delete[] fail;
	return{-1, comps};
}
