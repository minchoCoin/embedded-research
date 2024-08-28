
/**
  ******************************************************************************
  * @file    app_x-cube-ai.c
  * @author  X-CUBE-AI C code generator
  * @brief   AI program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

 /*
  * Description
  *   v1.0 - Minimum template to show how to use the Embedded Client API
  *          model. Only one input and one output is supported. All
  *          memory resources are allocated statically (AI_NETWORK_XX, defines
  *          are used).
  *          Re-target of the printf function is out-of-scope.
  *   v2.0 - add multiple IO and/or multiple heap support
  *
  *   For more information, see the embeded documentation:
  *
  *       [1] %X_CUBE_AI_DIR%/Documentation/index.html
  *
  *   X_CUBE_AI_DIR indicates the location where the X-CUBE-AI pack is installed
  *   typical : C:\Users\<user_name>\STM32Cube\Repository\STMicroelectronics\X-CUBE-AI\7.1.0
  */

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#if defined ( __ICCARM__ )
#elif defined ( __CC_ARM ) || ( __GNUC__ )
#endif

/* System headers */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include "app_x-cube-ai.h"
#include "main.h"
#include "ai_datatypes_defines.h"
#include "voice_model.h"
#include "voice_model_data.h"

/* USER CODE BEGIN includes */
#include "arm_math.h"
/* USER CODE END includes */

/* IO buffers ----------------------------------------------------------------*/

#if !defined(AI_VOICE_MODEL_INPUTS_IN_ACTIVATIONS)
AI_ALIGNED(4) ai_i8 data_in_1[AI_VOICE_MODEL_IN_1_SIZE_BYTES];
ai_i8* data_ins[AI_VOICE_MODEL_IN_NUM] = {
data_in_1
};
#else
ai_i8* data_ins[AI_VOICE_MODEL_IN_NUM] = {
NULL
};
#endif

#if !defined(AI_VOICE_MODEL_OUTPUTS_IN_ACTIVATIONS)
AI_ALIGNED(4) ai_i8 data_out_1[AI_VOICE_MODEL_OUT_1_SIZE_BYTES];
ai_i8* data_outs[AI_VOICE_MODEL_OUT_NUM] = {
data_out_1
};
#else
ai_i8* data_outs[AI_VOICE_MODEL_OUT_NUM] = {
NULL
};
#endif

/* Activations buffers -------------------------------------------------------*/

AI_ALIGNED(32)
static uint8_t pool0[AI_VOICE_MODEL_DATA_ACTIVATION_1_SIZE];

ai_handle data_activations0[] = {pool0};

/* AI objects ----------------------------------------------------------------*/

static ai_handle voice_model = AI_HANDLE_NULL;

static ai_buffer* ai_input;
static ai_buffer* ai_output;

static void ai_log_err(const ai_error err, const char *fct)
{
  /* USER CODE BEGIN log */
  if (fct)
    printf("TEMPLATE - Error (%s) - type=0x%02x code=0x%02x\r\n", fct,
        err.type, err.code);
  else
    printf("TEMPLATE - Error - type=0x%02x code=0x%02x\r\n", err.type, err.code);

  do {} while (1);
  /* USER CODE END log */
}

static int ai_boostrap(ai_handle *act_addr)
{
  ai_error err;

  /* Create and initialize an instance of the model */
  err = ai_voice_model_create_and_init(&voice_model, act_addr, NULL);
  if (err.type != AI_ERROR_NONE) {
    ai_log_err(err, "ai_voice_model_create_and_init");
    return -1;
  }

  ai_input = ai_voice_model_inputs_get(voice_model, NULL);
  ai_output = ai_voice_model_outputs_get(voice_model, NULL);

#if defined(AI_VOICE_MODEL_INPUTS_IN_ACTIVATIONS)
  /*  In the case where "--allocate-inputs" option is used, memory buffer can be
   *  used from the activations buffer. This is not mandatory.
   */
  for (int idx=0; idx < AI_VOICE_MODEL_IN_NUM; idx++) {
	data_ins[idx] = ai_input[idx].data;
  }
#else
  for (int idx=0; idx < AI_VOICE_MODEL_IN_NUM; idx++) {
	  ai_input[idx].data = data_ins[idx];
  }
#endif

#if defined(AI_VOICE_MODEL_OUTPUTS_IN_ACTIVATIONS)
  /*  In the case where "--allocate-outputs" option is used, memory buffer can be
   *  used from the activations buffer. This is no mandatory.
   */
  for (int idx=0; idx < AI_VOICE_MODEL_OUT_NUM; idx++) {
	data_outs[idx] = ai_output[idx].data;
  }
#else
  for (int idx=0; idx < AI_VOICE_MODEL_OUT_NUM; idx++) {
	ai_output[idx].data = data_outs[idx];
  }
#endif

  return 0;
}



static int ai_run(void)
{
  ai_i32 batch;

  batch = ai_voice_model_run(voice_model, ai_input, ai_output);
  if (batch != 1) {
    ai_log_err(ai_voice_model_get_error(voice_model),
        "ai_voice_model_run");
    return -1;
  }

  return 0;
}

/* USER CODE BEGIN 2 */
extern UART_HandleTypeDef huart3;
extern ADC_HandleTypeDef hadc3;
extern TIM_HandleTypeDef htim2;
ai_double input_scale = 0.10635975003242493;
ai_i32 input_zero_point = -128;

ai_double output_scale = 0.00390625;
ai_i32 output_zero_point = -128;

char* target_voices[8] = {"up","down","left","right","go","stop","yes","no"};

ai_i8 input_quantization(float value){
	return (ai_i8)(value/input_scale + input_zero_point);
}

ai_double output_dequantization(ai_i8 value){
	return (((ai_double)value -output_zero_point) * output_scale);
}

uint16_t f_argmax(ai_double* data, uint32_t len){
	uint16_t max_pos = 0;
	for(int i = 0; i < len; i++){
	    if(data[max_pos]<data[i]){
	        max_pos = i;
	    }
	  }
	return max_pos;
}
extern int adc_get_voice_end;
extern uint16_t* voice_buffer;
extern void MX_TIM2_Init(void);
#define FFT_SIZE 256
#define HOP_LENGTH 128
#define NUM_FRAMES 110
arm_cfft_instance_f32 fft_instance;
float fft_input[FFT_SIZE*2];
float fft_output[FFT_SIZE];
float stft_result[FFT_SIZE/2 + 1][NUM_FRAMES];
int buf_len_ai=0;
char buf_ai[100];
double map(uint16_t value){
	//from 0 to 4096 -> from -1 to 1
	return (double)value / 4096.0 * 2.0 -1.0;
}

void perform_stft(uint16_t *audio_buffer, uint32_t audio_length) {
	//https://blog.naver.com/alsrb968/220734218195
    arm_cfft_init_f32(&fft_instance, FFT_SIZE);

    for (int frame = 0; frame < NUM_FRAMES; frame++) {

        for (int i = 0; i < FFT_SIZE; i++) {
        	float32_t window = 0.5f * (1 - arm_cos_f32(2 * PI * i / (FFT_SIZE - 1)));//Hann window (default of librosa stft)
            fft_input[2*i] = map(audio_buffer[frame * HOP_LENGTH + i]) * window;
            fft_input[2*i+1] = 0.0f;
        }


        arm_cfft_f32(&fft_instance, fft_input, 0, 1);


        arm_cmplx_mag_f32(fft_input, fft_output, FFT_SIZE);


        for (int i = 0; i <= FFT_SIZE/2; i++) {
            stft_result[i][frame] = (float)fft_output[i];
        }
    }
    //buf_len_ai = sprintf(buf_ai,"stft end...\r\n");
      //HAL_UART_Transmit(&huart3, (uint8_t *)buf_ai, buf_len_ai, 100);
}

int acquire_and_process_data(ai_i8* data[])
{
   //fill the inputs of the c-model
	//perform_stft(voice_buffer, 16000);

	while(adc_get_voice_end!=1){

	}

	if(adc_get_voice_end == 1){

		//start preprocessing
		perform_stft(voice_buffer, 16000);
		for (int idx=0; idx < AI_VOICE_MODEL_IN_1_SIZE; idx++ )
		  {

		      data[0][idx] = input_quantization(stft_result[(int)(idx/NUM_FRAMES)][idx%NUM_FRAMES]);

		  }

	}




  return 0;
}

int post_process(ai_i8* data[])
{
   //process the predictions3

  ai_double out_deq[AI_VOICE_MODEL_OUT_1_SIZE];
  for (int idx=0; idx < AI_VOICE_MODEL_OUT_1_SIZE; idx++ )
  {
      out_deq[idx] = output_dequantization(data[0][idx]);
  }
  uint16_t index = f_argmax(out_deq,AI_VOICE_MODEL_OUT_1_SIZE);


  buf_len_ai = sprintf(buf_ai,"voice keyword: %s\r\n\r\n",target_voices[index]);
  HAL_UART_Transmit(&huart3, (uint8_t *)buf_ai, buf_len_ai, 100);
  adc_get_voice_end=0;
  //HAL_ADC_Start_IT(&hadc3);

  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
  return 0;
}
/* USER CODE END 2 */

/* Entry points --------------------------------------------------------------*/

void MX_X_CUBE_AI_Init(void)
{
    /* USER CODE BEGIN 5 */
  printf("\r\nTEMPLATE - initialization\r\n");

  ai_boostrap(data_activations0);
    /* USER CODE END 5 */
}

void MX_X_CUBE_AI_Process(void)
{
    /* USER CODE BEGIN 6 */
  int res = -1;

  printf("TEMPLATE - run - main loop\r\n");

  if (voice_model) {

    do {
      /* 1 - acquire and pre-process input data */
      res = acquire_and_process_data(data_ins);
      /* 2 - process the data - call inference engine */
      if (res == 0)
        res = ai_run();
      /* 3- post-process the predictions */
      if (res == 0)
        res = post_process(data_outs);
      HAL_Delay(1000);
    } while (res==0);
  }

  if (res) {
    ai_error err = {AI_ERROR_INVALID_STATE, AI_ERROR_CODE_NETWORK};
    ai_log_err(err, "Process has FAILED");
  }
    /* USER CODE END 6 */
}
#ifdef __cplusplus
}
#endif
