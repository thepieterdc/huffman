/**
 * Created by Pieter De Clercq.
 *
 * Project: huffman
 */

#include <stdlib.h>
#include "test_datatype_uint256t.h"
#include "test_unit.h"
#include "../src/datatypes/uint256_t.h"

char *test_uint256t_copy() {
	uint256_t *inst = uint256(500);
	assertThat(inst != NULL);
	
	uint256_t *copy = uint256_copy(inst);
	assertThat(copy != NULL);
	
	inst->value[3] = 5;
	
	assertThat(inst->value[3] == 5);
	assertThat(copy->value[3] == 500);
	
	free(inst);
	free(copy);
	return 0;
}

char *test_uint256t_create() {
	uint256_t *inst = uint256(500);
	assertThat(inst != NULL);
	free(inst);
	return 0;
}

char *test_uint256t_equals_is_zero() {
	uint256_t *inst = uint256(500);
	assertThat(inst != NULL);
	
	uint256_t *other = uint256(501);
	assertThat(other != NULL);
	
	uint256_t *anotherone = uint256(500);
	assertThat(anotherone != NULL);
	
	assertThat(uint256_equals(inst, anotherone));
	assertThat(!uint256_equals(inst, other));
	assertThat(!uint256_equals(other, inst));
	assertThat(!uint256_equals(other, anotherone));
	assertThat(uint256_equals(anotherone, inst));
	assertThat(!uint256_equals(anotherone, other));
	
	uint256_t *zero = uint256(0);
	assertThat(uint256_is_zero(zero));
	assertThat(!uint256_is_zero(inst));
	assertThat(!uint256_is_zero(other));
	assertThat(!uint256_is_zero(anotherone));
	
	free(inst);
	free(other);
	free(anotherone);
	free(zero);
	
	return 0;
}

char *test_uint256t_nth_bit() {
	uint256_t *inst = uint256(0xFFFFFFFFFFFFFFFF);
	assertThat(inst != NULL);
	
	for (size_t i = 0; i < 63; ++i) {
		assertThat(uint256_nth_bit(inst, (uint8_t) i) == 1);
	}
	
	free(inst);
	
	return 0;
}

char *test_uint256t_set_lsb_msb() {
	uint256_t *inst = uint256(256);
	assertThat(inst != NULL);
	
	uint256_t *twofiveseven = uint256(257);
	assertThat(twofiveseven != NULL);
	
	assertThat(!uint256_equals(inst, twofiveseven));
	uint256_set_lsb(inst, 1);
	assertThat(uint256_equals(inst, twofiveseven));
	
	uint256_set_msb(inst, 1);
	assertThat(!uint256_equals(inst, twofiveseven));
	
	free(inst);
	free(twofiveseven);
	
	return 0;
}

char *test_uint256t_shift() {
	uint256_t *sixtyfour = uint256(64);
	assertThat(sixtyfour != NULL);
	
	uint256_t *twofivesix = uint256(256);
	assertThat(twofivesix != NULL);
	
	assertThat(!uint256_equals(sixtyfour, twofivesix));
	
	uint256_t *sixtyfour_128 = uint256_shift_left(sixtyfour);
	assertThat(sixtyfour_128 != NULL);
	uint256_t *twofivesix_128 = uint256_shift_right(twofivesix);
	assertThat(twofivesix_128 != NULL);
	
	assertThat(uint256_equals(twofivesix_128, sixtyfour_128));
	
	assertThat(!uint256_equals(twofivesix, sixtyfour));
	uint256_shift_left_assign(sixtyfour);
	uint256_shift_right_assign(twofivesix);
	assertThat(uint256_equals(twofivesix, sixtyfour));
	
	uint256_t *one = uint256(1);
	uint256_t *one_copy = uint256_copy(one);
	
	assertThat(uint256_equals(one, one_copy));
	assertThat(uint256_equals(one, uint256_shift_right_assign(uint256_shift_left_assign(one_copy))));
	
	free(sixtyfour);
	free(sixtyfour_128);
	free(twofivesix);
	free(twofivesix_128);
	free(one);
	free(one_copy);
	
	return 0;
}