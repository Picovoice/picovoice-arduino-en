/*
    Copyright 2021 Picovoice Inc.

    You may not use this file except in compliance with the license. A copy of the license is located in the "LICENSE"
    file accompanying this source.

    Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
    an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
    specific language governing permissions and limitations under the License.
*/

#include <Picovoice_EN.h>
#include <stdbool.h>

#include "utility/pv_audio_dump.h"

void setup() {
    Serial.begin(9600);
    while (!Serial);

    pv_status_t status = pv_audio_rec_init();
    if (status != PV_STATUS_SUCCESS) {
        Serial.print("Audio init failed with ");
        Serial.println(pv_status_to_string(status));
        while (1);
    }

    pv_audio_dump_init();

    Serial.println("Send anything to start recording:");
}

void loop()
{
    if (Serial.available() > 0) {
        Serial.read();
        Serial.println("Recording...");
        bool is_dump_buffer_full = false;
        while (!is_dump_buffer_full) {
            const int16_t *buffer = pv_audio_rec_get_new_buffer();
            if (buffer) {
                is_dump_buffer_full = pv_audio_dump_add(buffer, 512U);
            }
        }
        pv_audio_dump_start();
    }
}
