// https://github.com/libgdx/libgdx/blob/master/gdx/src/com/badlogic/gdx/utils/BufferUtils.java

#ifndef LIBGDX_GDX_BUFFER_UTILS_H
#define LIBGDX_GDX_BUFFER_UTILS_H

template<size_t n1, size_t n2> void transform(float * const &src, float * const &m, float * const &dst) {}

template<> inline void transform<4, 4>(float * const &src, float * const &m, float * const &dst) {
    const float x = src[0], y = src[1], z = src[2], w = src[3];
    dst[0] = x * m[ 0] + y * m[ 4] + z * m[ 8] + w * m[12];
    dst[1] = x * m[ 1] + y * m[ 5] + z * m[ 9] + w * m[13];
    dst[2] = x * m[ 2] + y * m[ 6] + z * m[10] + w * m[14];
    dst[3] = x * m[ 3] + y * m[ 7] + z * m[11] + w * m[15];
}

template<> inline void transform<3, 4>(float * const &src, float * const &m, float * const &dst) {
    const float x = src[0], y = src[1], z = src[2];
    dst[0] = x * m[ 0] + y * m[ 4] + z * m[ 8] + m[12];
    dst[1] = x * m[ 1] + y * m[ 5] + z * m[ 9] + m[13];
    dst[2] = x * m[ 2] + y * m[ 6] + z * m[10] + m[14];
}

template<> inline void transform<2, 4>(float * const &src, float * const &m, float * const &dst) {
    const float x = src[0], y = src[1];
    dst[0] = x * m[ 0] + y * m[ 4] + m[12];
    dst[1] = x * m[ 1] + y * m[ 5] + m[13];
}

template<> inline void transform<3, 3>(float * const &src, float * const &m, float * const &dst) {
    const float x = src[0], y = src[1], z = src[2];
    dst[0] = x * m[0] + y * m[3] + z * m[6];
    dst[1] = x * m[1] + y * m[4] + z * m[7];
    dst[2] = x * m[2] + y * m[5] + z * m[8];
}

template<> inline void transform<2, 3>(float * const &src, float * const &m, float * const &dst) {
    const float x = src[0], y = src[1];
    dst[0] = x * m[0] + y * m[3] + m[6];
    dst[1] = x * m[1] + y * m[4] + m[7];
}

template<size_t n1, size_t n2> void transform(float * const &v, int const &stride, int const &count, float * const &m, int offset) {
    for (int i = 0; i < count; i++) {
        transform<n1, n2>(&v[offset], m, &v[offset]);
        offset += stride;
    }
}

template<size_t n1, size_t n2> void transform(float * const &v, int const &stride, unsigned short * const &indices, int const &count, float * const &m, int offset) {
    for (int i = 0; i < count; i++) {
        transform<n1, n2>(&v[offset], m, &v[offset]);
        offset += stride;
    }
}

inline bool compare(float * const &lhs, float * const & rhs, const unsigned int &size, const float &epsilon) {
    for (unsigned int i = 0; i < size; i++)
        if ((*(unsigned int*)&lhs[i] != *(unsigned int*)&rhs[i]) && ((lhs[i] > rhs[i] ? lhs[i] - rhs[i] : rhs[i] - lhs[i]) > epsilon))
            return false;
    return true;
}

long find(float * const &vertex, const unsigned int &size, float * const &vertices, const unsigned int &count, const float &epsilon) {
    for (unsigned int i = 0; i < count; i++)
        if (compare(&vertices[i*size], vertex, size, epsilon))
            return (long)i;
    return -1;
}
inline bool compare(float * const &lhs, float * const & rhs, const unsigned int &size) {
    for (unsigned int i = 0; i < size; i++)
        if ((*(unsigned int*)&lhs[i] != *(unsigned int*)&rhs[i]) && lhs[i] != rhs[i])
            return false;
    return true;
}

long find(float * const &vertex, const unsigned int &size, float * const &vertices, const unsigned int &count) {
    for (unsigned int i = 0; i < count; i++)
        if (compare(&vertices[i*size], vertex, size))
            return (long)i;
    return -1;
}
inline unsigned int calcHash(float * const &vertex, const unsigned int &size) {
    unsigned int result = 0;
    for (unsigned int i = 0; i < size; ++i)
        result += ((*((unsigned int *)&vertex[i])) & 0xffffff80) >> (i & 0x7);
    return result & 0x7fffffff;
}

long find(float * const &vertex, const unsigned int &size, float * const &vertices, unsigned int * const &hashes, const unsigned int &count) {
    const unsigned int hash = calcHash(vertex, size);
    for (unsigned int i = 0; i < count; i++)
        if (hashes[i] == hash && compare(&vertices[i*size], vertex, size))
            return (long)i;
    return -1;
}

#endif //LIBGDX_GDX_BUFFER_UTILS_H
