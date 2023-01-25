#include <iostream>
# include <math.h>

using namespace std;

double countingS(double a, double b, double n) {
	double s = (b - a) / n;
	return s;
}

void setArrX(double*& x, double s, double n, double a) {	
	double divider = a;	
	for (int i = 0; i < n; i++) {
		x[i] = divider;
		divider += s;
	}
}

void getArr(double* x, double n) {
	for (int i = 0; i < n; i++) {
		cout << "x" << i << " = "<< x[i] << endl;
	}
}

double getFun(double x, int m) {
	double f = 0;
	if (m == 1) {
		f = sin(x);
	}
	if (m == 2) {
		f = (pow(x, 2)) + (2 * x) + 5;
	}
	if (m == 3) {
		f = exp(x);
	}
	return f;
}

double getFun2(double x) {
	double f = (pow(x, 2)) + (2 * x) + 5;
	return f;
}


void setH(double*& h, double* x, double s, double n, int m) {
	double temp = s / 2; 
	double f = 0;
	for (int i = 0; i < n; i++) {
		f = getFun((x[i] + temp), m);
		h[i] = f;
	}
}


void calkaProstokatow(double* h, double s, double n) {
	double calka = 0;
	for (int i = 0; i < n; i++) {
		calka += s * h[i];
	}
	cout << "Metoda Prostokatow : " << calka << endl;
}

void calkaTrapezow(double* x, double n, double s, int m) {
	double calka = 0;
	double a, b, fa, fb = 0;
	for (int i = 0; i < n; i++) {
		int j = i + 1;
		a = x[i];
		b = x[j];
		fa = getFun(a, m);
		fb = getFun(b, m);
		calka += (fa + fb) / 2 * (b - a);
	}
	cout << "Metoda Trapezow: " << calka << endl;
}

void calkaParabol(double* x, double n, double s, int m) {
	double calka = 0;
	double a, b, fa, fb, fc = 0;
	for (int i = 0; i < n; i++) {
		int j = i + 1;
		a = x[i];
		b = x[j];
		fa = getFun(a, m);
		fb = getFun(b, m);
		fc = 4 * (getFun(((a + b) / 2), m));
		calka += (fa + fc + fb) / 6 * (b - a);
	}
	cout << "Metoda Parabol : " << calka << endl;
}

void kwadratura(double*& t, int k, double* x, double* xi, int n) {		
	for (int i = 0; i < k; i++) {		
		t[i] = (x[0] + x[n]) / 2 + (((x[n] - x[0]) / 2) * xi[i]);		
	}
}

void przedzial(double*& xi, double *& Ai, int k) {
	if (k == 2) {
		xi[0] = -0.57735;
		xi[1] = 0.57735;
		Ai[0] = 1;
		Ai[1] = 1;
	}
	if (k == 4) {
		xi[0] = -0.861136;
		xi[1] = -0.339981;
		xi[2] = 0.339981;
		xi[3] = 0.861136;
		Ai[0] = 0.347855;
		Ai[1] = 0.652145;
		Ai[2] = 0.652145;
		Ai[3] = 0.347855;
	}
	if(k != 2 && k != 4) {
		cout << "Zla liczba wezlow kwadratury" << endl;
		exit(0);
	}
}

void calkaGaussa(double* t, double* ai, double* x, int k, int n, int m) {
	double calka = 0;
	double temp = (x[n] - x[0]) / 2;	
	for (int i = 0; i < k; i++) {
		double ft = getFun(t[i], m);		
		calka += ft * ai[i] * temp;	
	}
	cout << "Metoda Gaussa-Legendre'a : " << calka << endl;
}

void metodaProstokatow(double n, double a, double b, double s, int m){
	double* x = new double[n];
	setArrX(x, s, n, a);	
	double* h = new double[n];
	setH(h, x, s, n, m);
	calkaProstokatow(h, s, n);
	delete[] h, x;
}

void metodaTrapezow(double n, double s, int m, double a){
	double* x = new double[n+1];
	setArrX(x, s, n+1, a);	
	calkaTrapezow(x, n, s, m);
	delete[] x;
}

void metodaParabol(double n, double s, int m, double a) {
	double* x = new double[n + 1];
	setArrX(x, s, n + 1, a);	
	calkaParabol(x, n, s, m);
	delete[] x;
}

void metodaGaussa(double n, double s, int m, double a) {
	int k = 0;
	cout << "Liczba wezlow kwadratury : ";
	cin >> k; 
	double* t = new double[k];
	double* xi = new double[k];
	double* ai = new double[k];
	przedzial(xi, ai, k);
	double* x = new double[n + 1];
	setArrX(x, s, n + 1, a);
	kwadratura(t, k, x, xi, n);
	calkaGaussa(t, ai, x, k, n, m);
}

void getPrzedzial(double a, double b) {
	cout << "Przedzial <" << a << ", " << b << ">" << endl;
}

void menu(double n, double a, double b) {
	cout << "Wybierz rowanie: "<<endl << "1. f(x) = sin(x)" << endl <<
		"2. f(x) = x^2 + 2x + 5" << endl << "3. f(x) = exp(x)" << endl;
	int m = 0;
	cin >> m;
	if (m == 1) {
		a = 0.5;
		b = 2.5;
		cout << "f(x) = sin(x)" << endl;	
	}
	if (m == 2) {
		a = 0.5;
		b = 5.0;
		cout << "f(x) = x^2 + 2x + 5" << endl;		
	}
	if (m == 3) {
		a = 0.5;
		b = 5.0;
		cout << "f(x) = exp(x)" << endl;		
	}
	if (m != 1 && m != 2 && m != 3) {
		exit(0);
	}
	getPrzedzial(a, b);
	cout << "Liczba przedzialow : " << n << endl;
	double s = countingS(a, b, n);
	metodaProstokatow(n, a, b, s, m);
	metodaTrapezow(n, s, m, a);
	metodaParabol(n, s, m, a);
	metodaGaussa(n, s, m, a);
}

int main() {	
	double n = 4;
	double a = 0;
	double b = 0;	
	menu(n, a, b);
	return 0;
}