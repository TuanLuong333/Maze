#include <bits/stdc++.h>
using namespace std;



int main()
{
	int n,res=0;cin>>n;
	cin.ignore(1);
	string a[n];
	map<string, int> mp;
	for(int i=0;i<n;i++)
	{
		getline(cin,a[i]);
		stringstream ss(a[i]);
		string word;
		vector<string> v;
		while(ss>>word)
		{
			v.push_back(word);
		}
		mp[v[v.size()-1]]++;
	}
	for(auto x : mp)
	{
		res=max(res,x.second);
	}
	cout<<res;
}
















