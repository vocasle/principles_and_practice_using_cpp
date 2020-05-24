#include <iostream>
#include <string>

class B1
{
public:
	void virtual vf() { std::cout << "B1::vf()\n"; }
	void f() { std::cout << "B1::f()\n"; }
	void virtual pvf() = 0;
};

class D1 : public B1
{
public:
	void vf() { std::cout << "D1::vf()\n"; }
	void f() { std::cout << "D1::f()\n"; }
};

class D2 : public D1
{
public:
	void pvf() { std::cout << "D2::pvf()\n"; }
};

class B2
{
public:
	void virtual pvf() = 0;
};

class D21 : public B2
{
public:
	void pvf() { std::cout << str << std::endl; }
private:
	std::string str = "Hello from D21\n";
};

class D22 : public B2
{
public:
	void pvf() { std::cout << num << std::endl; }
private:
	int num = 1994;
};

int main()
{
	// auto b1 = B1(); // will fail, because B1 becomes abstract class due to void pfv() method
	// b1.vf();
	// b1.f();

	// auto d1 = D1(); // will fail, because D1 is abstract class due to void pfv() method
	// d1.vf();
	// d1.f();

	// B1& rd1 = d1;
	// rd1.vf();
	// rd1.f();
	auto d2 = D2();
	d2.f();
	d2.vf();
	d2.pvf();

	auto d22 = D22();
	auto d21 = D21();
	B2& rd22 = d22;
	B2& rd21 = d21;
	d21.pvf();
	d22.pvf();
}