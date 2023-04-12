/*
    Copyright 2021-2023 Picovoice Inc.

    You may not use this file except in compliance with the license. A copy of the license is located in the "LICENSE"
    file accompanying this source.

    Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
    an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
    specific language governing permissions and limitations under the License.
*/

#include <stdint.h>
#include <stdlib.h>

#include "PDM.h"
#include "picovoice.h"

#define PV_AUDIO_REC_AUDIO_FREQUENCY (16000U)
#define PV_AUDIO_REC_CHANNEL_NUMBER (1)
#define PV_AUDIO_REC_RECORD_BUFFER_SIZE (512)

#define AUDIO_IN_PDM_BUFFER_SIZE (64)
#define AUDIO_IN_PCM_BUFFER_SIZE (AUDIO_IN_PDM_BUFFER_SIZE / 2)

static int16_t record_pcm_buffer[AUDIO_IN_PCM_BUFFER_SIZE];
static int16_t ping_pong_buffer[2][PV_AUDIO_REC_RECORD_BUFFER_SIZE];

static int32_t last_read_index = -1;
static int32_t read_index = 1;
static int32_t write_index = 0;
static int32_t buffer_index = 0;

struct
{
    uint32_t channel_number;
    uint32_t audio_frequency;
    uint32_t record_buffer_size;
    int16_t *record_pcm_buffer;
    bool is_recording;
} pv_audio_rec;

void pv_audio_callback() {
    int32_t available_bytes = PDM.available();
    PDM.read(record_pcm_buffer, available_bytes);
    memcpy(&ping_pong_buffer[write_index][buffer_index], record_pcm_buffer, available_bytes);
    buffer_index += (available_bytes / 2);
    if (buffer_index >= PV_AUDIO_REC_RECORD_BUFFER_SIZE) {
        read_index = write_index;
        write_index = 1 - write_index;
        buffer_index = 0;
    }
}

pv_status_t pv_audio_rec_init(void) {
    pv_audio_rec.channel_number = PV_AUDIO_REC_CHANNEL_NUMBER;
    pv_audio_rec.audio_frequency = PV_AUDIO_REC_AUDIO_FREQUENCY;
    pv_audio_rec.record_buffer_size = PV_AUDIO_REC_RECORD_BUFFER_SIZE;
    pv_audio_rec.record_pcm_buffer = record_pcm_buffer;
    PDM.onReceive(pv_audio_callback);
    PDM.setBufferSize(AUDIO_IN_PDM_BUFFER_SIZE);
    if (!PDM.begin(PV_AUDIO_REC_CHANNEL_NUMBER, PV_AUDIO_REC_AUDIO_FREQUENCY)) {
        return PV_STATUS_INVALID_STATE;
    }
    pv_audio_rec.is_recording = true;
    return PV_STATUS_SUCCESS;
}


const int16_t *pv_audio_rec_get_new_buffer(void) {
    if (read_index == -1) {
        return NULL;
    }

    if (last_read_index == read_index) {
        return NULL;
    }

    last_read_index = read_index;

    return ping_pong_buffer[read_index];
}

void pv_audio_rec_deinit(void) {
    PDM.end();
}
