// StlContainers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <utility>

typedef std::pair<int, std::string> jatekos;

class JatekosPerhapsWoCompare {
public:
	std::string name;
	JatekosPerhapsWoCompare(std::string s) : name(s) {}
	bool operator<(const JatekosPerhapsWoCompare other) const {
		return name < other.name;
	}
	
};

int main()
{
	std::vector<jatekos> jatekosok;

	jatekosok.push_back(jatekos(1, "Buffon"));
	// jatekosok.push_back(std::make_pair(2, "Chiellini")); // jo lenne, de a kesobbiek miatt nem, ahol komparalni is kell
	jatekosok.push_back(jatekos(2, "Chiellini"));
	std::cout << "Elso jatekos: " << jatekosok[0].first << " - " << jatekosok[0].second << std::endl;
	std::cout << "Masodik jatekos: " << std::get<0>(jatekosok[1]) << " - " << std::get<1>(jatekosok[1]) << std::endl;

	

	// vector:
	// a dynamic array, like C array(i.e., capable of random access) with the ability to resize itself
	// automatically when inserting or erasing an object.
	// Inserting an element to the back of the vector at the end takes amortized constant time.
	// Removing the last element takes only constant time, because no resizing happens.
	// Inserting and erasing at the beginning or in the middle is linear in time.
	// A specialization for type bool exists, which optimizes for space by storing bool values as bits.

	// list:
	// 	a doubly linked list; elements are not stored in contiguous memory.
	// Opposite performance from a vector. Slow lookup and access (linear time), but once a position
	// has been found, quick insertion and deletion (constant time).
	std::list<jatekos> psg = { jatekos(7, "Mbappe"), jatekos(9, "Cavani") };
	psg.push_front(jatekos(1, "Buffon"));
	psg.push_back(jatekos(11, "Di Maria"));
	// az alabbi make_pair-rel nem mukodik csak jatekossal, mert jatekos tipus nem osszehasonlithato make_pairrel
	std::list<jatekos>::iterator it = std::find(psg.begin(), psg.end(), jatekos(7, "Mbappe"));
	if (it != psg.end()) {
		psg.insert(it, jatekos(3, "Kimpembe")); //Mbappe ele beszurjuk Kimpembet
	}
	std::cout << "PSG-ben mar van vagy " << psg.size() << " jatekos:" << std::endl;
	for (jatekos j : psg) {
		std::cout << j.first << ": " << j.second << std::endl;
	}

	
	// deque - double-ended queue
	// ugy kell mondani, hogy "deck"

	//Therefore, they provide a functionality similar to vectors, but with efficient
	// insertion and deletion of elements also at the beginning of the sequence, and not
	// only at its end.
	// But, unlike vectors, deques are not guaranteed to store all its elements in 
	// contiguous storage locations: accessing elements in a deque by offsetting a pointer
	// to another element causes undefined behavior.

	// Both vectors and deques provide a very similar interface and can be used for similar
	// purposes, but internally both work in quite different ways : While vectors use a 
	// single array that needs to be occasionally reallocated for growth, the elements of 
	// a deque can be scattered in different chunks of storage, with the container keeping
	// the necessary information internally to provide direct access to any of its elements
	// in constant time and with a uniform sequential interface(through iterators).Therefore,
	// deques are a little more complex internally than vectors, but this allows them to grow
	// more efficiently under certain circumstances, especially with very long sequences, where
	// reallocations become more expensive.
	std::deque<jatekos> manu;
	manu.push_back(jatekos(6, "Pogba"));
	manu.push_back(jatekos(8, "Mata"));
	manu.push_front(jatekos(2, "Lindelof"));
	manu.push_front(jatekos(1, "De Gea"));
	std::cout << "MU-ban mar van vagy " << manu.size() << " jatekos:" << std::endl;
	for (jatekos j : manu) {
		std::cout << j.first << ": " << j.second << std::endl;
	}
	jatekos kapus = manu.front();
	jatekos legnagyobb = manu.back();
	manu.pop_front(); // void-ot ad vissza, csak torol
	manu.pop_back(); // void-ot ad vissza, csak torol
	std::cout << "A kapus " << kapus.second << " volt de mar tavozott" << std::endl;
	std::cout << legnagyobb.second << " szinten tavozott :(" << std::endl;
	std::cout << "MU-ban mar csak " << manu.size() << " jatekos van:" << std::endl;
	for (jatekos j : manu) {
		std::cout << j.first << ": " << j.second << std::endl;
	}

	
	// queue - FIFO, single-end. 
	// Any sequence supporting operations front(), back(), push_back(), and pop_front()
	// can be used to instantiate queue (e.g. list and deque).
	// Iteralni nem lehet - ez egy container adapter:
	// If you need to iterate over a queue then you need something more than a queue. The point
	// of the standard container adapters is to provide a minimal interface. If you need to do
	// iteration as well, why not just use a deque (or list) instead?

	// Asszociativ kontenerek

	// Set: rendezett elemek, egy elem csak egyszer szerepelhet benne
	std::set<jatekos> psgJatekosok;
	std::cout << std::endl;
	psgJatekosok.empty() ? std::cout << "Meg nincs jatekos a halmazban" : std::cout << "Mar vannak jatekosok";
	std::cout << std::endl;
	for (jatekos j : psg) {
		psgJatekosok.insert(j);
	}
	psgJatekosok.empty() ? std::cout << "Meg nincs jatekos a halmazban" : std::cout << "Mar vannak jatekosok";
	std::cout << std::endl;
	for (jatekos j : psgJatekosok) {
		std::cout << j.first << ": " << j.second << std::endl;
	}
	std::cout << std::endl;
	// mi tortenik, ha valakit ketszer rakunk bele?
	psgJatekosok.insert(jatekos(3, "Kimpembe")); // kimpembe egyszer mar benne volt
	psgJatekosok.insert(jatekos(13, "Dani Alves")); // Dani Alves sorrendhelyesen kerul bele
	psgJatekosok.insert(jatekos(5, "Marquinhos")); // Marquinhos is
	for (jatekos j : psgJatekosok) {
		std::cout << j.first << ": " << j.second << std::endl;
	}

	
	// Mi tortenik, ha egy osztalyban nincs compare operator? Sajnos hiba!
	std::set<JatekosPerhapsWoCompare> reallyNowQuestionMark;
	reallyNowQuestionMark.insert(JatekosPerhapsWoCompare("SomeName"));
	reallyNowQuestionMark.insert(JatekosPerhapsWoCompare("BomeName"));
	for (JatekosPerhapsWoCompare j : reallyNowQuestionMark) {
		std::cout << j.name << std::endl;
	}

	std::set<jatekos> manuJatekosok;
	for (jatekos j : manu) {
		manuJatekosok.insert(j);
	}

	// map: kulcs-ertek parok
	// It stores only unique keys and that too in sorted order based on its assigned sorting criteria.
	// As keys are in sorted order therefore searching element in map through key is very fast i.e.it takes logarithmic time.
	// In std::map there will be only one value attached with the every key.
	std::map<jatekos, std::string> jatekosToCsapat;
	jatekosToCsapat.insert(std::make_pair(jatekos(1, "Buffon"), "PSG"));
	jatekosToCsapat.insert(std::make_pair(jatekos(6, "Pogba"), "ManU"));
	jatekosToCsapat[jatekos(7, "Mbappe")] = "PSG";
	std::cout << std::endl;
	if (jatekosToCsapat.find(jatekos(6, "Pogba")) != jatekosToCsapat.end()) {
		std::cout << "Pogba csapata: " << jatekosToCsapat[jatekos(6, "Pogba")] << std::endl;
	}
	std::cout << std::endl;
	std::cout << "A map-en vegig iteralva ezt kapjuk:" << std::endl;
	for (std::pair<jatekos, std::string> pair : jatekosToCsapat) {
		std::cout << pair.first.second << " csapata: " << pair.second << std::endl;
	}


	std::cin.get();
    return 0;
}

