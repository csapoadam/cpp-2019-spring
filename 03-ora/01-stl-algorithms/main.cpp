// StlAlgorithms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cmath>
#include <iterator>
#include <deque>
#include <string>
#include <cctype>

#include "tools.h"

bool isEven(int x) {
	return x % 2 == 0;
}

int fibonacciGenerator() {
	static int numTimesCalled = 0;
	static int penultimate = 1;
	static int ultimate = 1;
	if (numTimesCalled < 3) numTimesCalled++;
	if (numTimesCalled == 1 || numTimesCalled == 2) {
		return 1;
	}
	else {
		int retval = ultimate + penultimate;
		penultimate = ultimate;
		ultimate = retval;
		return retval;
	}
}

int main()
{
	// Eloszor is: lambda fuggvenyek
	// Fuggvenyek nev nelkul is megadhatoak. Pl.:
	std::cout << "isEven(2) = " << isEven(2) << std::endl;
	std::cout << "isEven(3) = " << isEven(3) << std::endl;
	// a lambda fuggvenyt megadjuk es meg is hivjuk
	std::cout << "lambda isEven(2) = " << [](int x) { return x % 2 == 0; }(2) << std::endl;
	std::cout << "lambda isEven(3) = " << [](int x) { return x % 2 == 0; }(3) << std::endl;

	// Masodszor: fuggvenyek megadhatoak structkent vagy osztalykent is, aminek van () operatora!
	// Az ilyen osztalyokat Functoroknak hivjak ( fanktor, haha :) )
	struct IsOdd {
		int number;
		IsOdd(int num) : number(num) {}
		bool operator()() {
			return number % 2 == 1;
		}
	};

	std::cout << "struct isOdd(2) = " << IsOdd(2)() << std::endl;
	std::cout << "struct isOdd(3) = " << IsOdd(3)() << std::endl;
	
	class IsNDivisibleByX {
	public:
		bool operator()(int n, int x) {
			return n % x == 0;
		}
	};


	
	std::cout << "(6 divisible by 3) = " << IsNDivisibleByX()(6, 3) << std::endl;
	std::cout << "(6 divisible by 4) = " << IsNDivisibleByX()(6, 4) << std::endl;
	
	/////////////////////////////////////////////////
	// ******************************************* //
	/////////////////////////////////////////////////

	// vektorokra meg igazabol barmire ami iteralhato leteznek az:
	// std::any_of
	// std::none_of
	// std::all_of fuggvenyek

	std::vector<int> intvec = { 2, 3, 4, 6, 8, 12 };
	// ld. tools.h-ban levo operator overload!
	std::cout << "Let us consider this vector v: " << intvec << std::endl;
	if (std::all_of(intvec.begin(),
		intvec.end(), 
		[](int x) {return x % 2 == 0; })) {
			std::cout << "All elements of v are even!" << std::endl;
	}
	else {
		std::cout << "Not all elements of v are even!" << std::endl;
	}

	if (std::all_of(intvec.begin() + 2, intvec.end(), [](int x) {return x % 2 == 0; })) {
		std::cout << "All elements of v after the second one are even!" << std::endl;
	}
	else {
		std::cout << "Not all elements of v after the second one are even!" << std::endl;
	}

	

	if (std::any_of(intvec.begin(), intvec.end(), [](int x) {return x % 2 == 0; })) {
		std::cout << "At least one element of v is even!" << std::endl;
	}
	else {
		std::cout << "No element of v is even!" << std::endl;
	}

	if (std::any_of(intvec.begin(),
		intvec.end(),
		[](int x) {return x > 10; })) {
			std::cout << "At least one element of v is greater than 10!" << std::endl;
	}

	struct IsDivisibleByX {
		int divisor;
		IsDivisibleByX(int whatIsX) : divisor(whatIsX) {}
		bool operator()(int whatIsNumber) {
			return whatIsNumber % divisor == 0;
		}
	};

	if (std::none_of(intvec.begin(),
		intvec.end(), 
		IsDivisibleByX(10))) {
			std::cout << "No element of v is divisible by 10!" << std::endl;
	}
	if (std::any_of(intvec.begin(), 
		intvec.end(),
		IsDivisibleByX(3))) {
			std::cout << "At least one element of v is divisible by 3!" << std::endl;
	}

	

	//////////////////////////////////////
	//// **************************** ////
	std::cout << "Print vector using for_each:" << std::endl;
	// lambda fuggvenynek adhatunk nevet is. A lambda fuggveny egy klasszikus rvalue...
	auto printNumbers = [](const int& n) { std::cout << " " << n; };
	std::for_each(intvec.begin(), intvec.end(), printNumbers);
	std::cout << std::endl;

	

	//... std::for_each segitsegevel erteket is akkumulalhatunk. Ehhez kell egy functor is.
	// std::for_each visszateresi erteke ilyenkor std::move(f), ahol f a functor
	// ez azt jelenti, hogy masolas nelkul (mozgatassal) megkapjuk a functor allapotat!
	struct Sum {
		int sum;
		Sum() : sum{ 0 } { }
		void operator()(int n) { sum += n; }
	};
	// ami meno, hogy igy a vektor elemei is modosithatoak (nem a masolatukon dolgozunk)
	std::for_each(intvec.begin(),
		intvec.end(),[](int &n) { n++; });

	// calls Sum::operator() for each number
	Sum s = std::for_each(
		intvec.begin(),
		intvec.end(),
		Sum());
	std::cout << "sum of all values incremented by 1: " << 
		s.sum << std::endl;
	std::cout << "after: " << std::endl;
	std::for_each(intvec.begin(), intvec.end(), printNumbers);
	std::cout << std::endl;

	

	// ilyen esetekben persze az std::accumulate egyszerubb lehet:
	// (ehhez kell a numeric header)
	int sum = std::accumulate(
		intvec.begin(),
		intvec.end(),
		0);
	std::cout << "sum calculated using accumulate is: " << sum << std::endl;
	// a harmadik argumentum itt a kezdo ertek.
	// Ha akarjuk, negyedikkent sajat binaris operatort is megadhatunk...
	// pow() fv. cmath headerben van
	// Vegyuk eszre, hogy a binaris operator elso argumentuma a korabbrol akkumulalt ertek
	int sum_of_squares = std::accumulate(
		intvec.begin(),
		intvec.end(),
		0,
		[](int a, int b) {return a + pow(b, 2); });
	std::cout << "sum of squares = " << sum_of_squares << std::endl;

	//////////////////////////////////////////////
	// **************************************** //
	//////////////////////////////////////////////
	// masolni az std::copy es std::copy_if-fel lehet:

	std::vector<int> intvec2;
	std::vector<int> intvec3;
	std::deque<int> intvec4; // kell include<deque>

	std::copy(
		intvec.begin(),
		intvec.end(),
		std::back_inserter(intvec2));
	std::copy_if(
		intvec.begin(),
		intvec.end(),
		std::back_inserter(intvec3),
		[](int x) { return x % 2 == 1; });
	std::copy(intvec.begin(),
		intvec.end(),
		std::front_inserter(intvec4)); // kell include iterator
	std::cout << "original: " << intvec << std::endl;
	std::cout << "copy: " << intvec2 << std::endl;
	std::cout << "copy if odd: " << intvec3 << std::endl;
	std::cout << "copied w/ front_inserter: " << intvec4 << std::endl;
	
	//////////////////////////////////////////////
	// **************************************** //
	//////////////////////////////////////////////
	// kontenerek feltolthetoek un. generatorral

	// generator barmilyen fv. ami visszaadja a megfelelo tipust es tobbszor meghivhato
	// ilyen a fenti fibonacciGenerator is!
	std::vector<int> fibonaccis(10);
	std::generate(fibonaccis.begin(),
		fibonaccis.end(),
		fibonacciGenerator);
	std::cout << "first 10 fibonacci numbers: " << fibonaccis << std::endl;
	
	//////////////////////////////////////////////
	// **************************************** //
	//////////////////////////////////////////////
	// erdemes ismerni az un. erase-remove idiomat
	// csak az erase is jo, viszont minden egyes torlesnel shiftelni fogja az ertekeket
	// ami a vektor (vagy hasonlo struktura) atmeretezesevel jar
	// -> ez nem hatekony!
	// a remove ezzel szemben iteratorokat hasznal
	// (tehat nem erdekli, hogy folytonosan
	// vannak-e az elemek a memoriaban), és mindent
	// ami torlendo az iteratorok vegere pakolja
	// a vegen eleg csak a kontener veget torolni!

	std::string stringwithspaces(" Ez egy nagyon hosszu  szokozokkel\tellatott sztring");
	std::cout << "Az eredeti sztring: " << std::endl << stringwithspaces << std::endl;
	stringwithspaces.erase(std::remove(
		stringwithspaces.begin(),
		stringwithspaces.end(),
		' '),
	stringwithspaces.end());
	std::cout << "Szokozok torlese utan: " << std::endl << stringwithspaces << std::endl;

	stringwithspaces.erase(
		std::remove_if(
			stringwithspaces.begin(),
			stringwithspaces.end(),
			[](unsigned char x) {return std::isspace(x); }),
		stringwithspaces.end());
	std::cout << "Minden whitespace torlese utan: " << std::endl << stringwithspaces << std::endl;

	std::cin.get();

    return 0;
}

