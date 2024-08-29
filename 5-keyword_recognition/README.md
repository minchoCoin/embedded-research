# keyword recognition
keyword recognition using stm32 and mic

keyword: 'right' 'left' 'stop' 'up' 'no' 'go' 'down' 'yes'

this code is still constructing...

# components
- board: [NUCLEO-F429ZI](https://www.st.com/en/evaluation-tools/nucleo-f429zi.html)
- mic: MAX9814

# using library and IDE
- data preprocessing and making model
    - enviornment: google Colab
    - data preprocessing(stft): librosa
    - model training: tensorflow
- stm32
    - IDE: STM32CubeIDE (with STM32F4xx_HAL_Driver)
    - stm32 AI Library: STM32 X.Cube-AI(8.1.0)
    - stm32 FFT Library: CMSIS-DSP Library(1.4.0)
# references
- https://www.tensorflow.org/tutorials/audio/simple_audio?hl=ko
- https://blog.naver.com/PostView.naver?blogId=mapes_khkim&logNo=221878153123
- https://m.blog.naver.com/mapes_khkim/221878162225
- https://wikidocs.net/book/7512
- http://kocw-n.xcache.kinxcdn.com/data/document/2023/shinhan/leesangrok0218/5.pdf
- https://community.st.com/t5/stm32-mcus/how-to-install-x-cube-ai-through-stm32cubemx/ta-p/585776
- https://www.st.com/resource/en/user_manual/dm00570145-getting-started-with-x-cube-ai-expansion-package-for-artificial-intelligence-ai-stmicroelectronics.pdf
- https://www.st.com/resource/en/user_manual/um1974-stm32-nucleo144-boards-mb1137-stmicroelectronics.pdf
- install j-link driver for stm32F429 Nucleo-144
	- https://www.segger.com/downloads/jlink#J-LinkSoftwareAndDocumentationPack

- https://make.e4ds.com/contest/contest_quest_view.asp?ctidx=7&step=6&atidx=539
- https://www.digikey.kr/en/maker/projects/tinyml-getting-started-with-stm32-x-cube-ai/f94e1c8bfc1e4b6291d0f672d780d2c0
- https://github.com/Szu-Chi/Implement-MNIST-Handwritten-Digit-Classification-on-MCU/tree/master
- https://wiki.st.com/stm32mcu/wiki/AI:X-CUBE-AI_support_of_ONNX_and_TensorFlow_quantized_models
- https://www.st.com/en/embedded-software/x-cube-ai.html#documentation
- https://minchocoin.github.io/categories/stm32f107vc
- https://www.stm32wrobotyce.pl/2022/01/25/wykrywanie-gestow-1d-analogowy-czujnik-sharp-i-stm32cube-ai/
- https://community.st.com/t5/stm32cubeide-mcus/stm32cubeide-library-issues/td-p/667593
- https://www.st.com/resource/en/application_note/an4841-digital-signal-processing-for-stm32-microcontrollers-using-cmsis-stmicroelectronics.pdf
- https://wiki.st.com/stm32mcu/wiki/Getting_started_with_ADC
- https://usermanual.wiki/Document/STM32ARMMANUALtrang1875.1008118776.pdf
- https://m.blog.naver.com/PostView.naver?blogId=kim1417&logNo=221993809231

