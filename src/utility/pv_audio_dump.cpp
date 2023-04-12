/*
    Copyright 2021-2023 Picovoice Inc.

    You may not use this file except in compliance with the license. A copy of the license is located in the "LICENSE"
    file accompanying this source.

    Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
    an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
    specific language governing permissions and limitations under the License.
*/
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "LibPrintf.h"

#define pv_min(a,b) ((a) < (b) ? (a) : (b))

#define PV_AUDIO_DUMP_DURATION_SEC      (3)
#define PV_AUDIO_REC_AUDIO_FREQUENCY    (16000U)
#define PV_AUDIO_DUMP_BUFFER_SIZE   ((uint32_t)(PV_AUDIO_DUMP_DURATION_SEC * PV_AUDIO_REC_AUDIO_FREQUENCY))

static int16_t dump_buffer[PV_AUDIO_DUMP_BUFFER_SIZE];
static uint32_t dump_index;

void pv_audio_dump_init(void) {
    dump_index = 0;
    memset(dump_buffer, 0, sizeof(dump_buffer));
}

bool pv_audio_dump_add(const int16_t *buffer, uint32_t buffer_size) {
    uint32_t max_index = pv_min(buffer_size, (PV_AUDIO_DUMP_BUFFER_SIZE - dump_index));
    for (uint32_t i = 0; i < max_index; i++) {
        dump_buffer[dump_index++] = buffer[i];
    }
    return (dump_index == PV_AUDIO_DUMP_BUFFER_SIZE);
}

void pv_audio_dump_reset_buffer(void) {
    dump_index = 0;
    memset(dump_buffer, 0, sizeof(dump_buffer));
}

void pv_audio_dump_start(void) {
    for (uint32_t i = 0; i < PV_AUDIO_DUMP_BUFFER_SIZE; i++) {
        printf("%.4x\n", ((uint16_t) dump_buffer[i]));
    }
    pv_audio_dump_reset_buffer();
}
