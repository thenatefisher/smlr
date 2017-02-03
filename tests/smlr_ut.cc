/*
@file
*/

#include "gtest.h"
#include "smlr.h"
#include "smlr_internal.h"

void dump_smlr(smlr_t* p_smlr) {
  if (!p_smlr)
    return;
  char buf[p_smlr->buf_bytes + 1];
  memcpy(buf, p_smlr->p_buf, p_smlr->buf_bytes);
  buf[p_smlr->buf_bytes] = '\0';
  printf("\tp_buf:\t\t%s\n", buf);
  printf("\tindex:\t\t%zu\n", p_smlr->index);
  printf("\tinput_bytes:\t%zu\n", p_smlr->input_bytes);
  printf("\tbuf_bytes:\t%zu\n", p_smlr->buf_bytes);
  printf("\tleft_bytes:\t%zu\n", p_smlr->left_bytes);
  printf("\tright_bytes:\t%zu\n", p_smlr->right_bytes);
  printf("\tbuf_base:\t%zu\n", p_smlr->buf_base);
  printf("\talign:\t\t%u\n", p_smlr->align);
}

TEST(SmlrTest, valid_new_delete_test) {
  smlr_t* p_smlr;
  EXPECT_NE(nullptr, p_smlr = smlr_new(20, ALIGN_LEFT));
  if (HasFailure())
    dump_smlr(p_smlr);
  EXPECT_EQ(EXIT_SUCCESS, smlr_delete(p_smlr));
}

TEST(SmlrTest, invalid_ptr_new_delete_test) {
  smlr_t* p_smlr;
  EXPECT_EQ(nullptr, p_smlr = smlr_new(0, ALIGN_LEFT));
  if (HasFailure())
    dump_smlr(p_smlr);
  EXPECT_NE(EXIT_SUCCESS, smlr_delete(p_smlr));
}

TEST(SmlrTest, invalid_alignment_new_delete_test) {
  smlr_t* p_smlr;
  EXPECT_EQ(nullptr, p_smlr = smlr_new(10, (smlr_alignment_t)10));
  if (HasFailure())
    dump_smlr(p_smlr);
  EXPECT_NE(EXIT_SUCCESS, smlr_delete(p_smlr));
}

TEST(SmlrTest, smlr_push) {
  smlr_t* p_smlr;
  uint8_t is_end = 0;
  EXPECT_NE(nullptr, p_smlr = smlr_new(7, ALIGN_LEFT));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '1', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '2', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '3', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '4', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '5', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '6', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '7', &is_end));

  if (HasFailure())
    dump_smlr(p_smlr);
  EXPECT_EQ(EXIT_SUCCESS, smlr_delete(p_smlr));
}

TEST(SmlrTest, smlr_push_RIGHT) {
  smlr_t* p_smlr;
  size_t  buf_sz = 5;
  uint8_t is_end = 0;
  EXPECT_NE(nullptr, p_smlr = smlr_new(buf_sz, ALIGN_RIGHT));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '1', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '2', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '3', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '4', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '5', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '6', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '7', &is_end));
  char truth[] = "67345";

  EXPECT_EQ(0, memcmp(p_smlr->p_buf, truth, buf_sz));

  if (HasFailure())
    dump_smlr(p_smlr);
  EXPECT_EQ(EXIT_SUCCESS, smlr_delete(p_smlr));
}

TEST(SmlrTest, smlr_push_MIDDLE) {
  smlr_t* p_smlr;
  size_t  buf_sz = 5;
  uint8_t is_end = 0;
  EXPECT_NE(nullptr, p_smlr = smlr_new(buf_sz, ALIGN_MIDDLE));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '1', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '2', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '3', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '4', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '5', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '6', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '7', &is_end));
  char truth[] = "16745";

  EXPECT_EQ(0, memcmp(p_smlr->p_buf, truth, buf_sz));

  if (HasFailure())
    dump_smlr(p_smlr);
  EXPECT_EQ(EXIT_SUCCESS, smlr_delete(p_smlr));
}

TEST(SmlrTest, smlr_push_LEFT) {
  smlr_t* p_smlr;
  size_t  buf_sz = 5;
  uint8_t is_end = 0;
  EXPECT_NE(nullptr, p_smlr = smlr_new(buf_sz, ALIGN_LEFT));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '1', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '2', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '3', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '4', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '5', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '6', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, '7', &is_end));
  char truth[] = "12345";

  EXPECT_EQ(0, memcmp(p_smlr->p_buf, truth, buf_sz));
  if (HasFailure())
    dump_smlr(p_smlr);
  EXPECT_EQ(EXIT_SUCCESS, smlr_delete(p_smlr));
}

TEST(SmlrTest, smlr_push_invalid) {
  uint8_t is_end = 0;
  EXPECT_NE(EXIT_SUCCESS, smlr_push(NULL, '1', &is_end));
}

TEST(SmlrTest, smlr_push_eof) {
  smlr_t* p_smlr;
  uint8_t is_end = 0;
  EXPECT_NE(nullptr, p_smlr = smlr_new(5, ALIGN_LEFT));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, EOF, &is_end));
  EXPECT_NE(0, is_end);
  if (HasFailure())
    dump_smlr(p_smlr);
  EXPECT_EQ(EXIT_SUCCESS, smlr_delete(p_smlr));
}

TEST(SmlrTest, smlr_push_not_eof) {
  smlr_t* p_smlr;
  uint8_t is_end = 0;
  EXPECT_NE(nullptr, p_smlr = smlr_new(5, ALIGN_LEFT));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'a', &is_end));
  EXPECT_EQ(0, is_end);
  if (HasFailure())
    dump_smlr(p_smlr);
  EXPECT_EQ(EXIT_SUCCESS, smlr_delete(p_smlr));
}

TEST(SmlrTest, smlr_get_buf_left_nominal_short) {
  smlr_t*      p_smlr;
  const size_t buf_sz = 10;
  uint8_t      is_end = 0;
  char         buf[buf_sz];
  EXPECT_NE(nullptr, p_smlr = smlr_new(buf_sz, ALIGN_LEFT));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'a', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'b', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'c', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'd', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'e', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'f', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_get_buf(p_smlr, buf, buf_sz));

  EXPECT_STREQ(buf, "abcdef");

  if (HasFailure())
    dump_smlr(p_smlr);
  EXPECT_EQ(EXIT_SUCCESS, smlr_delete(p_smlr));
}

TEST(SmlrTest, smlr_internals_5) {
  smlr_t* p_smlr;
  size_t  buf_sz = 5;
  EXPECT_NE(nullptr, p_smlr = smlr_new(buf_sz, ALIGN_MIDDLE));

  EXPECT_EQ(0, p_smlr->index);
  EXPECT_EQ(0, p_smlr->input_bytes);
  EXPECT_EQ(5, p_smlr->buf_bytes);
  EXPECT_EQ(1, p_smlr->left_bytes);
  EXPECT_EQ(1, p_smlr->right_bytes);
  EXPECT_EQ(0, p_smlr->buf_base);

  if (HasFailure())
    dump_smlr(p_smlr);
  EXPECT_EQ(EXIT_SUCCESS, smlr_delete(p_smlr));
}

TEST(SmlrTest, smlr_internals_10) {
  smlr_t* p_smlr;
  size_t  buf_sz = 10;
  EXPECT_NE(nullptr, p_smlr = smlr_new(buf_sz, ALIGN_MIDDLE));

  EXPECT_EQ(0, p_smlr->index);
  EXPECT_EQ(0, p_smlr->input_bytes);
  EXPECT_EQ(10, p_smlr->buf_bytes);
  EXPECT_EQ(4, p_smlr->left_bytes);
  EXPECT_EQ(3, p_smlr->right_bytes);
  EXPECT_EQ(0, p_smlr->buf_base);

  if (HasFailure())
    dump_smlr(p_smlr);
  EXPECT_EQ(EXIT_SUCCESS, smlr_delete(p_smlr));
}

TEST(SmlrTest, smlr_left_alphabet) {
  smlr_t*      p_smlr;
  const size_t buf_sz = 12;
  uint8_t      is_end = 0;
  EXPECT_NE(nullptr, p_smlr = smlr_new(buf_sz, ALIGN_MIDDLE));

  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'a', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'b', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'c', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'd', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'e', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'f', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'g', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'h', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'i', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'j', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'k', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'l', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, EOF, &is_end));

  EXPECT_EQ(12, p_smlr->index);
  EXPECT_EQ(12, p_smlr->input_bytes);
  EXPECT_EQ(12, p_smlr->buf_bytes);
  EXPECT_EQ(5, p_smlr->left_bytes);
  EXPECT_EQ(4, p_smlr->right_bytes);
  EXPECT_EQ(0, p_smlr->buf_base);
  EXPECT_NE(0, is_end);

  char buf_true[buf_sz + 1] = "abcdefghijkl";
  char buf_out[buf_sz + 1];
  EXPECT_EQ(EXIT_SUCCESS, smlr_get_buf(p_smlr, buf_out, buf_sz + 1));
  EXPECT_STREQ(buf_true, buf_out);

  if (HasFailure())
    dump_smlr(p_smlr);
  EXPECT_EQ(EXIT_SUCCESS, smlr_delete(p_smlr));
}

TEST(SmlrTest, smlr_left_alphabet_trunc) {
  smlr_t*      p_smlr;
  const size_t buf_sz = 11;
  uint8_t      is_end = 0;
  EXPECT_NE(nullptr, p_smlr = smlr_new(buf_sz, ALIGN_MIDDLE));

  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'a', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'b', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'c', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'd', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'e', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'f', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'g', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'h', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'i', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'j', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'k', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, 'l', &is_end));
  EXPECT_EQ(EXIT_SUCCESS, smlr_push(p_smlr, EOF, &is_end));

  EXPECT_EQ(5, p_smlr->index);
  EXPECT_EQ(12, p_smlr->input_bytes);
  EXPECT_EQ(11, p_smlr->buf_bytes);
  EXPECT_EQ(4, p_smlr->left_bytes);
  EXPECT_EQ(4, p_smlr->right_bytes);
  EXPECT_EQ(4, p_smlr->buf_base);
  EXPECT_NE(0, is_end);

  char buf_true[buf_sz + 1] = "abcd...ijkl";
  char buf_out[buf_sz + 1];
  EXPECT_EQ(EXIT_SUCCESS, smlr_get_buf(p_smlr, buf_out, buf_sz + 1));
  EXPECT_STREQ(buf_true, buf_out);

  if (HasFailure())
    dump_smlr(p_smlr);
  EXPECT_EQ(EXIT_SUCCESS, smlr_delete(p_smlr));
}
