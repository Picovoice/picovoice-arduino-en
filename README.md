# # Picovoice SDK for Arduino boards - English language

Made in Vancouver, Canada by [Picovoice](https://picovoice.ai)

Picovoice is an end-to-end platform for building voice products on your terms. It enables creating voice experiences similar to Alexa and Google. But it entirely runs 100% on-device. Picovoice is

- **Private:** Everything is processed offline. Intrinsically HIPAA and GDPR compliant.
- **Reliable:** Runs without needing constant connectivity.
- **Zero Latency:** Edge-first architecture eliminates unpredictable network delay.
- **Accurate:** Resilient to noise and reverberation.

## Compatibility

* Arduino Nano 33 BLE Sense

## Dependency

* LibPrintf

## Integration

1. define all the necessary variables before `setup()`:

```c
#include <Picovoice_EN.h>

pv_picovoice_t *handle = NULL;

#define MEMORY_BUFFER_SIZE ...
static uint8_t memory_buffer[MEMORY_BUFFER_SIZE] __attribute__((aligned(16));

static const uint8_t *keyword_array = ...
const float porcupine_sensitivity = 0.5f

static void wake_word_callback(void) {
    // logic to execute upon detection of wake word
}

static const uint8_t *context_array = ...
const float rhino_sensitivity = 0.75f

static void inference_callback(pv_inference_t *inference) {
    // `inference` exposes three immutable properties:
    // (1) `IsUnderstood`
    // (2) `Intent`
    // (3) `Slots`
    // ..
    pv_inference_delete(inference);
}
```

Sensitivity is the parameter that enables developers to trade miss rate for false alarm. It is a floating-point number
within [0, 1]. A higher sensitivity reduces miss rate (false reject rate) at cost of increased false alarm rate.

`handle` is an instance of Picovoice runtime engine that detects utterances of wake phrase defined in `keyword_array`. Upon detection of wake word it starts inferring user's intent from the follow-on voice command within the context defined in `context_array`. `wake_word_callback` is invoked upon the detection of wake phrase and `inference_callback` is invoked upon completion of follow-on voice command inference.

2. put the following code block inside `setup()` in order to initialize the Picovoice engine:

```c
const pv_status_t status = pv_picovoice_init(
        MEMORY_BUFFER_SIZE,
        memory_buffer,
        sizeof(keyword_array),
        keyword_array,
        porcupine_sensitivity,
        wake_word_callback,
        sizeof(context_array),
        context_array,
        rhino_sensitivity,
        inference_callback,
        &handle);

if (status != PV_STATUS_SUCCESS) {
    // error handling logic
}
```

Picovoice accepts single channel, 16-bit PCM audio. The sample rate can be retrieved using `pv_sample_rate()`. Picovoice accepts input audio in consecutive chunks (aka frames); the length of each frame can be retrieved using `pv_porcupine_frame_length()`. Inside the `loop()` function in the sketch, pass the recorded audio to the Picovoice engine:

```c
const int16_t *pcm = pv_audio_rec_get_new_buffer()
const pv_status_t status = pv_picovoice_process(handle, pcm);
if (status != PV_STATUS_SUCCESS) {
    // error handling logic
}
```

## Create Custom Wake Words & Contexts

1. Compile and upload the `Picovoice_EN/GetUUID` sketch from the `File -> Examples` menu. Copy the UUID of the board printed at the beginning of the session to the serial monitor.
2. Go to [Picovoice Console](https://console.picovoice.ai/) to create models for [Porcupine wake word engine](https://picovoice.ai/docs/quick-start/console-porcupine/) and [Rhino Speech-to-Intent engine](https://picovoice.ai/docs/quick-start/console-rhino/).
3. Select `Arm Cortex M` as the platform when training the model, and Select `Arduino Nano 33 BLE Sense` as the board type and provide the UUID of the chipset on the board.
4. Click the train button. The model is now being trained. You will be able to download it within a few hours.

### Import Custom Wake Words & Contexts

1. Download your custom voice model(s) from [Picovoice Console](https://console.picovoice.ai/).
2. Decompress the zip file. The model file is either `.ppn` for Porcupine wake word or `.rhn` for Rhino context.
3. Use [binary_to_c_array.py](https://github.com/Picovoice/picovoice-arduino-en/blob/master/extras/binary_to_c_array.py) to convert your binary models to C array format utilizing the following command: `python3 binary_to_c_array.py --binary_file_path input_binary_model --array_file_path output_c_array.txt`
4. Copy the content of `output_c_array.txt` and update the `keyword_array` and `context_array` values.