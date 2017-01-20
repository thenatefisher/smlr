/*
@file
*/

#include "gtest.h"
#include "smlr.h"
#include "smlr_internal.h"

TEST(SmlrTest, valid_new_delete_test) {
  smlr_t *p_smlr;
  EXPECT_NE(nullptr, p_smlr = smlr_new(20, ALIGN_LEFT));
  EXPECT_EQ(EXIT_SUCCESS, smlr_delete(p_smlr));
}

TEST(SmlrTest, invalid_ptr_new_delete_test) {
  smlr_t *p_smlr;
  EXPECT_EQ(nullptr, p_smlr = smlr_new(0, ALIGN_LEFT));
  EXPECT_NE(EXIT_SUCCESS, smlr_delete(p_smlr));
}

TEST(SmlrTest, invalid_alignment_new_delete_test) {
  smlr_t *p_smlr;
  EXPECT_EQ(nullptr, p_smlr = smlr_new(10, (smlr_alignment_t)10));
  EXPECT_NE(EXIT_SUCCESS, smlr_delete(p_smlr));
}

TEST(SmlrTest, smlr_push) {
  smlr_t *p_smlr;
  size_t prefix_sz;
  EXPECT_NE(nullptr, p_smlr = smlr_new(7, ALIGN_LEFT));

  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '1'));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '2'));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '3'));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '4'));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '5'));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '6'));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '7'));

  EXPECT_EQ(EXIT_SUCCESS, smlr_delete(p_smlr));
}

TEST(SmlrTest, smlr_push_wrap) {
  smlr_t *p_smlr;
  size_t prefix_sz;
  EXPECT_NE(nullptr, p_smlr = smlr_new(5, ALIGN_LEFT));

  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '1'));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '2'));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '3'));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '4'));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '5'));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '6'));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '7'));

  EXPECT_EQ(EXIT_SUCCESS, smlr_delete(p_smlr));
}

TEST(SmlrTest, smlr_push_invalid) {
  smlr_t *p_smlr;
  size_t prefix_sz;
  EXPECT_NE(nullptr, p_smlr = smlr_new(5, ALIGN_LEFT));
  EXPECT_NE(EXIT_SUCCESS, smlr_push(NULL, '1'));
  EXPECT_EQ(EXIT_SUCCESS, smlr_delete(p_smlr));
}

TEST(SmlrTest, smlr_get_buf_left_nominal_short) {
  smlr_t *p_smlr;
  const size_t buf_sz = 10;
  char buf[buf_sz];

  EXPECT_NE(nullptr, p_smlr = smlr_new(buf_sz, ALIGN_LEFT));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'a'));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'b'));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'c'));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'd'));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'e'));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'f'));
  EXPECT_EQ(EXIT_SUCCESS, smlr_get_buf(p_smlr, buf, buf_sz));

  EXPECT_EQ(0, strcmp(buf, "abcdef"));

  EXPECT_EQ(EXIT_SUCCESS, smlr_delete(p_smlr));
}
