/**
 * Copyright (c) 2017, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA Corporation is strictly prohibited.
 *
 */

#ifndef __DSOPENALPR_LIB__
#define __DSOPENALPR_LIB__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DsOpenalprCtx DsOpenalprCtx;

typedef struct
{
  int processing_width;
  int processing_height;
  int full_frame;
} DsOpenalprInitParams;

typedef struct
{
  int left;
  int top;
  int width;
  int height;
  char label[64];
} DsOpenalpr_Object;

typedef struct
{
  int num_objects;
  DsOpenalpr_Object object[4];
} DsOpenalprOutput;

// Initialize library context
DsOpenalprCtx * DsOpenalprCtx_Init (DsOpenalprInitParams *init_params);

// Queue input for processing
void DsOpenalpr_QueueInput (DsOpenalprCtx *ctx, unsigned char *data);

// Dequeue processed output
DsOpenalprOutput *DsOpenalpr_DequeueOutput (DsOpenalprCtx *ctx);

// Deinitialize library context
void DsOpenalprCtx_Deinit (DsOpenalprCtx *ctx);

#ifdef __cplusplus
}
#endif

#endif
