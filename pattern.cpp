#include <iostream>
#include <string>
#include <vector>
#include <functional>
using namespace std;

//Returned by search -type functions
//indicates found index and # of comparisons used
struct search{
	int idx, comparisons;
};

void searchFunc(function<search(string, string)> func, string text, string pattern);
search bruteForceSearch(string t, string p);
search boyerMatch(string t, string p);
search kmp(string t, string p);
vector<int> failure(string p);

int main(){
	system("cls");
	string text = "aaabcaadaabaaa", pattern = "aabaaa";
	searchFunc(bruteForceSearch, text, pattern);
	searchFunc(boyerMatch, text, pattern);
	searchFunc(kmp, text, pattern);
}

void searchFunc(function<search(string, string)> func, string text, string pattern){
	search result = func(text, pattern);
	cout << text << (result.idx != -1 ? " contains" : " does not contain") << " " << pattern << endl
		 << result.comparisons << (result.comparisons == 1? " comparison used\n" : " comparisons used\n");
}

//Brute Force Matching algorithm
search bruteForceSearch(string t, string p){
	int comps = 0;
	int n = t.length(), m = p.length();
	for(int i = 0; i < n - m; ++i){
		int j = 0;
		while(j < m && t[i + j] == p[j]){
			j++;
			if(j == m)
				return{ i, ++comps };
		}
		comps++;
	}
	return{ -1, comps };
}

//Boyer-Moore Matching Algorithm
search boyerMatch(string t, string p){
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
search kmp(string t, string p){
	int comps = 0;
	int n = t.size(), m = p.size();
	vector<int> fail = failure(p);
	int i = 0, j = 0;
	while(i < n){
		if(t[i] == p[j]){
			if(j == m - 1)
				return{ i - m + 1, ++comps };
			i++;
			j++;
		}
		else if(j > 0)
			j = fail[j - 1];
		else
			i++;
		comps++;
	}
	return{ -1, comps };
}

//Knuth-Morris-Pratt Matching Algotirhm
vector<int> failure(string p){
	int m = p.length();
	vector<int> f(m);
	f[0] = 0;
	int i = 1, j = 0;
	while(i < m){
		if(p[i] == p[j])
			f[i++] = ++j;
		else if(j > 0)
			j = f[j - 1];
		else
			f[i++] = 0;
	}
	return f;
}
