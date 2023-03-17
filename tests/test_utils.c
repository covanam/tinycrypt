#include "test_utils.h"

void add_round_key_ngu(uint8_t *s, const unsigned int *k)
{
	s[0] ^= (uint8_t)(k[0] >> 24); s[1] ^= (uint8_t)(k[0] >> 16);
	s[2] ^= (uint8_t)(k[0] >> 8); s[3] ^= (uint8_t)(k[0]);
	s[4] ^= (uint8_t)(k[1] >> 24); s[5] ^= (uint8_t)(k[1] >> 16);
	s[6] ^= (uint8_t)(k[1] >> 8); s[7] ^= (uint8_t)(k[1]);
	s[8] ^= (uint8_t)(k[2] >> 24); s[9] ^= (uint8_t)(k[2] >> 16);
	s[10] ^= (uint8_t)(k[2] >> 8); s[11] ^= (uint8_t)(k[2]);
	s[12] ^= (uint8_t)(k[3] >> 24); s[13] ^= (uint8_t)(k[3] >> 16);
	s[14] ^= (uint8_t)(k[3] >> 8); s[15] ^= (uint8_t)(k[3]);
}

void show_str(const char *label, const uint8_t *s, size_t len)
{
        unsigned int i;

        TC_PRINT("%s = ", label);
        for (i = 0; i < (unsigned int) len; ++i) {
                TC_PRINT("%02x", s[i]);
        }
        TC_PRINT("\n");
}

void fatal(unsigned int testnum, const void *expected, size_t expectedlen,
           const void *computed, size_t computedlen)
{

        TC_ERROR("\tTest #%d Failed!\n", testnum);
        show_str("\t\tExpected", expected, expectedlen);
        show_str("\t\tComputed  ", computed, computedlen);
        TC_PRINT("\n");
}

unsigned int check_result(unsigned int testnum, const void *expected, size_t expectedlen,
                   const void *computed, size_t computedlen)
{
	unsigned int result = TC_PASS;

        if (expectedlen != computedlen) {
                TC_ERROR("The length of the computed buffer (%zu)", computedlen);
                TC_ERROR("does not match the expected length (%zu).", expectedlen);
                result = TC_FAIL;
        } else if (memcmp(computed, expected, computedlen) != 0) {
                fatal(testnum, expected, expectedlen, computed, computedlen);
                result = TC_FAIL;
        }

        return result;
}
