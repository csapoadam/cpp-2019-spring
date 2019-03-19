#pragma once

#include <iostream>
#include <vector>
#include <deque>

template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
	if (!v.empty()) {
		out << '[';
		out << v[0];
		for (auto it = v.begin() + 1; it != v.end(); ++it) {
			out << ", " << *it;
		}
		out << "]";
	}
	return out;
}

template <typename T>
std::ostream& operator<< (std::ostream& out, const std::deque<T>& v) {
	if (!v.empty()) {
		out << '[';
		out << v[0];
		for (auto it = v.begin() + 1; it != v.end(); ++it) {
			out << ", " << *it;
		}
		out << "]";
	}
	return out;
}