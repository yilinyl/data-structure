#include<iostream>
using namespace std;
int gcd(int a, int b){
	int x = a%b;
	if (x == 0)
		return b;
	if (x == 1)
		return 1;
	else {
		int c = a;
		a = b;
		b = c%b;
		return gcd(a, b);
	}
}

int main(){
	int a, b, x;
	cout << "请输入a,b的值" << endl;
	cin >> a >> b;
	x = gcd(a, b);
	if (x == 1)
		cout << a << " 和" << b << "互质，没有公约数" << endl;
	else cout << a << "和" << b << "的最大公约数是：" << x << endl;
	return 0;
}
