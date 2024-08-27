#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <climits> 
   
/* Sets out_codepoint to the current utf8 codepoint in str, and returns the
 * address of the next utf8 codepoint after the current one in str. */
constexpr int8_t* utf8codepoint(const int8_t* str, int32_t* out_codepoint) 
{
    if (0xf0 == (0xf8 & str[0])) {
        /* 4 byte utf8 codepoint */
        *out_codepoint = ((0x07 & str[0]) << 18) | ((0x3f & str[1]) << 12) |
            ((0x3f & str[2]) << 6) | (0x3f & str[3]);
        str += 4;
    }
    else if (0xe0 == (0xf0 & str[0])) {
        /* 3 byte utf8 codepoint */
        *out_codepoint =
            ((0x0f & str[0]) << 12) | ((0x3f & str[1]) << 6) | (0x3f & str[2]);
        str += 3;
    }
    else if (0xc0 == (0xe0 & str[0])) {
        /* 2 byte utf8 codepoint */
        *out_codepoint = ((0x1f & str[0]) << 6) | (0x3f & str[1]);
        str += 2;
    }
    else {
        /* 1 byte utf8 codepoint otherwise */
        *out_codepoint = str[0];
        str += 1;
    }

    return (int8_t*)str;
}


/* Make a codepoint lower case if possible. */
constexpr int32_t utf8lwrcodepoint(int32_t cp) {
    if (((0x0041 <= cp) && (0x005a >= cp)) ||
        ((0x00c0 <= cp) && (0x00d6 >= cp)) ||
        ((0x00d8 <= cp) && (0x00de >= cp)) ||
        ((0x0391 <= cp) && (0x03a1 >= cp)) ||
        ((0x03a3 <= cp) && (0x03ab >= cp)) ||
        ((0x0410 <= cp) && (0x042f >= cp))) {
        cp += 32;
    }
    else if ((0x0400 <= cp) && (0x040f >= cp)) {
        cp += 80;
    }
    else if (((0x0100 <= cp) && (0x012f >= cp)) ||
        ((0x0132 <= cp) && (0x0137 >= cp)) ||
        ((0x014a <= cp) && (0x0177 >= cp)) ||
        ((0x0182 <= cp) && (0x0185 >= cp)) ||
        ((0x01a0 <= cp) && (0x01a5 >= cp)) ||
        ((0x01de <= cp) && (0x01ef >= cp)) ||
        ((0x01f8 <= cp) && (0x021f >= cp)) ||
        ((0x0222 <= cp) && (0x0233 >= cp)) ||
        ((0x0246 <= cp) && (0x024f >= cp)) ||
        ((0x03d8 <= cp) && (0x03ef >= cp)) ||
        ((0x0460 <= cp) && (0x0481 >= cp)) ||
        ((0x048a <= cp) && (0x04ff >= cp))) {
        cp |= 0x1;
    }
    else if (((0x0139 <= cp) && (0x0148 >= cp)) ||
        ((0x0179 <= cp) && (0x017e >= cp)) ||
        ((0x01af <= cp) && (0x01b0 >= cp)) ||
        ((0x01b3 <= cp) && (0x01b6 >= cp)) ||
        ((0x01cd <= cp) && (0x01dc >= cp))) {
        cp += 1;
        cp &= ~0x1;
    }
    else {
        switch (cp) {
        default:
            break;
        case 0x0178:
            cp = 0x00ff;
            break;
        case 0x0243:
            cp = 0x0180;
            break;
        case 0x018e:
            cp = 0x01dd;
            break;
        case 0x023d:
            cp = 0x019a;
            break;
        case 0x0220:
            cp = 0x019e;
            break;
        case 0x01b7:
            cp = 0x0292;
            break;
        case 0x01c4:
            cp = 0x01c6;
            break;
        case 0x01c7:
            cp = 0x01c9;
            break;
        case 0x01ca:
            cp = 0x01cc;
            break;
        case 0x01f1:
            cp = 0x01f3;
            break;
        case 0x01f7:
            cp = 0x01bf;
            break;
        case 0x0187:
            cp = 0x0188;
            break;
        case 0x018b:
            cp = 0x018c;
            break;
        case 0x0191:
            cp = 0x0192;
            break;
        case 0x0198:
            cp = 0x0199;
            break;
        case 0x01a7:
            cp = 0x01a8;
            break;
        case 0x01ac:
            cp = 0x01ad;
            break;
        case 0x01b8:
            cp = 0x01b9;
            break;
        case 0x01bc:
            cp = 0x01bd;
            break;
        case 0x01f4:
            cp = 0x01f5;
            break;
        case 0x023b:
            cp = 0x023c;
            break;
        case 0x0241:
            cp = 0x0242;
            break;
        case 0x03fd:
            cp = 0x037b;
            break;
        case 0x03fe:
            cp = 0x037c;
            break;
        case 0x03ff:
            cp = 0x037d;
            break;
        case 0x037f:
            cp = 0x03f3;
            break;
        case 0x0386:
            cp = 0x03ac;
            break;
        case 0x0388:
            cp = 0x03ad;
            break;
        case 0x0389:
            cp = 0x03ae;
            break;
        case 0x038a:
            cp = 0x03af;
            break;
        case 0x038c:
            cp = 0x03cc;
            break;
        case 0x038e:
            cp = 0x03cd;
            break;
        case 0x038f:
            cp = 0x03ce;
            break;
        case 0x0370:
            cp = 0x0371;
            break;
        case 0x0372:
            cp = 0x0373;
            break;
        case 0x0376:
            cp = 0x0377;
            break;
        case 0x03f4:
            cp = 0x03b8;
            break;
        case 0x03cf:
            cp = 0x03d7;
            break;
        case 0x03f9:
            cp = 0x03f2;
            break;
        case 0x03f7:
            cp = 0x03f8;
            break;
        case 0x03fa:
            cp = 0x03fb;
            break;
        }
    }

    return cp;
}


/* Make a codepoint upper case if possible. */
constexpr int32_t utf8uprcodepoint(int32_t cp) {
    if (((0x0061 <= cp) && (0x007a >= cp)) ||
        ((0x00e0 <= cp) && (0x00f6 >= cp)) ||
        ((0x00f8 <= cp) && (0x00fe >= cp)) ||
        ((0x03b1 <= cp) && (0x03c1 >= cp)) ||
        ((0x03c3 <= cp) && (0x03cb >= cp)) ||
        ((0x0430 <= cp) && (0x044f >= cp))) {
        cp -= 32;
    }
    else if ((0x0450 <= cp) && (0x045f >= cp)) {
        cp -= 80;
    }
    else if (((0x0100 <= cp) && (0x012f >= cp)) ||
        ((0x0132 <= cp) && (0x0137 >= cp)) ||
        ((0x014a <= cp) && (0x0177 >= cp)) ||
        ((0x0182 <= cp) && (0x0185 >= cp)) ||
        ((0x01a0 <= cp) && (0x01a5 >= cp)) ||
        ((0x01de <= cp) && (0x01ef >= cp)) ||
        ((0x01f8 <= cp) && (0x021f >= cp)) ||
        ((0x0222 <= cp) && (0x0233 >= cp)) ||
        ((0x0246 <= cp) && (0x024f >= cp)) ||
        ((0x03d8 <= cp) && (0x03ef >= cp)) ||
        ((0x0460 <= cp) && (0x0481 >= cp)) ||
        ((0x048a <= cp) && (0x04ff >= cp))) {
        cp &= ~0x1;
    }
    else if (((0x0139 <= cp) && (0x0148 >= cp)) ||
        ((0x0179 <= cp) && (0x017e >= cp)) ||
        ((0x01af <= cp) && (0x01b0 >= cp)) ||
        ((0x01b3 <= cp) && (0x01b6 >= cp)) ||
        ((0x01cd <= cp) && (0x01dc >= cp))) {
        cp -= 1;
        cp |= 0x1;
    }
    else {
        switch (cp) {
        default:
            break;
        case 0x00ff:
            cp = 0x0178;
            break;
        case 0x0180:
            cp = 0x0243;
            break;
        case 0x01dd:
            cp = 0x018e;
            break;
        case 0x019a:
            cp = 0x023d;
            break;
        case 0x019e:
            cp = 0x0220;
            break;
        case 0x0292:
            cp = 0x01b7;
            break;
        case 0x01c6:
            cp = 0x01c4;
            break;
        case 0x01c9:
            cp = 0x01c7;
            break;
        case 0x01cc:
            cp = 0x01ca;
            break;
        case 0x01f3:
            cp = 0x01f1;
            break;
        case 0x01bf:
            cp = 0x01f7;
            break;
        case 0x0188:
            cp = 0x0187;
            break;
        case 0x018c:
            cp = 0x018b;
            break;
        case 0x0192:
            cp = 0x0191;
            break;
        case 0x0199:
            cp = 0x0198;
            break;
        case 0x01a8:
            cp = 0x01a7;
            break;
        case 0x01ad:
            cp = 0x01ac;
            break;
        case 0x01b9:
            cp = 0x01b8;
            break;
        case 0x01bd:
            cp = 0x01bc;
            break;
        case 0x01f5:
            cp = 0x01f4;
            break;
        case 0x023c:
            cp = 0x023b;
            break;
        case 0x0242:
            cp = 0x0241;
            break;
        case 0x037b:
            cp = 0x03fd;
            break;
        case 0x037c:
            cp = 0x03fe;
            break;
        case 0x037d:
            cp = 0x03ff;
            break;
        case 0x03f3:
            cp = 0x037f;
            break;
        case 0x03ac:
            cp = 0x0386;
            break;
        case 0x03ad:
            cp = 0x0388;
            break;
        case 0x03ae:
            cp = 0x0389;
            break;
        case 0x03af:
            cp = 0x038a;
            break;
        case 0x03cc:
            cp = 0x038c;
            break;
        case 0x03cd:
            cp = 0x038e;
            break;
        case 0x03ce:
            cp = 0x038f;
            break;
        case 0x0371:
            cp = 0x0370;
            break;
        case 0x0373:
            cp = 0x0372;
            break;
        case 0x0377:
            cp = 0x0376;
            break;
        case 0x03d1:
            cp = 0x0398;
            break;
        case 0x03d7:
            cp = 0x03cf;
            break;
        case 0x03f2:
            cp = 0x03f9;
            break;
        case 0x03f8:
            cp = 0x03f7;
            break;
        case 0x03fb:
            cp = 0x03fa;
            break;
        }
    }

    return cp;
}


/* Returns 1 if the given character is lowercase, or 0 if it is not. */
constexpr int utf8islower(int32_t chr) {
    return chr != utf8uprcodepoint(chr);
}

/* Returns 1 if the given character is uppercase, or 0 if it is not. */
constexpr int utf8isupper(int32_t chr) {
    return chr != utf8lwrcodepoint(chr);
}

/* Return less than 0, 0, greater than 0 if src1 < src2, src1 == src2, src1 >
 * src2 respectively, case insensitive. */
constexpr int utf8casecmp(const int8_t* src1,
    const int8_t* src2) {
    int32_t src1_lwr_cp = 0, src2_lwr_cp = 0, src1_upr_cp = 0,
        src2_upr_cp = 0, src1_orig_cp = 0, src2_orig_cp = 0;

    for (;;) {
        src1 = utf8codepoint(src1, &src1_orig_cp);
        src2 = utf8codepoint(src2, &src2_orig_cp);

        /* lower the srcs if required */
        src1_lwr_cp = utf8lwrcodepoint(src1_orig_cp);
        src2_lwr_cp = utf8lwrcodepoint(src2_orig_cp);

        /* lower the srcs if required */
        src1_upr_cp = utf8uprcodepoint(src1_orig_cp);
        src2_upr_cp = utf8uprcodepoint(src2_orig_cp);

        /* check if the lowered codepoints match */
        if ((0 == src1_orig_cp) && (0 == src2_orig_cp)) {
            return 0;
        }
        else if ((src1_lwr_cp == src2_lwr_cp) || (src1_upr_cp == src2_upr_cp)) {
            continue;
        }

        /* if they don't match, then we return the difference between the characters
         */
        return src1_lwr_cp - src2_lwr_cp;
    }
}


/* Append the utf8 string src onto the utf8 string dst. */
int8_t* utf8cat(int8_t* dst, const int8_t* src) 
{
    int8_t* d = dst;
    /* find the null terminating byte in dst */
    while ('\0' != *d) {
        d++;
    }

    /* overwriting the null terminating byte in dst, append src byte-by-byte */
    while ('\0' != *src) {
        *d++ = *src++;
    }

    /* write out a new null terminating byte into dst */
    *d = '\0';

    return dst;
}


/* Find the first match of the utf8 codepoint chr in the utf8 string src. */
constexpr int8_t* utf8chr(const int8_t* src,
    int32_t chr) {
    int8_t c[5] = { '\0', '\0', '\0', '\0', '\0' };

    if (0 == chr) {
        /* being asked to return position of null terminating byte, so
         * just run s to the end, and return! */
        while ('\0' != *src) {
            src++;
        }
        return (int8_t*)src;
    }
    else if (0 == ((int32_t)0xffffff80 & chr)) {
        /* 1-byte/7-bit ascii
         * (0b0xxxxxxx) */
        c[0] = (int8_t)chr;
    }
    else if (0 == ((int32_t)0xfffff800 & chr)) {
        /* 2-byte/11-bit utf8 code point
         * (0b110xxxxx 0b10xxxxxx) */
        c[0] = (int8_t)(0xc0 | (int8_t)(chr >> 6));
        c[1] = (int8_t)(0x80 | (int8_t)(chr & 0x3f));
    }
    else if (0 == ((int32_t)0xffff0000 & chr)) {
        /* 3-byte/16-bit utf8 code point
         * (0b1110xxxx 0b10xxxxxx 0b10xxxxxx) */
        c[0] = (int8_t)(0xe0 | (int8_t)(chr >> 12));
        c[1] = (int8_t)(0x80 | (int8_t)((chr >> 6) & 0x3f));
        c[2] = (int8_t)(0x80 | (int8_t)(chr & 0x3f));
    }
    else { /* if (0 == ((int)0xffe00000 & chr)) { */
        /* 4-byte/21-bit utf8 code point
         * (0b11110xxx 0b10xxxxxx 0b10xxxxxx 0b10xxxxxx) */
        c[0] = (int8_t)(0xf0 | (int8_t)(chr >> 18));
        c[1] = (int8_t)(0x80 | (int8_t)((chr >> 12) & 0x3f));
        c[2] = (int8_t)(0x80 | (int8_t)((chr >> 6) & 0x3f));
        c[3] = (int8_t)(0x80 | (int8_t)(chr & 0x3f));
    }

    /* we've made c into a 2 utf8 codepoint string, one for the chr we are
     * seeking, another for the null terminating byte. Now use utf8str to
     * search */
    return utf8str(src, c);
}

/* Return less than 0, 0, greater than 0 if src1 < src2,
 * src1 == src2, src1 > src2 respectively. */
constexpr int utf8cmp(const int8_t* src1,
    const int8_t* src2) {
    while (('\0' != *src1) || ('\0' != *src2)) {
        if (*src1 < *src2) {
            return -1;
        }
        else if (*src1 > *src2) {
            return 1;
        }

        src1++;
        src2++;
    }

    /* both utf8 strings matched */
    return 0;
}


/* Copy the utf8 string src onto the memory allocated in dst. */
int8_t* utf8cpy(int8_t* utf8_restrict dst,
    const int8_t* utf8_restrict src) {
    int8_t* d = dst;

    /* overwriting anything previously in dst, write byte-by-byte
     * from src */
    while ('\0' != *src) {
        *d++ = *src++;
    }

    /* append null terminating byte */
    *d = '\0';

    return dst;
}


/* Number of utf8 codepoints in the utf8 string src that consists entirely
 * of utf8 codepoints not from the utf8 string reject. */
constexpr size_t utf8cspn(const int8_t* src,
    const int8_t* reject) {
    size_t chars = 0;

    while ('\0' != *src) {
        const int8_t* r = reject;
        size_t offset = 0;

        while ('\0' != *r) {
            /* checking that if *r is the start of a utf8 codepoint
             * (it is not 0b10xxxxxx) and we have successfully matched
             * a previous character (0 < offset) - we found a match */
            if ((0x80 != (0xc0 & *r)) && (0 < offset)) {
                return chars;
            }
            else {
                if (*r == src[offset]) {
                    /* part of a utf8 codepoint matched, so move our checking
                     * onwards to the next byte */
                    offset++;
                    r++;
                }
                else {
                    /* r could be in the middle of an unmatching utf8 code point,
                     * so we need to march it on to the next character beginning, */

                    do {
                        r++;
                    } while (0x80 == (0xc0 & *r));

                    /* reset offset too as we found a mismatch */
                    offset = 0;
                }
            }
        }

        /* found a match at the end of *r, so didn't get a chance to test it */
        if (0 < offset) {
            return chars;
        }

        /* the current utf8 codepoint in src did not match reject, but src
         * could have been partway through a utf8 codepoint, so we need to
         * march it onto the next utf8 codepoint starting byte */
        do {
            src++;
        } while ((0x80 == (0xc0 & *src)));
        chars++;
    }

    return chars;
}


/* Similar to utf8size, except that only at most n bytes of src are looked and
 * the null terminating byte is excluded. */
constexpr size_t utf8nsize_lazy(const int8_t* str, size_t n) {
    size_t size = 0;
    while (size < n && '\0' != str[size]) {
        size++;
    }
    return size;
}


/* Similar to utf8size, except that the null terminating byte is excluded. */
constexpr size_t utf8size_lazy(const int8_t* str) {
    return utf8nsize_lazy(str, SIZE_MAX);
}


/* Number of bytes in the utf8 string str,
 * including the null terminating byte. */
constexpr size_t utf8size(const int8_t* str) {
    return utf8size_lazy(str) + 1;
}


/* Duplicate the utf8 string src by getting its size, calling alloc_func_ptr to
 * copy over data to a new buffer, and returning that. Or 0 if alloc_func_ptr
 * returned null. */
int8_t* utf8dup_ex(const int8_t* src,
    int8_t* (*alloc_func_ptr)(int8_t*, size_t),
    int8_t* user_data) {
    int8_t* n = nullptr;

    /* figure out how many bytes (including the terminator) we need to copy first
     */
    size_t bytes = utf8size(src);

    if (alloc_func_ptr) {
        n = alloc_func_ptr(user_data, bytes);
    }
    else {
#if !defined(UTF8_NO_STD_MALLOC)
        n = (int8_t*)malloc(bytes);
#else
        return nullptr;
#endif
    }

    if (nullptr == n) {
        /* out of memory so we bail */
        return nullptr;
    }
    else {
        bytes = 0;

        /* copy src byte-by-byte into our new utf8 string */
        while ('\0' != src[bytes]) {
            n[bytes] = src[bytes];
            bytes++;
        }

        /* append null terminating byte */
        n[bytes] = '\0';
        return n;
    }
}


/* Similar to utf8dup, except that at most n bytes of src are copied. If src is
 * longer than n, only n bytes are copied and a null byte is added.
 *
 * Returns a new string if successful, 0 otherwise. */
int8_t* utf8ndup_ex(const int8_t* src, size_t n,
    int8_t* (*alloc_func_ptr)(int8_t*, size_t),
    int8_t* user_data) {
    int8_t* c = nullptr;
    size_t bytes = 0;

    /* Find the end of the string or stop when n is reached */
    while ('\0' != src[bytes] && bytes < n) {
        bytes++;
    }

    /* In case bytes is actually less than n, we need to set it
     * to be used later in the copy byte by byte. */
    n = bytes;

    if (alloc_func_ptr) {
        c = alloc_func_ptr(user_data, bytes + 1);
    }
    else {
#if !defined(UTF8_NO_STD_MALLOC)
        c = (int8_t*)malloc(bytes + 1);
#else
        c = nullptr;
#endif
    }

    if (nullptr == c) {
        /* out of memory so we bail */
        return nullptr;
    }

    bytes = 0;

    /* copy src byte-by-byte into our new utf8 string */
    while ('\0' != src[bytes] && bytes < n) {
        c[bytes] = src[bytes];
        bytes++;
    }

    /* append null terminating byte */
    c[bytes] = '\0';
    return c;
}


/* Duplicate the utf8 string src by getting its size, malloc'ing a new buffer
 * copying over the data, and returning that. Or 0 if malloc failed. */
int8_t* utf8dup(const int8_t* src) {
    return utf8dup_ex(src, nullptr, nullptr);
}


/* Similar to utf8dup, except that at most n bytes of src are copied. If src is
 * longer than n, only n bytes are copied and a null byte is added.
 *
 * Returns a new string if successful, 0 otherwise */
int8_t* utf8ndup(const int8_t* src, size_t n) {
    return utf8ndup_ex(src, n, nullptr, nullptr);
}


/* Similar to utf8len, except that only at most n bytes of src are looked. */
constexpr size_t utf8nlen(const int8_t* str, size_t n) {
    const int8_t* t = str;
    size_t length = 0;

    while ((size_t)(str - t) < n && '\0' != *str) {
        if (0xf0 == (0xf8 & *str)) {
            /* 4-byte utf8 code point (began with 0b11110xxx) */
            str += 4;
        }
        else if (0xe0 == (0xf0 & *str)) {
            /* 3-byte utf8 code point (began with 0b1110xxxx) */
            str += 3;
        }
        else if (0xc0 == (0xe0 & *str)) {
            /* 2-byte utf8 code point (began with 0b110xxxxx) */
            str += 2;
        }
        else { /* if (0x00 == (0x80 & *s)) { */
            /* 1-byte ascii (began with 0b0xxxxxxx) */
            str += 1;
        }

        /* no matter the bytes we marched s forward by, it was
         * only 1 utf8 codepoint */
        length++;
    }

    if ((size_t)(str - t) > n) {
        length--;
    }
    return length;
}


/* Number of utf8 codepoints in the utf8 string str,
 * excluding the null terminating byte. */
constexpr size_t utf8len(const int8_t* str) {
    return utf8nlen(str, SIZE_MAX);
}


/* Return less than 0, 0, greater than 0 if src1 < src2, src1 == src2, src1 >
 * src2 respectively, case insensitive. Checking at most n bytes of each utf8
 * string. */
constexpr int utf8ncasecmp(const int8_t* src1,
    const int8_t* src2, size_t n) {
    int32_t src1_lwr_cp = 0, src2_lwr_cp = 0, src1_upr_cp = 0,
        src2_upr_cp = 0, src1_orig_cp = 0, src2_orig_cp = 0;

    do {
        const int8_t* const s1 = src1;
        const int8_t* const s2 = src2;

        /* first check that we have enough bytes left in n to contain an entire
         * codepoint */
        if (0 == n) {
            return 0;
        }

        if ((1 == n) && ((0xc0 == (0xe0 & *s1)) || (0xc0 == (0xe0 & *s2)))) {
            const int32_t c1 = (0xe0 & *s1);
            const int32_t c2 = (0xe0 & *s2);

            if (c1 != c2) {
                return c1 - c2;
            }
            else {
                return 0;
            }
        }

        if ((2 >= n) && ((0xe0 == (0xf0 & *s1)) || (0xe0 == (0xf0 & *s2)))) {
            const int32_t c1 = (0xf0 & *s1);
            const int32_t c2 = (0xf0 & *s2);

            if (c1 != c2) {
                return c1 - c2;
            }
            else {
                return 0;
            }
        }

        if ((3 >= n) && ((0xf0 == (0xf8 & *s1)) || (0xf0 == (0xf8 & *s2)))) {
            const int32_t c1 = (0xf8 & *s1);
            const int32_t c2 = (0xf8 & *s2);

            if (c1 != c2) {
                return c1 - c2;
            }
            else {
                return 0;
            }
        }

        src1 = utf8codepoint(src1, &src1_orig_cp);
        src2 = utf8codepoint(src2, &src2_orig_cp);
        n -= utf8codepointsize(src1_orig_cp);

        src1_lwr_cp = utf8lwrcodepoint(src1_orig_cp);
        src2_lwr_cp = utf8lwrcodepoint(src2_orig_cp);

        src1_upr_cp = utf8uprcodepoint(src1_orig_cp);
        src2_upr_cp = utf8uprcodepoint(src2_orig_cp);

        /* check if the lowered codepoints match */
        if ((0 == src1_orig_cp) && (0 == src2_orig_cp)) {
            return 0;
        }
        else if ((src1_lwr_cp == src2_lwr_cp) || (src1_upr_cp == src2_upr_cp)) {
            continue;
        }

        /* if they don't match, then we return the difference between the characters
         */
        return src1_lwr_cp - src2_lwr_cp;
    } while (0 < n);

    /* both utf8 strings matched */
    return 0;
}


/* Append the utf8 string src onto the utf8 string dst,
 * writing at most n+1 bytes. Can produce an invalid utf8
 * string if n falls partway through a utf8 codepoint. */
int8_t* utf8ncat(int8_t* dst, const int8_t* src, size_t n) {
    int8_t* d = dst;

    /* find the null terminating byte in dst */
    while ('\0' != *d) {
        d++;
    }

    /* overwriting the null terminating byte in dst, append src byte-by-byte
     * stopping if we run out of space */
    while (('\0' != *src) && (0 != n--)) {
        *d++ = *src++;
    }

    /* write out a new null terminating byte into dst */
    *d = '\0';

    return dst;
}


/* Return less than 0, 0, greater than 0 if src1 < src2,
 * src1 == src2, src1 > src2 respectively. Checking at most n
 * bytes of each utf8 string. */
constexpr int utf8ncmp(const int8_t* src1,
    const int8_t* src2, size_t n) {
    while ((0 != n--) && (('\0' != *src1) || ('\0' != *src2))) {
        if (*src1 < *src2) {
            return -1;
        }
        else if (*src1 > *src2) {
            return 1;
        }

        src1++;
        src2++;
    }

    /* both utf8 strings matched */
    return 0;
}


/* Calculates the size of the next utf8 codepoint in str. */
constexpr size_t utf8codepointcalcsize(const int8_t* str) {
    if (0xf0 == (0xf8 & str[0])) {
        /* 4 byte utf8 codepoint */
        return 4;
    }
    else if (0xe0 == (0xf0 & str[0])) {
        /* 3 byte utf8 codepoint */
        return 3;
    }
    else if (0xc0 == (0xe0 & str[0])) {
        /* 2 byte utf8 codepoint */
        return 2;
    }

    /* 1 byte utf8 codepoint otherwise */
    return 1;
}

/* Copy the utf8 string src onto the memory allocated in dst.
 * Copies at most n bytes. If n falls partway through a utf8
 * codepoint, or if dst doesn't have enough room for a null
 * terminator, the final string will be cut short to preserve
 * utf8 validity. */
int8_t* utf8ncpy(int8_t* dst,const int8_t* src, size_t n) {
    int8_t* d = dst;
    size_t index = 0, check_index = 0;

    if (n == 0) {
        return dst;
    }

    /* overwriting anything previously in dst, write byte-by-byte
     * from src */
    for (index = 0; index < n; index++) {
        d[index] = src[index];
        if ('\0' == src[index]) {
            break;
        }
    }

    for (check_index = index - 1;
        check_index > 0 && 0x80 == (0xc0 & d[check_index]); check_index--) {
        /* just moving the index */
    }

    if (check_index < index &&
        ((index - check_index) < utf8codepointcalcsize(&d[check_index]) ||
            (index - check_index) == n)) {
        index = check_index;
    }

    /* append null terminating byte */
    for (; index < n; index++) {
        d[index] = 0;
    }

    return dst;
}


/* Find the last match of the utf8 codepoint chr in the utf8 string src. */
constexpr int8_t* utf8rchr(const int8_t* src, int chr) {

    int8_t* match = nullptr;
    int8_t c[5] = { '\0', '\0', '\0', '\0', '\0' };

    if (0 == chr) {
        /* being asked to return position of null terminating byte, so
         * just run s to the end, and return! */
        while ('\0' != *src) {
            src++;
        }
        return (int8_t*)src;
    }
    else if (0 == ((int)0xffffff80 & chr)) {
        /* 1-byte/7-bit ascii
         * (0b0xxxxxxx) */
        c[0] = (int8_t)chr;
    }
    else if (0 == ((int)0xfffff800 & chr)) {
        /* 2-byte/11-bit utf8 code point
         * (0b110xxxxx 0b10xxxxxx) */
        c[0] = (int8_t)(0xc0 | (int8_t)(chr >> 6));
        c[1] = (int8_t)(0x80 | (int8_t)(chr & 0x3f));
    }
    else if (0 == ((int)0xffff0000 & chr)) {
        /* 3-byte/16-bit utf8 code point
         * (0b1110xxxx 0b10xxxxxx 0b10xxxxxx) */
        c[0] = (int8_t)(0xe0 | (int8_t)(chr >> 12));
        c[1] = (int8_t)(0x80 | (int8_t)((chr >> 6) & 0x3f));
        c[2] = (int8_t)(0x80 | (int8_t)(chr & 0x3f));
    }
    else { /* if (0 == ((int)0xffe00000 & chr)) { */
        /* 4-byte/21-bit utf8 code point
         * (0b11110xxx 0b10xxxxxx 0b10xxxxxx 0b10xxxxxx) */
        c[0] = (int8_t)(0xf0 | (int8_t)(chr >> 18));
        c[1] = (int8_t)(0x80 | (int8_t)((chr >> 12) & 0x3f));
        c[2] = (int8_t)(0x80 | (int8_t)((chr >> 6) & 0x3f));
        c[3] = (int8_t)(0x80 | (int8_t)(chr & 0x3f));
    }

    /* we've created a 2 utf8 codepoint string in c that is
     * the utf8 character asked for by chr, and a null
     * terminating byte */

    while ('\0' != *src) {
        size_t offset = 0;

        while ((src[offset] == c[offset]) && ('\0' != src[offset])) {
            offset++;
        }

        if ('\0' == c[offset]) {
            /* we found a matching utf8 code point */
            match = (int8_t*)src;
            src += offset;

            if ('\0' == *src) {
                break;
            }
        }
        else {
            src += offset;

            /* need to march s along to next utf8 codepoint start
             * (the next byte that doesn't match 0b10xxxxxx) */
            if ('\0' != *src) {
                do {
                    src++;
                } while (0x80 == (0xc0 & *src));
            }
        }
    }

    /* return the last match we found (or 0 if no match was found) */
    return match;
}


/* Locates the first occurrence in the utf8 string str of any byte in the
 * utf8 string accept, or 0 if no match was found. */
constexpr int8_t* utf8pbrk(const int8_t* str,
    const int8_t* accept) {
    while ('\0' != *str) {
        const int8_t* a = accept;
        size_t offset = 0;

        while ('\0' != *a) {
            /* checking that if *a is the start of a utf8 codepoint
             * (it is not 0b10xxxxxx) and we have successfully matched
             * a previous character (0 < offset) - we found a match */
            if ((0x80 != (0xc0 & *a)) && (0 < offset)) {
                return (int8_t*)str;
            }
            else {
                if (*a == str[offset]) {
                    /* part of a utf8 codepoint matched, so move our checking
                     * onwards to the next byte */
                    offset++;
                    a++;
                }
                else {
                    /* r could be in the middle of an unmatching utf8 code point,
                     * so we need to march it on to the next character beginning, */

                    do {
                        a++;
                    } while (0x80 == (0xc0 & *a));

                    /* reset offset too as we found a mismatch */
                    offset = 0;
                }
            }
        }

        /* we found a match on the last utf8 codepoint */
        if (0 < offset) {
            return (int8_t*)str;
        }

        /* the current utf8 codepoint in src did not match accept, but src
         * could have been partway through a utf8 codepoint, so we need to
         * march it onto the next utf8 codepoint starting byte */
        do {
            str++;
        } while ((0x80 == (0xc0 & *str)));
    }

    return nullptr;
}


/* Number of utf8 codepoints in the utf8 string src that consists entirely
 * of utf8 codepoints from the utf8 string accept. */
constexpr size_t utf8spn(const int8_t* src,
    const int8_t* accept) {
    size_t chars = 0;

    while ('\0' != *src) {
        const int8_t* a = accept;
        size_t offset = 0;

        while ('\0' != *a) {
            /* checking that if *r is the start of a utf8 codepoint
             * (it is not 0b10xxxxxx) and we have successfully matched
             * a previous character (0 < offset) - we found a match */
            if ((0x80 != (0xc0 & *a)) && (0 < offset)) {
                /* found a match, so increment the number of utf8 codepoints
                 * that have matched and stop checking whether any other utf8
                 * codepoints in a match */
                chars++;
                src += offset;
                offset = 0;
                break;
            }
            else {
                if (*a == src[offset]) {
                    offset++;
                    a++;
                }
                else {
                    /* a could be in the middle of an unmatching utf8 codepoint,
                     * so we need to march it on to the next character beginning, */
                    do {
                        a++;
                    } while (0x80 == (0xc0 & *a));

                    /* reset offset too as we found a mismatch */
                    offset = 0;
                }
            }
        }

        /* found a match at the end of *a, so didn't get a chance to test it */
        if (0 < offset) {
            chars++;
            src += offset;
            continue;
        }

        /* if a got to its terminating null byte, then we didn't find a match.
         * Return the current number of matched utf8 codepoints */
        if ('\0' == *a) {
            return chars;
        }
    }

    return chars;
}


/* The position of the utf8 string needle in the utf8 string haystack. */
constexpr int8_t* utf8str(const int8_t* haystack,
    const int8_t* needle) {
    int32_t throwaway_codepoint = 0;

    /* if needle has no utf8 codepoints before the null terminating
     * byte then return haystack */
    if ('\0' == *needle) {
        return (int8_t*)haystack;
    }

    while ('\0' != *haystack) {
        const int8_t* maybeMatch = haystack;
        const int8_t* n = needle;

        while (*haystack == *n && (*haystack != '\0' && *n != '\0')) {
            n++;
            haystack++;
        }

        if ('\0' == *n) {
            /* we found the whole utf8 string for needle in haystack at
             * maybeMatch, so return it */
            return (int8_t*)maybeMatch;
        }
        else {
            /* h could be in the middle of an unmatching utf8 codepoint,
             * so we need to march it on to the next character beginning
             * starting from the current character */
            haystack = utf8codepoint(maybeMatch, &throwaway_codepoint);
        }
    }

    /* no match */
    return nullptr;
}


/* The position of the utf8 string needle in the utf8 string haystack, case
 * insensitive. */
constexpr int8_t* utf8casestr(const int8_t* haystack,
    const int8_t* needle) {
    /* if needle has no utf8 codepoints before the null terminating
     * byte then return haystack */
    if ('\0' == *needle) {
        return (int8_t*)haystack;
    }

    for (;;) {
        const int8_t* maybeMatch = haystack;
        const int8_t* n = needle;
        int32_t h_cp = 0, n_cp = 0;

        /* Get the next code point and track it */
        const int8_t* nextH = haystack = utf8codepoint(haystack, &h_cp);
        n = utf8codepoint(n, &n_cp);

        while ((0 != h_cp) && (0 != n_cp)) {
            h_cp = utf8lwrcodepoint(h_cp);
            n_cp = utf8lwrcodepoint(n_cp);

            /* if we find a mismatch, bail out! */
            if (h_cp != n_cp) {
                break;
            }

            haystack = utf8codepoint(haystack, &h_cp);
            n = utf8codepoint(n, &n_cp);
        }

        if (0 == n_cp) {
            /* we found the whole utf8 string for needle in haystack at
             * maybeMatch, so return it */
            return (int8_t*)maybeMatch;
        }

        if (0 == h_cp) {
            /* no match */
            return nullptr;
        }

        /* Roll back to the next code point in the haystack to test */
        haystack = nextH;
    }
}


/* Similar to utf8valid, except that only at most n bytes of src are looked. */
constexpr int8_t* utf8nvalid(const int8_t* str,
    size_t n) {
    const int8_t* t = str;
    size_t consumed = 0;

    while ((void)(consumed = (size_t)(str - t)), consumed < n && '\0' != *str) {
        const size_t remaining = n - consumed;

        if (0xf0 == (0xf8 & *str)) {
            /* ensure that there's 4 bytes or more remaining */
            if (remaining < 4) {
                return (int8_t*)str;
            }

            /* ensure each of the 3 following bytes in this 4-byte
             * utf8 codepoint began with 0b10xxxxxx */
            if ((0x80 != (0xc0 & str[1])) || (0x80 != (0xc0 & str[2])) ||
                (0x80 != (0xc0 & str[3]))) {
                return (int8_t*)str;
            }

            /* ensure that our utf8 codepoint ended after 4 bytes */
            if ((remaining != 4) && (0x80 == (0xc0 & str[4]))) {
                return (int8_t*)str;
            }

            /* ensure that the top 5 bits of this 4-byte utf8
             * codepoint were not 0, as then we could have used
             * one of the smaller encodings */
            if ((0 == (0x07 & str[0])) && (0 == (0x30 & str[1]))) {
                return (int8_t*)str;
            }

            /* 4-byte utf8 code point (began with 0b11110xxx) */
            str += 4;
        }
        else if (0xe0 == (0xf0 & *str)) {
            /* ensure that there's 3 bytes or more remaining */
            if (remaining < 3) {
                return (int8_t*)str;
            }

            /* ensure each of the 2 following bytes in this 3-byte
             * utf8 codepoint began with 0b10xxxxxx */
            if ((0x80 != (0xc0 & str[1])) || (0x80 != (0xc0 & str[2]))) {
                return (int8_t*)str;
            }

            /* ensure that our utf8 codepoint ended after 3 bytes */
            if ((remaining != 3) && (0x80 == (0xc0 & str[3]))) {
                return (int8_t*)str;
            }

            /* ensure that the top 5 bits of this 3-byte utf8
             * codepoint were not 0, as then we could have used
             * one of the smaller encodings */
            if ((0 == (0x0f & str[0])) && (0 == (0x20 & str[1]))) {
                return (int8_t*)str;
            }

            /* 3-byte utf8 code point (began with 0b1110xxxx) */
            str += 3;
        }
        else if (0xc0 == (0xe0 & *str)) {
            /* ensure that there's 2 bytes or more remaining */
            if (remaining < 2) {
                return (int8_t*)str;
            }

            /* ensure the 1 following byte in this 2-byte
             * utf8 codepoint began with 0b10xxxxxx */
            if (0x80 != (0xc0 & str[1])) {
                return (int8_t*)str;
            }

            /* ensure that our utf8 codepoint ended after 2 bytes */
            if ((remaining != 2) && (0x80 == (0xc0 & str[2]))) {
                return (int8_t*)str;
            }

            /* ensure that the top 4 bits of this 2-byte utf8
             * codepoint were not 0, as then we could have used
             * one of the smaller encodings */
            if (0 == (0x1e & str[0])) {
                return (int8_t*)str;
            }

            /* 2-byte utf8 code point (began with 0b110xxxxx) */
            str += 2;
        }
        else if (0x00 == (0x80 & *str)) {
            /* 1-byte ascii (began with 0b0xxxxxxx) */
            str += 1;
        }
        else {
            /* we have an invalid 0b1xxxxxxx utf8 code point entry */
            return (int8_t*)str;
        }
    }

    return nullptr;
}


/* Return 0 on success, or the position of the invalid
 * utf8 codepoint on failure. */
constexpr int8_t* utf8valid(const int8_t* str) {
    return utf8nvalid(str, SIZE_MAX);
}


/* Write a codepoint to the given string, and return the address to the next
 * place after the written codepoint. Pass how many bytes left in the buffer to
 * n. If there is not enough space for the codepoint, this function returns
 * null. */
int8_t* utf8catcodepoint(int8_t* str, int32_t chr, size_t n) {
    if (0 == ((int32_t)0xffffff80 & chr)) {
        /* 1-byte/7-bit ascii
         * (0b0xxxxxxx) */
        if (n < 1) {
            return nullptr;
        }
        str[0] = (int8_t)chr;
        str += 1;
    }
    else if (0 == ((int32_t)0xfffff800 & chr)) {
        /* 2-byte/11-bit utf8 code point
         * (0b110xxxxx 0b10xxxxxx) */
        if (n < 2) {
            return nullptr;
        }
        str[0] = (int8_t)(0xc0 | (int8_t)((chr >> 6) & 0x1f));
        str[1] = (int8_t)(0x80 | (int8_t)(chr & 0x3f));
        str += 2;
    }
    else if (0 == ((int32_t)0xffff0000 & chr)) {
        /* 3-byte/16-bit utf8 code point
         * (0b1110xxxx 0b10xxxxxx 0b10xxxxxx) */
        if (n < 3) {
            return nullptr;
        }
        str[0] = (int8_t)(0xe0 | (int8_t)((chr >> 12) & 0x0f));
        str[1] = (int8_t)(0x80 | (int8_t)((chr >> 6) & 0x3f));
        str[2] = (int8_t)(0x80 | (int8_t)(chr & 0x3f));
        str += 3;
    }
    else { /* if (0 == ((int)0xffe00000 & chr)) { */
        /* 4-byte/21-bit utf8 code point
         * (0b11110xxx 0b10xxxxxx 0b10xxxxxx 0b10xxxxxx) */
        if (n < 4) {
            return nullptr;
        }
        str[0] = (int8_t)(0xf0 | (int8_t)((chr >> 18) & 0x07));
        str[1] = (int8_t)(0x80 | (int8_t)((chr >> 12) & 0x3f));
        str[2] = (int8_t)(0x80 | (int8_t)((chr >> 6) & 0x3f));
        str[3] = (int8_t)(0x80 | (int8_t)(chr & 0x3f));
        str += 4;
    }

    return str;
}


/* Given a null-terminated string, makes the string valid by replacing invalid
 * codepoints with a 1-byte replacement. Returns 0 on success. */
int utf8makevalid(int8_t* str, const int32_t replacement) {
    int8_t* read = str;
    int8_t* write = read;
    const int8_t r = (int8_t)replacement;
    int32_t codepoint = 0;

    if (replacement > 0x7f) {
        return -1;
    }

    while ('\0' != *read) {
        if (0xf0 == (0xf8 & *read)) {
            /* ensure each of the 3 following bytes in this 4-byte
             * utf8 codepoint began with 0b10xxxxxx */
            if ((0x80 != (0xc0 & read[1])) || (0x80 != (0xc0 & read[2])) ||
                (0x80 != (0xc0 & read[3]))) {
                *write++ = r;
                read++;
                continue;
            }

            /* 4-byte utf8 code point (began with 0b11110xxx) */
            read = utf8codepoint(read, &codepoint);
            write = utf8catcodepoint(write, codepoint, 4);
        }
        else if (0xe0 == (0xf0 & *read)) {
            /* ensure each of the 2 following bytes in this 3-byte
             * utf8 codepoint began with 0b10xxxxxx */
            if ((0x80 != (0xc0 & read[1])) || (0x80 != (0xc0 & read[2]))) {
                *write++ = r;
                read++;
                continue;
            }

            /* 3-byte utf8 code point (began with 0b1110xxxx) */
            read = utf8codepoint(read, &codepoint);
            write = utf8catcodepoint(write, codepoint, 3);
        }
        else if (0xc0 == (0xe0 & *read)) {
            /* ensure the 1 following byte in this 2-byte
             * utf8 codepoint began with 0b10xxxxxx */
            if (0x80 != (0xc0 & read[1])) {
                *write++ = r;
                read++;
                continue;
            }

            /* 2-byte utf8 code point (began with 0b110xxxxx) */
            read = utf8codepoint(read, &codepoint);
            write = utf8catcodepoint(write, codepoint, 2);
        }
        else if (0x00 == (0x80 & *read)) {
            /* 1-byte ascii (began with 0b0xxxxxxx) */
            read = utf8codepoint(read, &codepoint);
            write = utf8catcodepoint(write, codepoint, 1);
        }
        else {
            /* if we got here then we've got a dangling continuation (0b10xxxxxx) */
            *write++ = r;
            read++;
            continue;
        }
    }

    *write = '\0';

    return 0;
}


/* Returns the size of the given codepoint in bytes. */
constexpr size_t utf8codepointsize(int32_t chr) {
    if (0 == ((int32_t)0xffffff80 & chr)) {
        return 1;
    }
    else if (0 == ((int32_t)0xfffff800 & chr)) {
        return 2;
    }
    else if (0 == ((int32_t)0xffff0000 & chr)) {
        return 3;
    }
    else { /* if (0 == ((int)0xffe00000 & chr)) { */
        return 4;
    }
}


/* Transform the given string into all lowercase codepoints. */
void utf8lwr(int8_t* str) {
    int32_t cp = 0;
    int8_t* pn = utf8codepoint(str, &cp);

    while (cp != 0) {
        const int32_t lwr_cp = utf8lwrcodepoint(cp);
        const size_t size = utf8codepointsize(lwr_cp);

        if (lwr_cp != cp) {
            utf8catcodepoint(str, lwr_cp, size);
        }

        str = pn;
        pn = utf8codepoint(str, &cp);
    }
}


/* Transform the given string into all uppercase codepoints. */
void utf8upr(int8_t* utf8_restrict str) {
    int32_t cp = 0;
    int8_t* pn = utf8codepoint(str, &cp);

    while (cp != 0) {
        const int32_t lwr_cp = utf8uprcodepoint(cp);
        const size_t size = utf8codepointsize(lwr_cp);

        if (lwr_cp != cp) {
            utf8catcodepoint(str, lwr_cp, size);
        }

        str = pn;
        pn = utf8codepoint(str, &cp);
    }
}


/* Sets out_codepoint to the current utf8 codepoint in str, and returns the
 * address of the previous utf8 codepoint before the current one in str. */
constexpr int8_t*
utf8rcodepoint(const int8_t* str,
    int32_t* out_codepoint) {
    const int8_t* s = (const int8_t*)str;

    if (0xf0 == (0xf8 & s[0])) {
        /* 4 byte utf8 codepoint */
        *out_codepoint = ((0x07 & s[0]) << 18) | ((0x3f & s[1]) << 12) |
            ((0x3f & s[2]) << 6) | (0x3f & s[3]);
    }
    else if (0xe0 == (0xf0 & s[0])) {
        /* 3 byte utf8 codepoint */
        *out_codepoint =
            ((0x0f & s[0]) << 12) | ((0x3f & s[1]) << 6) | (0x3f & s[2]);
    }
    else if (0xc0 == (0xe0 & s[0])) {
        /* 2 byte utf8 codepoint */
        *out_codepoint = ((0x1f & s[0]) << 6) | (0x3f & s[1]);
    }
    else {
        /* 1 byte utf8 codepoint otherwise */
        *out_codepoint = s[0];
    }

    do {
        s--;
    } while ((0 != (0x80 & s[0])) && (0x80 == (0xc0 & s[0])));

    return (int8_t*)s;
}
