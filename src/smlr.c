/*
 * @file
 * See header file for documentation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "smlr.h"
#include "smlr_internal.h"
#include "stddef.h"

#define NULLTERM_LEN 1U
#define ELLIPSIS_LEN 3U
const char ellipsis_str[ELLIPSIS_LEN + 1] = "...";

smlr_t* smlr_new(size_t output_size, smlr_alignment_t alignment) {

  // check input preconditions
  if (!output_size)
    return NULL;

  smlr_t* smlr  = NULL;
  char*   p_buf = NULL;

  if (!(smlr = calloc(sizeof(smlr_t), 1)) || !(p_buf = calloc(1, output_size))) {
    smlr_delete(smlr);
    return NULL;
  }

  switch (alignment) {
    case ALIGN_LEFT:
      smlr->left_bytes  = output_size - ELLIPSIS_LEN;
      smlr->right_bytes = 0U;
      break;
    case ALIGN_RIGHT:
      smlr->left_bytes  = 0U;
      smlr->right_bytes = output_size - ELLIPSIS_LEN;
      break;
    case ALIGN_MIDDLE:
      smlr->left_bytes  = (output_size - ELLIPSIS_LEN) / 2.f + 0.5f;
      smlr->right_bytes = (output_size - ELLIPSIS_LEN) / 2U;
      break;
    default:
      return NULL;
  }

  smlr->align       = alignment;
  smlr->p_buf       = p_buf;
  smlr->buf_bytes   = output_size;
  smlr->buf_base    = 0;
  smlr->index       = 0;
  smlr->input_bytes = 0;

  // check post condition
  if ((smlr->left_bytes + smlr->right_bytes + ELLIPSIS_LEN) != smlr->buf_bytes) {
    smlr_delete(smlr);
    return NULL;
  }

  return smlr;
}

int8_t smlr_delete(smlr_t* self) {
  if (!self)
    return EXIT_FAILURE;

  free(self->p_buf);
  free(self);

  return EXIT_SUCCESS;
}

int8_t smlr_push(smlr_t* self, const char c) {
  if (!self)
    return EXIT_FAILURE;

  if ((self->align == ALIGN_LEFT) && (self->input_bytes >= self->buf_bytes)) {
    self->input_bytes++;
    return EXIT_SUCCESS;
  }

  if ((self->align == ALIGN_MIDDLE) && (self->input_bytes == self->buf_bytes)) {
    self->buf_base = self->left_bytes;
  }

  if (self->index == self->buf_bytes) {
    self->index = self->buf_base;
  }

  *(self->p_buf + self->index) = c;

  self->input_bytes++;
  self->index++;

  return EXIT_SUCCESS;
}

int8_t smlr_get_buf(smlr_t* self, char* dst, size_t dst_bytes) {
  if (!self || !dst || !dst_bytes)
    return EXIT_FAILURE;

  if (self->input_bytes <= self->buf_bytes) {

    if (dst_bytes < (self->input_bytes + NULLTERM_LEN)) {
      return EXIT_FAILURE;
    }

    memcpy(dst, self->p_buf, self->input_bytes);
    dst[self->input_bytes] = '\0';

  } else {
    if (dst_bytes < (self->buf_bytes + NULLTERM_LEN)) {
      return EXIT_FAILURE;
    }

    switch (self->align) {
      case ALIGN_LEFT:
        memcpy(dst, self->p_buf, self->buf_bytes - ELLIPSIS_LEN);
        strncpy(dst + self->buf_bytes - ELLIPSIS_LEN, "...", ELLIPSIS_LEN);
        break;
      case ALIGN_RIGHT:
        memcpy(dst, self->p_buf + self->index, self->buf_bytes - self->index);
        memcpy(dst + self->buf_bytes - self->index, self->p_buf, self->index);
        strncpy(dst, "...", ELLIPSIS_LEN);
        break;
      case ALIGN_MIDDLE:
      default:
        memcpy(dst, self->p_buf, self->buf_base);
        memcpy(dst + self->buf_base, self->p_buf + self->index, self->buf_bytes - self->index);
        memcpy(dst + self->buf_base + self->buf_bytes - self->index,
               self->p_buf + self->buf_base,
               self->index - self->buf_base);
        strncpy(dst + self->buf_base, "...", ELLIPSIS_LEN);
        break;
    }

    dst[self->buf_bytes] = '\0';
  }

  return EXIT_SUCCESS;
}
