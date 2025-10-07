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
 along with self program.  If not, see <https://www.gnu.org/licenses/>.

*/

#include "HttpMessage.hpp"

int HttpMessage::decode_first_line(HttpMessage *self, const std::string &line)
{

        size_t start = 0;
        size_t i = 0;
        for (size_t end = 0; end < line.size(); end++)
        {
                if (line[end] == ' ' || end == line.size() - 1)
                {
                        size_t len = (end == line.size() - 1) ? (end - start + 1) : (end - start);
                        self->_first_line[i++] = line.substr(start, len);
                        start = end + 1;
                        if (i > 3)
                                break;
                }
        }
        if (i != 3)
        {
                throw std::runtime_error("Malformed HTTP request line");
        }
        return HttpMessage::decoding_header;
}
