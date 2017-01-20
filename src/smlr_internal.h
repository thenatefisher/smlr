#ifndef SMLR_INTL_H_
#define SMLR_INTL_H_

#include "smlr.h"
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct smlr_s {
  char*            p_buf;
  size_t           index;
  size_t           input_bytes;
  size_t           buf_bytes;
  size_t           left_bytes;
  size_t           right_bytes;
  size_t           buf_base;
  smlr_alignment_t align;
};

#ifdef __cplusplus
}
#endif

#endif
