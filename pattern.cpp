#include <iostream>
#include <string>
using namespace std;

int patternSearch(string t, string p);
int boyerMatch(string t, string p);

int main(){
	string s("abcdefghijklmnopqrstuvwxyyzdcba"), p("lmnop");
	cout << s << " " << (boyerMatch(s, p) != -1? "contains" : "does not contain") << " " << p << endl;
	p = "7777777";
	cout << s << " " << (boyerMatch(s, p) != -1 ? "contains" : "does not contain") << " " << p << endl;

}

//Brute force pattern search
int patternSearch(string t, string p){
	int n = t.length(), m = p.length();
	for(int i = 0; i < n - m; i++)
		for(int j = 0; j < m && t[i + j] == p[j]; ++j)
			if(j == m)
				return i;
	return -1;
}


int boyerMatch(string t, string p){
	int n = t.length(), m = p.length();
	int i = m - 1, j = m - 1;;
	do{
		if(t[i] == p[j]){
			if(j == 0)
				return i;
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
	}while(!(i > n - 1));
	return -1;
}