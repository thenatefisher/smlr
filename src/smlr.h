/*
 * @file
 * Given the pushed characters, compute a string following one of these forms:
 *    LEFT...RIGHT   (ALIGN_MIDDLE)
 *    ...RIGHT       (ALIGN_RIGHT)
 *    LEFT...        (ALIGN_LEFT)
 */

#ifndef SMLR_H_
#define SMLR_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct smlr_s smlr_t;

typedef enum { ALIGN_MIDDLE, ALIGN_LEFT, ALIGN_RIGHT } smlr_alignment_t;

int8_t smlr_delete(smlr_t* self);
int8_t smlr_get_buf(smlr_t* self, char* dst, size_t dst_bytes);
int8_t smlr_push(smlr_t* self, const char c, uint8_t* p_is_end);
smlr_t* smlr_new(size_t output_size, smlr_alignment_t alignment);

#ifdef __cplusplus
}
#endif

#endif
