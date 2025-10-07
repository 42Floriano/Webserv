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

#include <cstdlib>
#include "Console.hpp"
#include "HttpMessage.hpp"

typedef std::map<std::string, std::string> str_map;

void HttpMessage::encode(HttpMessage &msg)
{
        console::debug << "--- ENCODING LOOP START ---" << std::endl;
        console::debug << "[current phase: " << msg._encoding_phase << "]" << std::endl;
        ++console::debug;

        while (HttpMessage::encode_once(&msg)
                        && msg._encoding_phase != HttpMessage::decoding_done)
        {
                continue;
        }

        --console::debug;
        console::debug << "[current phase: " << msg._encoding_phase << "]" << std::endl;
        console::debug << "--- ENCODING LOOP END ---\n" << std::endl;
}




