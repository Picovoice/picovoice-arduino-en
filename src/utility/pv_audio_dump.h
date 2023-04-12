/*
    Copyright 2021-2023 Picovoice Inc.

    You may not use this file except in compliance with the license. A copy of the license is located in the "LICENSE"
    file accompanying this source.

    Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
    an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
    specific language governing permissions and limitations under the License.
*/

#ifndef PV_AUDIO_DUMP_H
#define PV_AUDIO_DUMP_H

void pv_audio_dump_init(void);
bool pv_audio_dump_add(const int16_t *buffer, uint32_t buffer_size);
void pv_audio_dump_start(void);
void pv_audio_dump_reset_buffer(void);

#endif // PV_AUDIO_DUMP_H
