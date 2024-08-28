/**
  ******************************************************************************
  * @file    voice_model.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Fri Aug  9 16:08:00 2024
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
#define AI_VOICE_MODEL_MODEL_SIGNATURE     "bb9f8c3671de3a05ff717ab6262abc20"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Fri Aug  9 16:08:00 2024"

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
  serving_default_keras_tensor_920_output_array, AI_ARRAY_FORMAT_S8|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 14080, AI_STATIC)
/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  serving_default_keras_tensor_920_0_conversion_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 14080, AI_STATIC)
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
AI_INTQ_INFO_LIST_OBJ_DECLARE(serving_default_keras_tensor_920_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.10635975003242493f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #1 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(upsample_4_1_conversion_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.10635975003242493f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #2 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(eltwise_5_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.14436142146587372f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #3 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(eltwise_6_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.14436142146587372f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #4 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_7_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.06255514174699783f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #5 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_9_pad_before_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.06255514174699783f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #6 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_9_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.05733798071742058f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #7 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_12_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.06156410649418831f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #8 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_13_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.2433251142501831f),
    AI_PACK_INTQ_ZP(-11)))

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
    AI_PACK_INTQ_SCALE(3.0142886316752993e-05f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #11 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(tfl_pseudo_qconst9_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.008035119622945786f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #12 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_7_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 32,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0013343801256269217f, 0.0034138266928493977f, 0.0017870375886559486f, 0.0015261595835909247f, 0.0025525717064738274f, 0.004528468009084463f, 0.002806656761094928f, 0.0010964259272441268f, 0.004979375749826431f, 0.0018291353480890393f, 0.0014247153885662556f, 0.0021808596793562174f, 0.0022755092941224575f, 0.0031953693833202124f, 0.0015119814779609442f, 0.0018394190119579434f, 0.0012403513537719846f, 0.004315819125622511f, 0.0020985640585422516f, 0.0019929627887904644f, 0.0012501004384830594f, 0.0032611661590635777f, 0.0019912829156965017f, 0.0032206617761403322f, 0.001968883443623781f, 0.000961931946221739f, 0.0038155887741595507f, 0.004421376157552004f, 0.0019400055753067136f, 0.003610329469665885f, 0.0037867764476686716f, 0.002118766075000167f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #13 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_9_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 64,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0022585527040064335f, 0.0034093232825398445f, 0.0031298212707042694f, 0.003428808180615306f, 0.0025773767847567797f, 0.0036637536250054836f, 0.002911883406341076f, 0.0021727397106587887f, 0.0023966371081769466f, 0.0029202750883996487f, 0.0024870496708899736f, 0.0027657405007630587f, 0.003962195012718439f, 0.0025443341583013535f, 0.004066097550094128f, 0.002773149171844125f, 0.003026335034519434f, 0.0006385258166119456f, 0.002400385681539774f, 0.002246812218800187f, 0.003496421966701746f, 0.0018630874110385776f, 0.004757390357553959f, 0.003453049575909972f, 0.004191775340586901f, 0.0026100408285856247f, 0.004277766216546297f, 0.002646984066814184f, 0.0021092318929731846f, 0.0026113216299563646f, 0.00250520883128047f, 0.0023579986300319433f, 0.0032410009298473597f, 0.0009604544611647725f, 0.0030344773549586535f, 0.0025594972539693117f, 0.004051498603075743f, 0.002273059682920575f, 0.0035091033205389977f, 0.0019245782168582082f, 0.003143932204693556f, 0.0033950163051486015f, 0.002389325527474284f, 0.002493159379810095f, 0.0009421943104825914f, 0.0031969936098903418f, 0.002304632915183902f, 0.0026154499500989914f, 0.0022720976267009974f, 0.0030167230870574713f, 0.0027677463367581367f, 0.003089576493948698f, 0.0029806778766214848f, 0.0038011176511645317f, 0.001642233575694263f, 0.002505571348592639f, 0.0030497200787067413f, 0.0026346584782004356f, 0.0024343798868358135f, 0.0027636210434138775f, 0.00241872388869524f, 0.001948654418811202f, 0.0027797401417046785f, 0.002534921048209071f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #14 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_12_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 64,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0026799780316650867f, 0.002211597515270114f, 0.002516084583476186f, 0.002382328500971198f, 0.00239525712095201f, 0.0020270433742552996f, 0.0011113162618130445f, 0.000524656381458044f, 0.0022379152942448854f, 0.0023370040580630302f, 0.002638217993080616f, 0.0023610517382621765f, 0.0024799779057502747f, 0.0006993188872002065f, 0.002206582110375166f, 0.002073977841064334f, 0.0022753209341317415f, 0.002253343816846609f, 0.0025597428902983665f, 0.002712595509365201f, 0.002079285914078355f, 0.00100999535061419f, 0.002006713068112731f, 0.0006203485536389053f, 0.0025608460418879986f, 0.0017652427777647972f, 0.0025000409223139286f, 0.002605079673230648f, 0.00224398379214108f, 0.0025501479394733906f, 0.0006843448500148952f, 0.0026551324408501387f, 0.0023019101936370134f, 0.002584504894912243f, 0.0026414082385599613f, 0.0025229882448911667f, 0.002274918369948864f, 0.002533372724428773f, 0.002006184309720993f, 0.0025651687756180763f, 0.0023085689172148705f, 0.0021645561791956425f, 0.0021964702755212784f, 0.0007237705285660923f, 0.0023010189179331064f, 0.0021245810203254223f, 0.0026695842389017344f, 0.0023769631516188383f, 0.002286723116412759f, 0.0022277699317783117f, 0.0006647153059020638f, 0.002293637255206704f, 0.002244920702651143f, 0.0009183240472339094f, 0.0030163205228745937f, 0.002700295066460967f, 0.002485994715243578f, 0.002452800516039133f, 0.0021124875638633966f, 0.002195361303165555f, 0.0019591585732996464f, 0.0006027132039889693f, 0.0022295110393315554f, 0.0007801666506566107f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #15 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_13_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 8,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003665704047307372f, 0.004187481477856636f, 0.004394914489239454f, 0.004614975303411484f, 0.004613959696143866f, 0.004223211668431759f, 0.0041125318966805935f, 0.003455504309386015f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #16 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_7_scratch1_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.06255514174699783f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #17 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_9_scratch1_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.05733798071742058f),
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
  serving_default_keras_tensor_920_output, AI_STATIC,
  3, 0x1,
  AI_SHAPE_INIT(4, 1, 110, 1, 128), AI_STRIDE_INIT(4, 1, 1, 110, 110),
  1, &serving_default_keras_tensor_920_output_array, &serving_default_keras_tensor_920_output_array_intq)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  serving_default_keras_tensor_920_0_conversion_output, AI_STATIC,
  4, 0x0,
  AI_SHAPE_INIT(4, 1, 110, 1, 128), AI_STRIDE_INIT(4, 4, 4, 440, 440),
  1, &serving_default_keras_tensor_920_0_conversion_output_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  serving_default_keras_tensor_920_0_conversion_output0, AI_STATIC,
  5, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 110, 128), AI_STRIDE_INIT(4, 4, 4, 4, 440),
  1, &serving_default_keras_tensor_920_0_conversion_output_array, NULL)

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



AI_STATIC_CONST ai_i32 nl_14_nl_params_data[] = { 2090146816, 24, -124 };
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


AI_STATIC_CONST ai_float upsample_4_scales_data[] = { 0.25, 0.2909090909090909, 1.0, 1 };
AI_ARRAY_OBJ_DECLARE(
    upsample_4_scales, AI_ARRAY_FORMAT_FLOAT,
    upsample_4_scales_data, upsample_4_scales_data, 4, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  upsample_4_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &serving_default_keras_tensor_920_0_conversion_output0),
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
  serving_default_keras_tensor_920_0_conversion_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &serving_default_keras_tensor_920_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &serving_default_keras_tensor_920_0_conversion_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  serving_default_keras_tensor_920_0_conversion_layer, 0,
  NL_TYPE, 0x0, NULL,
  nl, node_convert,
  &serving_default_keras_tensor_920_0_conversion_chain,
  NULL, &upsample_4_layer, AI_STATIC, 
)


#if (AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 296616, 1, 1),
    296616, NULL, NULL),
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 60416, 1, 1),
    60416, NULL, NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_VOICE_MODEL_IN_NUM, &serving_default_keras_tensor_920_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_VOICE_MODEL_OUT_NUM, &nl_14_output),
  &serving_default_keras_tensor_920_0_conversion_layer, 0, NULL)

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
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 60416, 1, 1),
      60416, NULL, NULL)
  ),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_VOICE_MODEL_IN_NUM, &serving_default_keras_tensor_920_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_VOICE_MODEL_OUT_NUM, &nl_14_output),
  &serving_default_keras_tensor_920_0_conversion_layer, 0, NULL)

#endif	/*(AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)*/


/******************************************************************************/
AI_DECLARE_STATIC
ai_bool voice_model_configure_activations(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_activations_map(g_voice_model_activations_map, 1, params)) {
    /* Updating activations (byte) offsets */
    
    serving_default_keras_tensor_920_output_array.data = AI_PTR(g_voice_model_activations_map[0] + 42240);
    serving_default_keras_tensor_920_output_array.data_start = AI_PTR(g_voice_model_activations_map[0] + 42240);
    
    serving_default_keras_tensor_920_0_conversion_output_array.data = AI_PTR(g_voice_model_activations_map[0] + 0);
    serving_default_keras_tensor_920_0_conversion_output_array.data_start = AI_PTR(g_voice_model_activations_map[0] + 0);
    
    upsample_4_output_array.data = AI_PTR(g_voice_model_activations_map[0] + 56320);
    upsample_4_output_array.data_start = AI_PTR(g_voice_model_activations_map[0] + 56320);
    
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
      
      .n_macc            = 9261344,
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
      
      .n_macc            = 9261344,
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

