//From cp-algorithm (https://cp-algorithms.com/string/z-function.html)
//Not tested yet

vector<int> z_function (string s)
{
	vector<int> z(s.size());
	for(int i = 1, l = 0, r = 0 ; i < s.size() ; i++)
	{
		if(i <= r)
			z[i] = min(r - i + 1, z[i - l]);

		while(i + z[i] < s.size() and s[z[i]] == s[i + z[i]])
			z[i]++;

		if(i + z[i] - 1 > r)
			l = i, r = i + z[i] - 1;
	}

	return z;
}
