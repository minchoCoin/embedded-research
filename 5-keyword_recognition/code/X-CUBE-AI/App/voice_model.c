/**
  ******************************************************************************
  * @file    voice_model.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Wed Aug 28 18:48:18 2024
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */


#include "voice_model.h"
#include "voice_model_data.h"

#include "ai_platform.h"
#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "core_convert.h"

#include "layers.h"



#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_voice_model
 
#undef AI_VOICE_MODEL_MODEL_SIGNATURE
#define AI_VOICE_MODEL_MODEL_SIGNATURE     "cf6893bfd0aac9a32a7bce4b1d3fbdf7"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Wed Aug 28 18:48:18 2024"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_VOICE_MODEL_N_BATCHES
#define AI_VOICE_MODEL_N_BATCHES         (1)

static ai_ptr g_voice_model_activations_map[1] = AI_C_ARRAY_INIT;
static ai_ptr g_voice_model_weights_map[1] = AI_C_ARRAY_INIT;



/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  gemm_12_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 4416, AI_STATIC)
/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  gemm_13_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 104, AI_STATIC)
/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  nl_14_scratch0_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 8, AI_STATIC)
/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  serving_default_keras_tensor0_output_array, AI_ARRAY_FORMAT_S8|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 15480, AI_STATIC)
/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  serving_default_keras_tensor0_0_conversion_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 15480, AI_STATIC)
/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  upsample_4_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1024, AI_STATIC)
/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  upsample_4_1_conversion_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1024, AI_STATIC)
/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_5_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1024, AI_STATIC)
/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_6_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1024, AI_STATIC)
/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_7_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 8192, AI_STATIC)
/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_9_pad_before_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 11552, AI_STATIC)
/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_9_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 4096, AI_STATIC)
/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  gemm_12_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 64, AI_STATIC)
/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  gemm_13_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 8, AI_STATIC)
/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  nl_14_output_array, AI_ARRAY_FORMAT_S8|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 8, AI_STATIC)
/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  tfl_pseudo_qconst8_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1, AI_STATIC)
/* Array#16 */
AI_ARRAY_OBJ_DECLARE(
  tfl_pseudo_qconst9_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1, AI_STATIC)
/* Array#17 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_7_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 512, AI_STATIC)
/* Array#18 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_7_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 32, AI_STATIC)
/* Array#19 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_9_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 32768, AI_STATIC)
/* Array#20 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_9_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 64, AI_STATIC)
/* Array#21 */
AI_ARRAY_OBJ_DECLARE(
  gemm_12_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 262144, AI_STATIC)
/* Array#22 */
AI_ARRAY_OBJ_DECLARE(
  gemm_12_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 64, AI_STATIC)
/* Array#23 */
AI_ARRAY_OBJ_DECLARE(
  gemm_13_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 512, AI_STATIC)
/* Array#24 */
AI_ARRAY_OBJ_DECLARE(
  gemm_13_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 8, AI_STATIC)
/* Array#25 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_7_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1536, AI_STATIC)
/* Array#26 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_7_scratch1_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 2048, AI_STATIC)
/* Array#27 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_9_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 8064, AI_STATIC)
/* Array#28 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_9_scratch1_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 2048, AI_STATIC)
/**  Array metadata declarations section  *************************************/
/* Int quant #0 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(serving_default_keras_tensor0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.1303439885377884f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #1 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(upsample_4_1_conversion_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.1303439885377884f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #2 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(eltwise_5_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.177979975938797f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #3 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(eltwise_6_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.177979975938797f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #4 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_7_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.09511444717645645f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #5 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_9_pad_before_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.09511444717645645f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #6 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_9_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0575246587395668f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #7 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_12_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0803915336728096f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #8 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_13_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.38720065355300903f),
    AI_PACK_INTQ_ZP(-29)))

/* Int quant #9 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(nl_14_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00390625f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #10 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(tfl_pseudo_qconst8_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(5.738407793387523e-08f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #11 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(tfl_pseudo_qconst9_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.008266427554190159f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #12 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_7_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 32,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.005879156291484833f, 0.001851943088695407f, 0.0015633723232895136f, 0.0012802359415218234f, 0.0011619748547673225f, 0.0029969983734190464f, 0.0024239495396614075f, 0.002342845546081662f, 0.0013472334248945117f, 0.0027525420300662518f, 0.0025358146522194147f, 0.0014567235484719276f, 0.002502099610865116f, 0.0015568071976304054f, 0.0031455657444894314f, 0.0023999346885830164f, 0.002079748548567295f, 0.0009831252973526716f, 0.0027908976189792156f, 0.0020073868799954653f, 0.002398809650912881f, 0.0017377978656440973f, 0.0018528515938669443f, 0.002172774402424693f, 0.00169690465554595f, 0.002519020112231374f, 0.00480889854952693f, 0.0022064081858843565f, 0.0030546023044735193f, 0.0037942954804748297f, 0.002060221042484045f, 0.002654923126101494f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #13 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_9_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 64,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0028031656984239817f, 0.004571236670017242f, 0.0024965950287878513f, 0.004246829077601433f, 0.0028643810655921698f, 0.0023553904611617327f, 0.002460672752931714f, 0.002726329257711768f, 0.0012985316570848227f, 0.003289640648290515f, 0.003048458369448781f, 0.0018818655516952276f, 0.0022061422932893038f, 0.0006580077460967004f, 0.0028052565176039934f, 0.0018797082593664527f, 0.0021708356216549873f, 0.003369305981323123f, 0.00445679621770978f, 0.00223771040327847f, 0.00226577022112906f, 0.0033712019212543964f, 0.003927947022020817f, 0.002761331619694829f, 0.0014849203871563077f, 0.0009479119325987995f, 0.0020515357609838247f, 0.0032992837950587273f, 0.002968164626508951f, 0.0028076369781047106f, 0.002800606656819582f, 0.001990377437323332f, 0.002794010564684868f, 0.0029997583478689194f, 0.0021017135586589575f, 0.00235279300250113f, 0.002363316947594285f, 0.0008400023216381669f, 0.0034166837576776743f, 0.0025697562377899885f, 0.002399434568360448f, 0.003065161406993866f, 0.0026265764608979225f, 0.0025117506738752127f, 0.0011185514740645885f, 0.0019172097090631723f, 0.0030265527311712503f, 0.0021039959974586964f, 0.002751687541604042f, 0.0030282195657491684f, 0.002710414119064808f, 0.0018742176471278071f, 0.002153402892872691f, 0.002458800794556737f, 0.0019592915195971727f, 0.0024297907948493958f, 0.0024906841572374105f, 0.0051085976883769035f, 0.001216311240568757f, 0.0026429027784615755f, 0.0033190848771482706f, 0.00318229291588068f, 0.003199361264705658f, 0.002193586900830269f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #14 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_12_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 64,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.000510739628225565f, 0.0020232314709573984f, 0.002286892384290695f, 0.002593220677226782f, 0.002206088975071907f, 0.0007723217131569982f, 0.0024646057281643152f, 0.0005073672509752214f, 0.0021615345031023026f, 0.0007259761914610863f, 0.001969669247046113f, 0.002151105087250471f, 0.0022648924496024847f, 0.0019673786591738462f, 0.0024436141829937696f, 0.002375092124566436f, 0.0020156092941761017f, 0.0022784490138292313f, 0.0021371592301875353f, 0.0027160111349076033f, 0.0024681647773832083f, 0.002557713072746992f, 0.0022626970894634724f, 0.0020459028892219067f, 0.0020592317450791597f, 0.0023749584797769785f, 0.0023331306874752045f, 0.0005567664047703147f, 0.0019204583950340748f, 0.002382410690188408f, 0.001530494075268507f, 0.002366269938647747f, 0.002116384683176875f, 0.002114106435328722f, 0.002357341581955552f, 0.001955247251316905f, 0.002281717723235488f, 0.0023148562759160995f, 0.002156510017812252f, 0.0029391893185675144f, 0.002316232305020094f, 0.0005656340508721769f, 0.0025219377130270004f, 0.001993343932554126f, 0.001917347894050181f, 0.0024251986760646105f, 0.002213528845459223f, 0.0005984677700325847f, 0.002205867553129792f, 0.002156074857339263f, 0.0020098467357456684f, 0.0028475956059992313f, 0.0004996508359909058f, 0.002412061905488372f, 0.002063322812318802f, 0.0021740442607551813f, 0.002472610678523779f, 0.002386464038863778f, 0.0020665957126766443f, 0.0020576883107423782f, 0.0020692506805062294f, 0.00199653091840446f, 0.002003811066970229f, 0.002139416756108403f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #15 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_13_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 8,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.004274876322597265f, 0.003288847394287586f, 0.004208399914205074f, 0.0039140889421105385f, 0.003243571612983942f, 0.00461954902857542f, 0.00411117123439908f, 0.00343050598166883f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #16 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_7_scratch1_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.09511444717645645f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #17 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_9_scratch1_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0575246587395668f),
    AI_PACK_INTQ_ZP(-128)))

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  gemm_12_scratch0, AI_STATIC,
  0, 0x0,
  AI_SHAPE_INIT(4, 1, 4416, 1, 1), AI_STRIDE_INIT(4, 2, 2, 8832, 8832),
  1, &gemm_12_scratch0_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  gemm_13_scratch0, AI_STATIC,
  1, 0x0,
  AI_SHAPE_INIT(4, 1, 104, 1, 1), AI_STRIDE_INIT(4, 2, 2, 208, 208),
  1, &gemm_13_scratch0_array, NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  nl_14_scratch0, AI_STATIC,
  2, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &nl_14_scratch0_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  serving_default_keras_tensor0_output, AI_STATIC,
  3, 0x1,
  AI_SHAPE_INIT(4, 1, 120, 1, 129), AI_STRIDE_INIT(4, 1, 1, 120, 120),
  1, &serving_default_keras_tensor0_output_array, &serving_default_keras_tensor0_output_array_intq)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  serving_default_keras_tensor0_0_conversion_output, AI_STATIC,
  4, 0x0,
  AI_SHAPE_INIT(4, 1, 120, 1, 129), AI_STRIDE_INIT(4, 4, 4, 480, 480),
  1, &serving_default_keras_tensor0_0_conversion_output_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  serving_default_keras_tensor0_0_conversion_output0, AI_STATIC,
  5, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 120, 129), AI_STRIDE_INIT(4, 4, 4, 4, 480),
  1, &serving_default_keras_tensor0_0_conversion_output_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  upsample_4_output, AI_STATIC,
  6, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 32, 32), AI_STRIDE_INIT(4, 4, 4, 4, 128),
  1, &upsample_4_output_array, NULL)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  upsample_4_1_conversion_output, AI_STATIC,
  7, 0x1,
  AI_SHAPE_INIT(4, 1, 1, 32, 32), AI_STRIDE_INIT(4, 1, 1, 1, 32),
  1, &upsample_4_1_conversion_output_array, &upsample_4_1_conversion_output_array_intq)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_5_output, AI_STATIC,
  8, 0x1,
  AI_SHAPE_INIT(4, 1, 1, 32, 32), AI_STRIDE_INIT(4, 1, 1, 1, 32),
  1, &eltwise_5_output_array, &eltwise_5_output_array_intq)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_6_output, AI_STATIC,
  9, 0x1,
  AI_SHAPE_INIT(4, 1, 1, 32, 32), AI_STRIDE_INIT(4, 1, 1, 1, 32),
  1, &eltwise_6_output_array, &eltwise_6_output_array_intq)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_7_output, AI_STATIC,
  10, 0x1,
  AI_SHAPE_INIT(4, 1, 32, 16, 16), AI_STRIDE_INIT(4, 1, 1, 32, 512),
  1, &conv2d_7_output_array, &conv2d_7_output_array_intq)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_9_pad_before_output, AI_STATIC,
  11, 0x1,
  AI_SHAPE_INIT(4, 1, 32, 19, 19), AI_STRIDE_INIT(4, 1, 1, 32, 608),
  1, &conv2d_9_pad_before_output_array, &conv2d_9_pad_before_output_array_intq)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_9_output, AI_STATIC,
  12, 0x1,
  AI_SHAPE_INIT(4, 1, 64, 8, 8), AI_STRIDE_INIT(4, 1, 1, 64, 512),
  1, &conv2d_9_output_array, &conv2d_9_output_array_intq)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_9_output0, AI_STATIC,
  13, 0x1,
  AI_SHAPE_INIT(4, 1, 4096, 1, 1), AI_STRIDE_INIT(4, 1, 1, 4096, 4096),
  1, &conv2d_9_output_array, &conv2d_9_output_array_intq)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  gemm_12_output, AI_STATIC,
  14, 0x1,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 1, 1, 64, 64),
  1, &gemm_12_output_array, &gemm_12_output_array_intq)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  gemm_13_output, AI_STATIC,
  15, 0x1,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 1, 1, 8, 8),
  1, &gemm_13_output_array, &gemm_13_output_array_intq)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(
  nl_14_output, AI_STATIC,
  16, 0x1,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 1, 1, 8, 8),
  1, &nl_14_output_array, &nl_14_output_array_intq)

/* Tensor #17 */
AI_TENSOR_OBJ_DECLARE(
  tfl_pseudo_qconst8, AI_STATIC,
  17, 0x1,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 1, 1, 1, 1),
  1, &tfl_pseudo_qconst8_array, &tfl_pseudo_qconst8_array_intq)

/* Tensor #18 */
AI_TENSOR_OBJ_DECLARE(
  tfl_pseudo_qconst9, AI_STATIC,
  18, 0x1,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 1, 1, 1, 1),
  1, &tfl_pseudo_qconst9_array, &tfl_pseudo_qconst9_array_intq)

/* Tensor #19 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_7_weights, AI_STATIC,
  19, 0x1,
  AI_SHAPE_INIT(4, 1, 4, 4, 32), AI_STRIDE_INIT(4, 1, 1, 32, 128),
  1, &conv2d_7_weights_array, &conv2d_7_weights_array_intq)

/* Tensor #20 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_7_bias, AI_STATIC,
  20, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &conv2d_7_bias_array, NULL)

/* Tensor #21 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_9_weights, AI_STATIC,
  21, 0x1,
  AI_SHAPE_INIT(4, 32, 4, 4, 64), AI_STRIDE_INIT(4, 1, 32, 2048, 8192),
  1, &conv2d_9_weights_array, &conv2d_9_weights_array_intq)

/* Tensor #22 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_9_bias, AI_STATIC,
  22, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &conv2d_9_bias_array, NULL)

/* Tensor #23 */
AI_TENSOR_OBJ_DECLARE(
  gemm_12_weights, AI_STATIC,
  23, 0x1,
  AI_SHAPE_INIT(4, 4096, 64, 1, 1), AI_STRIDE_INIT(4, 1, 4096, 262144, 262144),
  1, &gemm_12_weights_array, &gemm_12_weights_array_intq)

/* Tensor #24 */
AI_TENSOR_OBJ_DECLARE(
  gemm_12_bias, AI_STATIC,
  24, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &gemm_12_bias_array, NULL)

/* Tensor #25 */
AI_TENSOR_OBJ_DECLARE(
  gemm_13_weights, AI_STATIC,
  25, 0x1,
  AI_SHAPE_INIT(4, 64, 8, 1, 1), AI_STRIDE_INIT(4, 1, 64, 512, 512),
  1, &gemm_13_weights_array, &gemm_13_weights_array_intq)

/* Tensor #26 */
AI_TENSOR_OBJ_DECLARE(
  gemm_13_bias, AI_STATIC,
  26, 0x0,
  AI_SHAPE_INIT(4, 1, 8, 1, 1), AI_STRIDE_INIT(4, 4, 4, 32, 32),
  1, &gemm_13_bias_array, NULL)

/* Tensor #27 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_7_scratch0, AI_STATIC,
  27, 0x0,
  AI_SHAPE_INIT(4, 1, 1536, 1, 1), AI_STRIDE_INIT(4, 1, 1, 1536, 1536),
  1, &conv2d_7_scratch0_array, NULL)

/* Tensor #28 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_7_scratch1, AI_STATIC,
  28, 0x1,
  AI_SHAPE_INIT(4, 1, 32, 32, 2), AI_STRIDE_INIT(4, 1, 1, 32, 1024),
  1, &conv2d_7_scratch1_array, &conv2d_7_scratch1_array_intq)

/* Tensor #29 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_9_scratch0, AI_STATIC,
  29, 0x0,
  AI_SHAPE_INIT(4, 1, 8064, 1, 1), AI_STRIDE_INIT(4, 1, 1, 8064, 8064),
  1, &conv2d_9_scratch0_array, NULL)

/* Tensor #30 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_9_scratch1, AI_STATIC,
  30, 0x1,
  AI_SHAPE_INIT(4, 1, 64, 16, 2), AI_STRIDE_INIT(4, 1, 1, 64, 1024),
  1, &conv2d_9_scratch1_array, &conv2d_9_scratch1_array_intq)



/**  Layer declarations section  **********************************************/



AI_STATIC_CONST ai_i32 nl_14_nl_params_data[] = { 1663014144, 25, -62 };
AI_ARRAY_OBJ_DECLARE(
    nl_14_nl_params, AI_ARRAY_FORMAT_S32,
    nl_14_nl_params_data, nl_14_nl_params_data, 3, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_14_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_13_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_14_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_14_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  nl_14_layer, 14,
  NL_TYPE, 0x0, NULL,
  nl, forward_sm_integer,
  &nl_14_chain,
  NULL, &nl_14_layer, AI_STATIC, 
  .nl_params = &nl_14_nl_params, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  gemm_13_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_12_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_13_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &gemm_13_weights, &gemm_13_bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_13_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  gemm_13_layer, 13,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA_ch,
  &gemm_13_chain,
  NULL, &nl_14_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  gemm_12_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_9_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_12_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &gemm_12_weights, &gemm_12_bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_12_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  gemm_12_layer, 12,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA_ch,
  &gemm_12_chain,
  NULL, &gemm_13_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_9_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_9_pad_before_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_9_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_9_weights, &conv2d_9_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_9_scratch0, &conv2d_9_scratch1)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_9_layer, 10,
  OPTIMIZED_CONV2D_TYPE, 0x0, NULL,
  conv2d_nl_pool, forward_conv2d_deep_sssa8_ch_nl_pool,
  &conv2d_9_chain,
  NULL, &gemm_12_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = AI_HANDLE_PTR(pool_func_mp_array_integer_INT8), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)


AI_STATIC_CONST ai_i8 conv2d_9_pad_before_value_data[] = { -128 };
AI_ARRAY_OBJ_DECLARE(
    conv2d_9_pad_before_value, AI_ARRAY_FORMAT_S8,
    conv2d_9_pad_before_value_data, conv2d_9_pad_before_value_data, 1, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_9_pad_before_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_7_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_9_pad_before_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conv2d_9_pad_before_layer, 9,
  PAD_TYPE, 0x0, NULL,
  pad, forward_pad,
  &conv2d_9_pad_before_chain,
  NULL, &conv2d_9_layer, AI_STATIC, 
  .value = &conv2d_9_pad_before_value, 
  .mode = AI_PAD_CONSTANT, 
  .pads = AI_SHAPE_INIT(4, 1, 1, 2, 2), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_7_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_6_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_7_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_7_weights, &conv2d_7_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_7_scratch0, &conv2d_7_scratch1)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_7_layer, 8,
  OPTIMIZED_CONV2D_TYPE, 0x0, NULL,
  conv2d_nl_pool, forward_conv2d_sssa8_ch_nl_pool,
  &conv2d_7_chain,
  NULL, &conv2d_9_pad_before_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 2, 2), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = AI_HANDLE_PTR(pool_func_mp_array_integer_INT8), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  eltwise_6_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &eltwise_5_output, &tfl_pseudo_qconst8),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_6_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  eltwise_6_layer, 6,
  ELTWISE_INTEGER_TYPE, 0x0, NULL,
  eltwise_integer, forward_eltwise_integer_INT8,
  &eltwise_6_chain,
  NULL, &conv2d_7_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_INT8, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  eltwise_5_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &upsample_4_1_conversion_output, &tfl_pseudo_qconst9),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_5_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  eltwise_5_layer, 5,
  ELTWISE_INTEGER_TYPE, 0x0, NULL,
  eltwise_integer, forward_eltwise_integer_INT8,
  &eltwise_5_chain,
  NULL, &eltwise_6_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_INT8, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  upsample_4_1_conversion_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &upsample_4_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &upsample_4_1_conversion_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  upsample_4_1_conversion_layer, 4,
  NL_TYPE, 0x0, NULL,
  nl, node_convert,
  &upsample_4_1_conversion_chain,
  NULL, &eltwise_5_layer, AI_STATIC, 
)


AI_STATIC_CONST ai_float upsample_4_scales_data[] = { 0.24806201550387597, 0.26666666666666666, 1.0, 1 };
AI_ARRAY_OBJ_DECLARE(
    upsample_4_scales, AI_ARRAY_FORMAT_FLOAT,
    upsample_4_scales_data, upsample_4_scales_data, 4, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  upsample_4_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &serving_default_keras_tensor0_0_conversion_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &upsample_4_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  upsample_4_layer, 4,
  UPSAMPLE_TYPE, 0x0, NULL,
  upsample, forward_upsample_bilinear,
  &upsample_4_chain,
  NULL, &upsample_4_1_conversion_layer, AI_STATIC, 
  .scales = &upsample_4_scales, 
  .center = true, 
  .mode = AI_UPSAMPLE_BILINEAR, 
  .nearest_mode = AI_ROUND_FLOOR, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  serving_default_keras_tensor0_0_conversion_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &serving_default_keras_tensor0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &serving_default_keras_tensor0_0_conversion_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  serving_default_keras_tensor0_0_conversion_layer, 0,
  NL_TYPE, 0x0, NULL,
  nl, node_convert,
  &serving_default_keras_tensor0_0_conversion_chain,
  NULL, &upsample_4_layer, AI_STATIC, 
)


#if (AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 296616, 1, 1),
    296616, NULL, NULL),
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 66016, 1, 1),
    66016, NULL, NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_VOICE_MODEL_IN_NUM, &serving_default_keras_tensor0_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_VOICE_MODEL_OUT_NUM, &nl_14_output),
  &serving_default_keras_tensor0_0_conversion_layer, 0, NULL)

#else

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 296616, 1, 1),
      296616, NULL, NULL)
  ),
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 66016, 1, 1),
      66016, NULL, NULL)
  ),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_VOICE_MODEL_IN_NUM, &serving_default_keras_tensor0_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_VOICE_MODEL_OUT_NUM, &nl_14_output),
  &serving_default_keras_tensor0_0_conversion_layer, 0, NULL)

#endif	/*(AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)*/


/******************************************************************************/
AI_DECLARE_STATIC
ai_bool voice_model_configure_activations(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_activations_map(g_voice_model_activations_map, 1, params)) {
    /* Updating activations (byte) offsets */
    
    serving_default_keras_tensor0_output_array.data = AI_PTR(g_voice_model_activations_map[0] + 46440);
    serving_default_keras_tensor0_output_array.data_start = AI_PTR(g_voice_model_activations_map[0] + 46440);
    
    serving_default_keras_tensor0_0_conversion_output_array.data = AI_PTR(g_voice_model_activations_map[0] + 0);
    serving_default_keras_tensor0_0_conversion_output_array.data_start = AI_PTR(g_voice_model_activations_map[0] + 0);
    
    upsample_4_output_array.data = AI_PTR(g_voice_model_activations_map[0] + 61920);
    upsample_4_output_array.data_start = AI_PTR(g_voice_model_activations_map[0] + 61920);
    
    upsample_4_1_conversion_output_array.data = AI_PTR(g_voice_model_activations_map[0] + 0);
    upsample_4_1_conversion_output_array.data_start = AI_PTR(g_voice_model_activations_map[0] + 0);
    
    eltwise_5_output_array.data = AI_PTR(g_voice_model_activations_map[0] + 1024);
    eltwise_5_output_array.data_start = AI_PTR(g_voice_model_activations_map[0] + 1024);
    
    eltwise_6_output_array.data = AI_PTR(g_voice_model_activations_map[0] + 0);
    eltwise_6_output_array.data_start = AI_PTR(g_voice_model_activations_map[0] + 0);
    
    conv2d_7_scratch0_array.data = AI_PTR(g_voice_model_activations_map[0] + 1024);
    conv2d_7_scratch0_array.data_start = AI_PTR(g_voice_model_activations_map[0] + 1024);
    
    conv2d_7_scratch1_array.data = AI_PTR(g_voice_model_activations_map[0] + 2560);
    conv2d_7_scratch1_array.data_start = AI_PTR(g_voice_model_activations_map[0] + 2560);
    
    conv2d_7_output_array.data = AI_PTR(g_voice_model_activations_map[0] + 4608);
    conv2d_7_output_array.data_start = AI_PTR(g_voice_model_activations_map[0] + 4608);
    
    conv2d_9_pad_before_output_array.data = AI_PTR(g_voice_model_activations_map[0] + 12800);
    conv2d_9_pad_before_output_array.data_start = AI_PTR(g_voice_model_activations_map[0] + 12800);
    
    conv2d_9_scratch0_array.data = AI_PTR(g_voice_model_activations_map[0] + 0);
    conv2d_9_scratch0_array.data_start = AI_PTR(g_voice_model_activations_map[0] + 0);
    
    conv2d_9_scratch1_array.data = AI_PTR(g_voice_model_activations_map[0] + 8064);
    conv2d_9_scratch1_array.data_start = AI_PTR(g_voice_model_activations_map[0] + 8064);
    
    conv2d_9_output_array.data = AI_PTR(g_voice_model_activations_map[0] + 24352);
    conv2d_9_output_array.data_start = AI_PTR(g_voice_model_activations_map[0] + 24352);
    
    gemm_12_scratch0_array.data = AI_PTR(g_voice_model_activations_map[0] + 0);
    gemm_12_scratch0_array.data_start = AI_PTR(g_voice_model_activations_map[0] + 0);
    
    gemm_12_output_array.data = AI_PTR(g_voice_model_activations_map[0] + 8832);
    gemm_12_output_array.data_start = AI_PTR(g_voice_model_activations_map[0] + 8832);
    
    gemm_13_scratch0_array.data = AI_PTR(g_voice_model_activations_map[0] + 0);
    gemm_13_scratch0_array.data_start = AI_PTR(g_voice_model_activations_map[0] + 0);
    
    gemm_13_output_array.data = AI_PTR(g_voice_model_activations_map[0] + 208);
    gemm_13_output_array.data_start = AI_PTR(g_voice_model_activations_map[0] + 208);
    
    nl_14_scratch0_array.data = AI_PTR(g_voice_model_activations_map[0] + 0);
    nl_14_scratch0_array.data_start = AI_PTR(g_voice_model_activations_map[0] + 0);
    
    nl_14_output_array.data = AI_PTR(g_voice_model_activations_map[0] + 32);
    nl_14_output_array.data_start = AI_PTR(g_voice_model_activations_map[0] + 32);
    
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_ACTIVATIONS);
  return false;
}



/******************************************************************************/
AI_DECLARE_STATIC
ai_bool voice_model_configure_weights(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_weights_map(g_voice_model_weights_map, 1, params)) {
    /* Updating weights (byte) offsets */
    
    tfl_pseudo_qconst8_array.format |= AI_FMT_FLAG_CONST;
    tfl_pseudo_qconst8_array.data = AI_PTR(g_voice_model_weights_map[0] + 0);
    tfl_pseudo_qconst8_array.data_start = AI_PTR(g_voice_model_weights_map[0] + 0);
    
    tfl_pseudo_qconst9_array.format |= AI_FMT_FLAG_CONST;
    tfl_pseudo_qconst9_array.data = AI_PTR(g_voice_model_weights_map[0] + 4);
    tfl_pseudo_qconst9_array.data_start = AI_PTR(g_voice_model_weights_map[0] + 4);
    
    conv2d_7_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_7_weights_array.data = AI_PTR(g_voice_model_weights_map[0] + 8);
    conv2d_7_weights_array.data_start = AI_PTR(g_voice_model_weights_map[0] + 8);
    
    conv2d_7_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_7_bias_array.data = AI_PTR(g_voice_model_weights_map[0] + 520);
    conv2d_7_bias_array.data_start = AI_PTR(g_voice_model_weights_map[0] + 520);
    
    conv2d_9_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_9_weights_array.data = AI_PTR(g_voice_model_weights_map[0] + 648);
    conv2d_9_weights_array.data_start = AI_PTR(g_voice_model_weights_map[0] + 648);
    
    conv2d_9_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_9_bias_array.data = AI_PTR(g_voice_model_weights_map[0] + 33416);
    conv2d_9_bias_array.data_start = AI_PTR(g_voice_model_weights_map[0] + 33416);
    
    gemm_12_weights_array.format |= AI_FMT_FLAG_CONST;
    gemm_12_weights_array.data = AI_PTR(g_voice_model_weights_map[0] + 33672);
    gemm_12_weights_array.data_start = AI_PTR(g_voice_model_weights_map[0] + 33672);
    
    gemm_12_bias_array.format |= AI_FMT_FLAG_CONST;
    gemm_12_bias_array.data = AI_PTR(g_voice_model_weights_map[0] + 295816);
    gemm_12_bias_array.data_start = AI_PTR(g_voice_model_weights_map[0] + 295816);
    
    gemm_13_weights_array.format |= AI_FMT_FLAG_CONST;
    gemm_13_weights_array.data = AI_PTR(g_voice_model_weights_map[0] + 296072);
    gemm_13_weights_array.data_start = AI_PTR(g_voice_model_weights_map[0] + 296072);
    
    gemm_13_bias_array.format |= AI_FMT_FLAG_CONST;
    gemm_13_bias_array.data = AI_PTR(g_voice_model_weights_map[0] + 296584);
    gemm_13_bias_array.data_start = AI_PTR(g_voice_model_weights_map[0] + 296584);
    
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_WEIGHTS);
  return false;
}


/**  PUBLIC APIs SECTION  *****************************************************/


AI_DEPRECATED
AI_API_ENTRY
ai_bool ai_voice_model_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_VOICE_MODEL_MODEL_NAME,
      .model_signature   = AI_VOICE_MODEL_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 9264144,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .params            = AI_STRUCT_INIT,
      .activations       = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}


AI_API_ENTRY
ai_bool ai_voice_model_get_report(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_VOICE_MODEL_MODEL_NAME,
      .model_signature   = AI_VOICE_MODEL_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 9264144,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .map_signature     = AI_MAGIC_SIGNATURE,
      .map_weights       = AI_STRUCT_INIT,
      .map_activations   = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}

AI_API_ENTRY
ai_error ai_voice_model_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_voice_model_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_error ai_voice_model_create_and_init(
  ai_handle* network, const ai_handle activations[], const ai_handle weights[])
{
    ai_error err;
    ai_network_params params;

    err = ai_voice_model_create(network, AI_VOICE_MODEL_DATA_CONFIG);
    if (err.type != AI_ERROR_NONE)
        return err;
    if (ai_voice_model_data_params_get(&params) != true) {
        err = ai_voice_model_get_error(*network);
        return err;
    }
#if defined(AI_VOICE_MODEL_DATA_ACTIVATIONS_COUNT)
    if (activations) {
        /* set the addresses of the activations buffers */
        for (int idx=0;idx<params.map_activations.size;idx++)
            AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_activations, idx, activations[idx]);
    }
#endif
#if defined(AI_VOICE_MODEL_DATA_WEIGHTS_COUNT)
    if (weights) {
        /* set the addresses of the weight buffers */
        for (int idx=0;idx<params.map_weights.size;idx++)
            AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_weights, idx, weights[idx]);
    }
#endif
    if (ai_voice_model_init(*network, &params) != true) {
        err = ai_voice_model_get_error(*network);
    }
    return err;
}

AI_API_ENTRY
ai_buffer* ai_voice_model_inputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    ((ai_network *)network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_inputs_get(network, n_buffer);
}

AI_API_ENTRY
ai_buffer* ai_voice_model_outputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    ((ai_network *)network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_outputs_get(network, n_buffer);
}

AI_API_ENTRY
ai_handle ai_voice_model_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_voice_model_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if (!net_ctx) return false;

  ai_bool ok = true;
  ok &= voice_model_configure_weights(net_ctx, params);
  ok &= voice_model_configure_activations(net_ctx, params);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_voice_model_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_voice_model_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}



#undef AI_VOICE_MODEL_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

