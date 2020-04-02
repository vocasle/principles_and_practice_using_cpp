struct X {
	
	void f(int x) { // this function will call itself forewer
		struct Y {
			int f() { return 1; }
			int m;
		};

		int m;
		m = x; 
		Y m2;
		return f(m2.f());
	}

	int m; 
	void g(int m) {
		if (m) 
			f(m + 2); 
		else {
			g(m + 2);
		}
	}

	X() { } // constructor of X struct
	void m3() { // empty body, this function immediatly returns
	}

	void main() {
		X a; 
		a.f(2); // calls f method of X struct
	}
};

int main()
{
	X x{};
	x.main();
	return 0;
}