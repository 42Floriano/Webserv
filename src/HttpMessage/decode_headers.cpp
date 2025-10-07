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

int HttpMessage::decode_headers(HttpMessage *self, const std::string &buf)
{

        try
        {
                self->_headers.parse(buf);
        }
        catch (const std::exception &e)
        {
                throw std::runtime_error(std::string("Malformed HTTP header line: ") +
                                         e.what());
        }

        if (self->_headers.is_sealed())
        {
                const std::string	*transfer_encoding;

                transfer_encoding = self->_headers.get("Transfer-Encoding");
                if (transfer_encoding && *transfer_encoding  == "chunked")
                {
                        self->_content_length = -1;
                        return HttpMessage::decoding_chunk_size;
                }
                else
                {
                        if (self->_headers.get("Content-Length"))
                        {
                                std::stringstream lenstr(*self->_headers.get("Content-Length"));
                                lenstr >> self->_content_length;
                                return HttpMessage::decoding_body;
                        }
                        else
                        {
                                // TODO: if there is no content length we should read
                                // until disconnection
                                return HttpMessage::decoding_done;
                        }
                }
        }
        return HttpMessage::decoding_header;
}
