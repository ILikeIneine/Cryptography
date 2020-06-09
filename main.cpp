#include "main.h"
int main() {
	string ans;
	string num_1 = "2225235";
	string num_2 = "121151123123132133782135";
	cout << "testing";
	if ((Miller_Rabin_test(num_2) == true))
		cout << "is prime" << endl;
	else cout << " not prime" << endl;
//	cout << Miller_Rabin_test("23");
//	cout << int_subs("100", "97");
//		if ((Miller_Rabin_test(num_2) == true))
//			cout << "is prime" << endl;
//		else cout << " not prime" << endl;
//	cout << mod_mult("123", "12", "16");
//	cout << inv(num_1, num_2);


	

}