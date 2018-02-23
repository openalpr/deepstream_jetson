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

#include "dsopenalpr_lib.h"

#include <glib.h>

struct DsOpenalprCtx
{
  DsOpenalprInitParams init_params;
  GQueue *queue;
  GMutex lock;
};

DsOpenalprCtx *
DsOpenalprCtx_Init (DsOpenalprInitParams * init_params)
{
  DsOpenalprCtx *ctx = (DsOpenalprCtx *) g_malloc (sizeof (DsOpenalprCtx));
  ctx->init_params = *init_params;
  ctx->queue = g_queue_new ();
  g_mutex_init (&ctx->lock);
  return ctx;
}

// In case of an actual processing library, processing on data will be started
// in this function
void
DsOpenalpr_QueueInput (DsOpenalprCtx * ctx, unsigned char *data)
{
  // Queue input. Start processing.
  // Here we just add the input pointer to a queue
  g_mutex_lock (&ctx->lock);
  g_queue_push_tail (ctx->queue, data);
  g_mutex_unlock (&ctx->lock);
}

// In case of an actual processing library, processing on data wil be completed
// in this function and output will be returned
DsOpenalprOutput *
DsOpenalpr_DequeueOutput (DsOpenalprCtx * ctx)
{
  DsOpenalprOutput *out = g_malloc0 (sizeof (DsOpenalprOutput));

  // Processing finished. Dequeue
  g_mutex_lock (&ctx->lock);
  if (!g_queue_is_empty (ctx->queue)) {
    g_queue_pop_head (ctx->queue);
  }
  g_mutex_unlock (&ctx->lock);

  // Fill output structure using processed output
  // Here, we fake some detected objects and labels
  if (ctx->init_params.full_frame) {
    out->num_objects = 2;
    out->object[0] = (DsOpenalpr_Object) {
    ctx->init_params.processing_width / 8,
          ctx->init_params.processing_height / 8,
          ctx->init_params.processing_width / 8,
          ctx->init_params.processing_height / 8, "Obj0"};
    out->object[1] = (DsOpenalpr_Object) {
    ctx->init_params.processing_width / 2,
          ctx->init_params.processing_height / 2,
          ctx->init_params.processing_width / 8,
          ctx->init_params.processing_height / 8, "Obj1"};
  } else {
    out->num_objects = 1;
    out->object[0] = (DsOpenalpr_Object) {
    ctx->init_params.processing_width / 8,
          ctx->init_params.processing_height / 8,
          ctx->init_params.processing_width / 8,
          ctx->init_params.processing_height / 8, ""};
    g_snprintf (out->object[0].label, 64, "Obj_label");
  }

  return out;
}

void
DsOpenalprCtx_Deinit (DsOpenalprCtx * ctx)
{
  g_queue_free_full (ctx->queue, g_free);
  g_mutex_clear (&ctx->lock);
  g_free (ctx);
}
