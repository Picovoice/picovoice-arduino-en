/*
    Copyright 2023 Picovoice Inc.

    You may not use this file except in compliance with the license. A copy of the license is located in the "LICENSE"
    file accompanying this source.

    Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
    an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
    specific language governing permissions and limitations under the License.
*/

#ifndef PICOVOICE_EN_H
#define PICOVOICE_EN_H

#include <stdint.h>

#include "Arduino.h"
#include "LibPrintf.h"

#include "pv_picovoice.h"
#include "utility/pv_audio_rec.h"

/**
 * Getter for boards' unique identifier (UUID)
 *
 * @return UUID.
 */
const uint8_t *pv_get_uuid(void);


/**
 * Getter for the size of the UUID.
 *
 * @return size.
 */
uint32_t pv_get_uuid_size(void);

#endif // PICOVOICE_EN_H
