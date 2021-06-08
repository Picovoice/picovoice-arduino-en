/*
    Copyright 2021 Picovoice Inc.

    You may not use this file except in compliance with the license. A copy of the license is located in the "LICENSE"
    file accompanying this source.

    Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
    an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
    specific language governing permissions and limitations under the License.
*/

#include <Picovoice_EN.h>

void setup() {
    Serial.begin(9600);
    while (!Serial);

    const uint8_t *board_uuid = pv_get_uuid();
    Serial.print("UUID: ");
    const int32_t format_size = pv_get_uuid_size() * 4;
    char format[format_size];
    for (uint32_t i = 0; i < pv_get_uuid_size(); i++) {
        sprintf(format, " %.2x", board_uuid[i]);
        Serial.print(format);
    }
    Serial.println("\r");
}

void loop() {
}
