#include "Mod.h"

int cmp(string num1, string num2)
{
	if (num1.length() < num2.length())
			return -1;
	else if (num1.length() > num2.length())
		return 1;
	else
		return num1.compare(num2);
}

string int_add(string num_1, string num_2)
{
	int sign = 1;
	string ans;
	if (num_1[0] == '-')
	{
		if (num_2[0] == '-')	//num1<0  num2<0  --->  -(num1+num2)
		{
			sign = -1;
			ans = int_add(num_1.erase(0, 1), num_2.erase(0, 1));
		}
		else {					//num1<0 num2>0   --->  num2-num1
			ans = int_subs(num_2, num_1.erase(0, 1));
		}
	}
	else {
		if (num_2[0] == '-')	//num1>0 num2<0   --->	num1-num2
		{
			ans = int_subs(num_1, num_2.erase(0, 1));
		}
		else {					//num1>0 num2>0	  --->  num1+num2
			string::size_type len_1, len_2;
			len_1 = num_1.size();
			len_2 = num_2.size();
			if (len_1 < len_2)			//num_1 needs padding '0's in front
			{
				for (int i = 0; i < len_2 - len_1; i++) {
					num_1 = '0' + num_1;
				}
			}
			else {						//num_2 needs padding '0's in front 
				for (int i = 0; i < len_1 - len_2; i++)	{
					num_2 = '0' + num_2;
				}
			}
			int rslt= 0, carry = 0;
			for (int i = num_1.size() - 1; i >= 0; i--)
			{
				rslt = ((int)(num_1[i] - '0') + (int)(num_2[i] - '0') + carry) % 10;
				carry= ((int)(num_1[i] - '0') + (int)(num_2[i] - '0') + carry) / 10;
				ans = char(rslt + '0') + ans;
			}
			if (carry == 1)
				ans = '1' + ans;
		}
	}
	if (sign == -1 && ans[0] != '0')
		ans = '-' + ans;
	return ans;
}

string mod_add(string num_1, string num_2, string mod)
{
	return _mod(int_add(num_1, num_2), mod);
}

string int_subs(string num_1, string num_2)
{
	int sign = 1;
	string ans;
	if (num_2[0] == '-')
	{
		if (num_1[0] == '-')  //-num1 - (-num2) 
		{
			ans = int_subs(num_2.erase(0, 1), num_1.erase(0, 1));
		}
		else
			ans = int_add(num_1, num_2.erase(0, 1));
	}
	else {
		if (num_1[0] == '-')  //(-) - (+) = (-)
		{
			sign = -1;
			ans = int_add(num_1.erase(0, 1), num_2);
		}
		else {
			if (cmp(num_1, num_2) == 0)		//num1 = num2 result is "0"
				return "0";
			if (cmp(num_1, num_2) == -1)	//num1 < num2  exchange num1 and num2 & ANSWER is negative
			{
				sign = -1;
				string tmp = num_1;
				num_1 = num_2;
				num_2 = tmp;
			}
			string::size_type len_1, len_2, dist;
			len_1 = num_1.size();
			len_2 = num_2.size();
			dist = len_1 - len_2;
			int rslt = 0, carry = 0;
			for (int i = num_2.size() - 1; i >= 0; i--)
			{
				rslt = ((int)(num_1[i+dist] - '0') - (int)(num_2[i] - '0') + carry);
				if (rslt < 0) {
					rslt += 10;
					carry = -1;
				}
				else {
					carry = 0;
				}
				ans = char(rslt + '0') + ans;
			}
			for (int i = dist - 1; i >= 0; i--)
			{
				rslt = (int)(num_1[i] - '0') + carry;
				if (rslt < 0) {
					rslt += 10;
					carry = -1;
				}
				else
					carry = 0;
				ans = char(rslt + '0') + ans;
			}
		}
	}
	ans.erase(0, ans.find_first_not_of('0'));
	if (sign == -1)
		ans = '-' + ans;
	return ans;

}

string mod_subs(string num_1, string num_2, string mod)
{
	return _mod(int_subs(num_1, num_2), mod);
}

string int_mult(string num_1, string num_2)
{
	int sign = 1;
	string ans;
	if (num_1[0] == '-')
	{
		sign *= -1;
		num_1.erase(0, 1);
	}
	if (num_2[0] == '-')	//num1>0 num2<0   --->	num1-num2
	{
		sign *= -1;
		num_2.erase(0, 1);
	}
	if (cmp(num_1, num_2) == -1)	//num1 < num2  exchange num1 and num2 & ANSWER is negative
	{
		string tmp = num_1;
		num_1 = num_2;
		num_2 = tmp;
	}
	string::size_type len_1, len_2, dist;
	len_1 = num_1.size();
	len_2 = num_2.size();
	dist = len_1 - len_2;
	int rslt = 0, carry = 0;
	int i, j;
	string temp_ans;
	int first = 1, count = 0;
	ans = "0";
	for (i = len_2 - 1; i >= 0; i--, count++)
	{
		for (j = len_1 - 1; j >= 0; j--)
		{
		rslt = ((int)(num_1[j] - '0') * (int)(num_2[i] - '0') + carry) % 10;
		carry = ((int)(num_1[j] - '0') * (int)(num_2[i] - '0') + carry) / 10;
		temp_ans = char(rslt + '0') + temp_ans;
		}
		if (carry)
			temp_ans = char(carry + '0') + temp_ans;
		/***********THIS IS FUCKING STUPID***************/
		/*first time ans = tmpans;*/
		//if (first)
		//	ans = temp_ans;
		//else first = 0;
		/***********************************************/
		for (auto n = 1; n <= count; n++)
			temp_ans = temp_ans + '0';
		ans = int_add(temp_ans, ans);
		temp_ans.clear();
		/***********************************************************/
		carry = 0;	// WARNINIG!!!!! DO NOT TAKE IT TO NEXT TURN!!!!;
		/***********************************************************/
	}
	if (sign == -1)
		ans = '-' + ans;
	return ans;

};

string mod_mult(string num_1, string num_2, string mod)
{
	return _mod(int_mult(_mod(num_1, mod), _mod(num_2, mod)), mod);
}

string int_divi(string num_1, string num_2, int flag)
{
	string quotient, residue;
	int sign_1 = 1;
	int sign_2 = 1;
	if (num_2 == "0")
	{
		quotient = "Error!";
		residue = "Error!";
		return "ERROR";
	}
	if (num_1 == "0")
	{
		return "0";
	}
	if (num_1[0] == '-')
	{
		sign_1 *= -1;
		sign_2 = -1;
		num_1.erase(0, 1);
	}
	if (num_2[0] == '-')
	{
		sign_1 *= -1;
		num_2.erase(0, 1);
	}
	int val = cmp(num_1, num_2);
	if (val == -1)
	{
		quotient = "0";
		residue = num_1;
	}
	else if (0 == val)
	{
		quotient = "1";
		residue = "0";
	}
	else {
		string::size_type len_1, len_2, dist;
		len_1 = num_1.size();
		len_2 = num_2.size();
		dist = len_1 - len_2;
		int rslt = 0, carry = 0;
		int i;
		string temp_num_1;
		/********************Episode One************************/
		//string temp_mid;
		//string temp_quetient;
		//temp_num_1.append(num_1, 0, len_2);
		//int j;
		//for (i = len_2-1; i < len_1; i++)
		//{
		//	for (char ch = '9'; ch >= '0'; ch--)
		//	{
		//		temp_quetient = ch ;
		//		temp_mid= mod_mult(temp_quetient, num_2);
		//		if (cmp(temp_mid, temp_num_1) <= 0)
		//		{
		//			quotient = quotient + temp_quetient;
		//			temp_mid= mod_subs(temp_num_1, temp_mid);
		//			if (i < len_1)
		//			{
		//				temp_num_1 = temp_mid + num_1[i + 1];
		//				temp_num_1.erase(0, temp_num_1.find_first_not_of('0'));
		//				if (temp_num_1.empty())
		//					temp_num_1 = "0";
		//			}
		//			break;
		//		}
		//	}
		//}
		//residue = temp_mid;
		/********************Episode One************************/
		/********************Episode Two************************/
		string old_quotient;
		temp_num_1.append(num_1, 0, len_2 - 1);
		for (i = len_2 - 1; i < len_1; i++)
		{
			temp_num_1 = temp_num_1 + num_1[i];
			for (char ch = '9'; ch >= '0'; ch--) {
				if (old_quotient == "0")
					quotient = ch;
				else
					quotient = old_quotient + ch;

				if (cmp(int_mult(num_2, quotient), temp_num_1) <= 0)
				{
					old_quotient = quotient;
					break;
				}
			}
		}
		/********************Episode Two************************/
		quotient.erase(0, quotient.find_first_not_of('0'));
		if (quotient.empty())
			quotient = "0";
		residue = int_subs(num_1, int_mult(quotient, num_2));
	}
	//	quotient.erase(0, quotient.find_first_not_of('0'));
//	if (quotient.empty())
//		quotient = "0";
//	residue = mod_subs(num_1, mod_mult(quotient, num_2));
	if (-1 == sign_1)
		quotient = '-' + quotient;
	if (flag == 1)
		return quotient;
	else
		return residue;

}

string gcd(string n, string m)
{
	assert(!n.empty() && !m.empty());
	if (n == "0" || m == "0")
		return n == "0" ? m : n;
	string residue;
	while (m[0] != '0')
	{
		residue = _mod(n, m);
		n = m;
		m = residue;
	}
	return n;
	/********************/
	// if(m == "0")
	//	return n;
	// else return 
	//	gcd(m, mod(n,m));
	/********************/
}

string exgcd(string a, string b, string& x, string& y)
{
	string ans, t;
	if (b == "0")
	{
		x = "1";
		y = "0";
		return a;
	}
	ans = exgcd(b, _mod(a, b), x, y);
	t = x;
	x = y;												// x1 = y2
	y = int_subs(t, int_mult(int_divi(a, b, 1), y));	// y1 = x2 - (a/b) * y2

	cout << "x = " << x << "y = " << y << endl;
	return ans;											//ans = gcd(a,b)
}

string inv(string a, string p)
{
	assert(gcd(a, p) == "1");
	string x, y, gcd;
	gcd = exgcd(a, p, x, y);
	return _mod(int_add(_mod(x,p), p), p);
}

string _mod(string num_1, string num_2)
{
	return int_divi(num_1, num_2, 2);
}

string power_mod(string index, string power, string mod)
{
	if ("0" == power || "1" == index)
		return "1";
	string res("1");
	index = _mod(index, mod);
	while (power[0] != '0')
	{
		if (_mod(power, "2") == "1")
			res = _mod(int_mult(res, index), mod);
		index = _mod(int_mult(index, index), mod);
		power = int_divi(power, "2", 1);
	}
	return res;
}

void _pre_test(string n, string& r, string& d)
{
	r = "0";
	d = "0";
	while ("0" == _mod(n,"2"))
	{
		r = int_add(r, "1");		//get R;
		n = int_divi(n, "2", 1);	// n /= 2;
	}
	d = n;
}

bool witness(string a, string n, string r, string d)
{
	string x = power_mod(a, d, n);		//	a^d%
	if (x == "1" || x == int_subs(n, "1"))
		return true;
	while (r != "0")
	{
		x = power_mod(x, "2", n);		// a^(d*2 *2 *2 *2 *2)%n  ---> a^(d*2^r)%n
		if (x == int_subs(n, "1"))
			return true;
		r = int_subs(r, "1");
	}
	return false;
}

bool Miller_Rabin_test(string n)
{
	if (n == "2")
		return true;
	if ("0" == _mod(n, "2") || int_subs(n,"3")[0] == '-')		// n < 2  , n % 2
		return false;

	string R, D, a;
	_pre_test(int_subs(n, "1"), R, D);
	vector<string> prime_arr = { "2", "3", "5", "7","11","13","17" };
//	for (a = "2"; int_subs(int_subs(n, "1"), a)[0] != '0'; a = int_add(a, "1"))		//  1 < a < n-1
	for(int i = 0; i<prime_arr.size();i++)
	{

		if (!witness(prime_arr[i], n, R, D))
		{
				return false;
		}
	}
	return true;
}


/*
long long mod_divi(string num_1, string num_2, long long mod)
{
	long long ans;
	ans = (_mod(num_1, mod) * power_mod(_mod(num_2, mod), mod - 2, mod)) % mod;
	return ans;		
}
*/

/*
long long _mod(string num, long long n)
{
	long long ans = 0;
	for (int i = 0; i < num.length(); i++)
	{
		ans = (ans * 10 + num[i] - '0') % n;
	}
	return ans;
}

/*
long long power_mod(int index, int power, long long mod)
{
	if (0 == power || 1 == index)
		return 1;
	long long sum = 1;
	index = index % mod;
	while (power)
	{
		if (power & 1)
			sum = (sum * index) % mod;
		sum = (sum * sum) % mod;
		power >>= 1;
	}
	return sum;
}
*/


