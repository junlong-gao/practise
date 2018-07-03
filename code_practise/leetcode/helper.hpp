#include <bits/stdc++.h>

using namespace std;

template < typename T >
inline std::ostream& operator << (std::ostream& os, const std::vector<T>& v) 
{
    os << "[";
    for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        if (ii != v.begin()) {
           os << ", ";
        }
        os << *ii;
    }
    os << "]";
    return os;
}

template < typename T, typename Q >
inline std::ostream& operator << (std::ostream& os, const std::pair<T, Q>& v) 
{
    os << "(";
    os << v.first << ", " << v.second;
    os << ")";
    return os;
}

template < typename T, typename Q >
inline std::ostream& operator << (std::ostream& os, const std::unordered_map<T, Q>& v) 
{
    os << "[";
    for (auto ii = v.begin(); ii != v.end(); ++ii)
    {
        if (ii != v.begin()) {
           os << ", ";
        }
        os << *ii;
    }
    os << "]";
    return os;
}
