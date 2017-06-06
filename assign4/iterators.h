#ifndef ITERATORS_H
#define ITERATORS_H

/*
 * This class provides a C++ version of the 'range'
 * function from Python.
 * 
 * It takes
 * 
 */
#include <algorithm>
//return iterator(*this)
//return iterator(*this, true)
template <typename T>
class range {
public:
    class iterator {
        public:
            iterator(T index): m_index(index) {}
            const T&  operator *()                       { return m_pv.at(m_index); }
            iterator& operator ++()                      { ++m_index; return *this; }
            bool      operator !=(const iterator& other) { return m_index != other.m_index; }
        private:
            persistent_vector  m_pv;
   			size_t m_index;
    };

    range(T end):          m_begin(0),    m_end(end) {}
    range(T begin, T end): m_begin(begin),m_end(std::max(begin,end)) {}

    iterator begin() { return iterator(*this); }
    iterator end()   { return iterator(*this, true); }

    private:
        T m_begin;
        T m_end;
};

#endif // defined ITERATORS_H
