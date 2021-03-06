/* Copyright 2017 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#ifndef TENSORFLOW_CONTRIB_LITE_BUILTIN_OP_DATA_H_
#define TENSORFLOW_CONTRIB_LITE_BUILTIN_OP_DATA_H_

#include <stdint.h>

#include "tensorflow/contrib/lite/context.h"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

// TODO(aselle): Consider using "if this then that" for testing.

// Useful placeholder to put in otherwise empty structs to avoid size warnings.
typedef struct {
  char dummy_;
} EmptyStructPlaceholder;

// Possible padding types (for convolutions)
typedef enum {
  kTfLitePaddingUnknown = 0,
  kTfLitePaddingSame,
  kTfLitePaddingValid,
} TfLitePadding;

typedef struct {
  int width;
  int height;
} TfLitePaddingValues;

// Possible fused activation functions.
// TODO(aselle): rename to TfLiteActivation
typedef enum {
  kTfLiteActNone = 0,
  kTfLiteActRelu,
  kTfLiteActRelu1,
  kTfLiteActRelu6,
  kTfLiteActTanh,
  kTfLiteActSignBit,
  kTfLiteActSigmoid,
} TfLiteFusedActivation;

typedef struct {
  TfLitePadding padding;
  int stride_width;
  int stride_height;
  int dilation_width_factor;
  int dilation_height_factor;
  TfLiteFusedActivation activation;
} TfLiteConvParams;

typedef struct {
  TfLitePadding padding;
  int stride_width;
  int stride_height;
  int filter_width;
  int filter_height;
  TfLiteFusedActivation activation;
  struct {
    TfLitePaddingValues padding;
  } computed;
} TfLitePoolParams;

typedef struct {
  TfLitePadding padding;
  int stride_width;
  int stride_height;
  int depth_multiplier;
  TfLiteFusedActivation activation;
} TfLiteDepthwiseConvParams;

typedef struct {
  int rank;
  TfLiteFusedActivation activation;
} TfLiteSVDFParams;

typedef struct {
  TfLiteFusedActivation activation;
} TfLiteRNNParams;

typedef struct {
  bool time_major;
  TfLiteFusedActivation activation;
} TfLiteSequenceRNNParams;

typedef enum {
  kTfLiteFullyConnectedWeightsFormatDefault = 0,
  kTfLiteFullyConnectedWeightsFormatShuffled4x16Int8 = 1,
} TfLiteFullyConnectedWeightsFormat;

typedef struct {
  // Parameters for FullyConnected version 1 or above.
  TfLiteFusedActivation activation;

  // Parameters for FullyConnected version 2 or above.
  TfLiteFullyConnectedWeightsFormat weights_format;
} TfLiteFullyConnectedParams;

typedef enum {
  kTfLiteLshProjectionUnknown = 0,
  kTfLiteLshProjectionSparse = 1,
  kTfLiteLshProjectionDense = 2,
} TfLiteLSHProjectionType;

typedef struct {
  TfLiteLSHProjectionType type;
} TfLiteLSHProjectionParams;

typedef struct {
  float beta;
} TfLiteSoftmaxParams;

typedef struct {
  int axis;
  TfLiteFusedActivation activation;
} TfLiteConcatenationParams;

typedef struct {
  TfLiteFusedActivation activation;
} TfLiteAddParams;

typedef struct {
  EmptyStructPlaceholder placeholder_;
} TfLiteSpaceToBatchNDParams;

typedef struct {
  EmptyStructPlaceholder placeholder_;
} TfLiteBatchToSpaceNDParams;

typedef struct {
  TfLiteFusedActivation activation;
} TfLiteMulParams;

typedef struct {
  TfLiteFusedActivation activation;
} TfLiteSubParams;

typedef struct {
  TfLiteFusedActivation activation;
} TfLiteDivParams;

typedef struct {
  TfLiteFusedActivation activation;
} TfLiteL2NormParams;

typedef struct {
  int radius;
  float bias;
  float alpha;
  float beta;
} TfLiteLocalResponseNormParams;

typedef enum {
  kTfLiteLSTMFullKernel = 0,
  kTfLiteLSTMBasicKernel
} TfLiteLSTMKernelType;

typedef struct {
  // Parameters for LSTM version 1.
  TfLiteFusedActivation activation;
  float cell_clip;
  float proj_clip;

  // Parameters for LSTM version 2.
  // kTfLiteLSTMBasicKernel is only supported in version 2 or above.
  TfLiteLSTMKernelType kernel_type;
} TfLiteLSTMParams;

typedef struct {
  bool align_corners;
} TfLiteResizeBilinearParams;

typedef struct {
  EmptyStructPlaceholder placeholder_;
} TfLitePadParams;

typedef struct {
  EmptyStructPlaceholder placeholder_;
} TfLitePadV2Params;

typedef struct {
  // TODO(ahentz): We can't have dynamic data in this struct, at least not yet.
  // For now we will fix the maximum possible number of dimensions.
  int shape[8];
  int num_dimensions;
} TfLiteReshapeParams;

typedef struct {
  int ngram_size;
  int max_skip_size;
  bool include_all_ngrams;
} TfLiteSkipGramParams;

typedef struct {
  int block_size;
} TfLiteSpaceToDepthParams;

typedef struct {
  TfLiteType in_data_type;
  TfLiteType out_data_type;
} TfLiteCastParams;

typedef enum {
  kTfLiteCombinerTypeSum = 0,
  kTfLiteCombinerTypeMean = 1,
  kTfLiteCombinerTypeSqrtn = 2,
} TfLiteCombinerType;

typedef struct {
  TfLiteCombinerType combiner;
} TfLiteEmbeddingLookupSparseParams;

typedef struct {
  int axis;
} TfLiteGatherParams;

typedef struct {
  EmptyStructPlaceholder placeholder_;
} TfLiteTransposeParams;

typedef struct {
  bool keep_dims;
} TfLiteReducerParams;

typedef struct {
  int num_splits;
} TfLiteSplitParams;

typedef struct {
  // TODO(ahentz): We can't have dynamic data in this struct, at least not yet.
  // For now we will fix the maximum possible number of dimensions.
  int squeeze_dims[8];
  int num_squeeze_dims;
} TfLiteSqueezeParams;

typedef struct {
  int begin_mask;
  int end_mask;
  int ellipsis_mask;
  int new_axis_mask;
  int shrink_axis_mask;
} TfLiteStridedSliceParams;

typedef struct {
  TfLiteType output_type;
} TfLiteArgMaxParams;

typedef struct {
  TfLiteType output_type;
} TfLiteArgMinParams;

typedef struct {
  TfLitePadding padding;
  int stride_width;
  int stride_height;
} TfLiteTransposeConvParams;

typedef struct {
  bool validate_indices;
} TfLiteSparseToDenseParams;

typedef struct {
  TfLiteType out_type;
} TfLiteShapeParams;

typedef struct {
  // Parameters supported by version 1:
  float min;
  float max;
  int num_bits;

  // Parameters supported by version 2:
  bool narrow_range;
} TfLiteFakeQuantParams;

typedef struct {
  int values_count;
  int axis;
} TfLitePackParams;

typedef struct {
  int axis;
} TfLiteOneHotParams;

typedef struct {
  int num;
  int axis;
} TfLiteUnpackParams;

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  // TENSORFLOW_CONTRIB_LITE_BUILTIN_OP_DATA_H_
