#pragma once

#include <util/digest/city.h>
#include <util/generic/vector.h>

template <class T>
inline ui64 VecCityHash(const yvector<T>& data) {
    return CityHash64(reinterpret_cast<const char*>(~data), sizeof(T) * data.size());
}
