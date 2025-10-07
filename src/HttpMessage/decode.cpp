/*

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU Affero General Public License as
 published by the Free Software Foundation, either version 3 of the
 License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Affero General Public License for more details.

 You should have received a copy of the GNU Affero General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

#include "Console.hpp"
#include "HttpMessage.hpp"

void HttpMessage::decode(HttpMessage &msg, int stop_at)
{
        console::debug << "--- DECODING LOOP START ---" << std::endl;
        console::debug << "[current phase: " << msg._decoding_phase << "]" << std::endl;
        ++console::debug;
        try
        {
                while (HttpMessage::decode_once(&msg) && msg._decoding_phase < stop_at)
                        continue;
        }
        catch (const std::exception &e)
        {
                console::error << "Http decoding failed: " << e.what() << std::endl;
                throw;
        }
        --console::debug;
        console::debug << "[current phase: " << msg._decoding_phase << "]" << std::endl;
        console::debug << "--- DECODING LOOP END ---\n" << std::endl;
}
