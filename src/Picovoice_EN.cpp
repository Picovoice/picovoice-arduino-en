/*
    Copyright 2021 Picovoice Inc.

    You may not use this file except in compliance with the license. A copy of the license is located in the "LICENSE"
    file accompanying this source.

    Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
    an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
    specific language governing permissions and limitations under the License.
*/

#include <stdint.h>

#include "Picovoice_EN.h"

#if defined(ARDUINO_ARDUINO_NANO33BLE)

#define UUID_ADDRESS (0x10000060)
#define UUID_SIZE (8)

#else

#error “This library only supports Arduino Nano 33 BLE.”

#endif

const uint8_t *pv_get_uuid(void) {
    return (const uint8_t *) UUID_ADDRESS;
}

uint32_t pv_get_uuid_size(void) {
    return UUID_SIZE;
}
