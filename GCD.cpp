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
	cout << "������a,b��ֵ" << endl;
	cin >> a >> b;
	x = gcd(a, b);
	if (x == 1)
		cout << a << " ��" << b << "���ʣ�û�й�Լ��" << endl;
	else cout << a << "��" << b << "�����Լ���ǣ�" << x << endl;
	return 0;
}
