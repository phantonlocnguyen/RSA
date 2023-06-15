#include<bits/stdc++.h>

//Cac ham tinh toan
int checkPrime(int n); //Ham kiem tra so nguyen to
int GCD(int a, int b); //Ham tim UCLN
void exEuler(int a, int b, int *x, int *y); //Ham Euler
int powMod(int x, int n, int m); //Ham tinh x^n mod m

//Cac ham RSA
void crKeysRSA(int *n, int *e, int *d); //Ham hai tao khoa
int enRSA(int n, int e, int mess); //Ham ma hoa RSA
int deRSA(int n, int d, int c); //Ham giai ma RSA

int main() {	
	int n, e, d, mess1, mess2, c;
	time_t t;
	srand((unsigned int) time(&t));
	
	printf("\n-------------------- TAO KHOA --------------------\n");
	crKeysRSA(&n, &e, &d);
	printf("\n\t=> Khoa Cong Khai: n = %d, e = %d\n", n, e);
	printf("\t=> Khoa Rieng Tu: n = %d, d = %d\n", n, d);
	printf("--------------------------------------------------\n");
	
	printf("\n--------------------- MA HOA ---------------------\n");
	do {
		mess1 = rand()%n;
	} while(mess1 >= n);
	printf("- Thong tin can ma hoa: %d\n", mess1);
	c = enRSA(n, e, mess1);
	printf("- Khoa Cong Khai: n = %d, e = %d\n", n, e);
	printf("\n\t=> Noi Dung Sau Khi Ma Hoa: %d\n", c);
	printf("--------------------------------------------------\n");
	
	printf("\n-------------------- GIAI MA ---------------------\n");
	mess2 = deRSA(n, d, c);
	printf("- Noi dung nhan duoc: %d\n", c);
	printf("- Khoa Rieng Tu: n = %d, d = %d\n", n, d);
	printf("\n\t=> Noi Dung Ban Dau: m = %d\n", mess2);
	printf("--------------------------------------------------\n");
	return 0;
}


int checkPrime(int n){
	for(int i = 2; i <= sqrt(n); i++)
		if(n % i == 0) return 0;
	return 1;
}


int GCD(int a, int b) {
	if(b == 0) return a;
	else return GCD(b, a%b);
}


void exEuler(int a, int b, int *x, int *y) {
    int xa = 1, xb = 0, ya = 0, yb = 1;
    int q, r, xr, yr;
    while (b != 0) {
        q = a / b;
        r = a % b;
        a = b;
        b = r;
        xr = xa - q * xb;
        yr = ya - q * yb;
        xa = xb;
        xb = xr;
        ya = yb;
        yb = yr;
    }
    *x = xa;
    *y = ya;
}


int powMod(int x, int n, int m) {
    int p;
	if (n == 0) return 1;
	p = powMod(x, n/2, m);
	if (n%2 == 0) return (p * p) % m;
	else return (p * p * x) % m;
}


void crKeysRSA(int *n, int *e, int *d) {
	int p, q, x, y, phi_n;
	
	// Chon ngau nhien p, q; tinh n
	do {
		p = rand()%100;
		q = rand()%100;
		*n = p * q;
	} while(!checkPrime(p) || !checkPrime(q) || p == q || *n < 100 || *n > 1000);
	printf("- p = %d, q = %d\n", p, q);
	printf("- n = p * q = %d\n", *n);
	
	// Tinh phi(n)
	phi_n = (p - 1) * (q - 1);
	printf("- phi_n = %d\n", phi_n);
	
	// Chon ngau nhien e  (1 < e < phi(n) && nguyen to cung nhau voi phi(n))
	do {
		*e = rand();
	} while( *e <= 1 || *e >= phi_n || GCD(*e, phi_n) != 1);

	// Tinh d
	exEuler(*e, phi_n, &x, &y);
	if(x < 0)
		x += phi_n;
	*d = x;
	printf("- e = %d, d = %d\n", *e, *d);
}


int enRSA(int n, int e, int m) {
	return powMod(m, e, n);
}


int deRSA(int n, int d, int c) {
	return powMod(c, d, n);
}
