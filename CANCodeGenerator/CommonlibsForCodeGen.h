#pragma once

#include <vector>
#include <string>

template <typename T>
std::vector<T> const & operator += (std::vector<T> & _lhs, std::vector<T> const & _rhs) {
	_lhs.insert(_lhs.end(),
		_rhs.begin(),
		_rhs.end());

	return _lhs;
}

std::vector<std::string> AddIndent(std::vector<std::string> const & _source);


