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

int HttpMessage::decode_trailers(HttpMessage *self, const std::string &buf)
{

        try
        {
                self->_trailers.parse(buf);
        }
        catch (const std::exception &e)
        {
                throw std::runtime_error(std::string("Malformed HTTP trailer line: ") +
                                         e.what());
        }
        if (self->_headers.is_sealed())
        {
                return (HttpMessage::decoding_done);
        }
        return (HttpMessage::decoding_trailers);
}
