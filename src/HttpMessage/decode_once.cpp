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

#include "Console.hpp"
#include "HttpMessage.hpp"

bool	HttpMessage::decode_once(HttpMessage *self)
{
        console::debug << "--- decode_once START ---" << std::endl;

        switch (self->_decoding_phase)
        {

        case HttpMessage::decoding_first_line:
                console::debug << "Decoding first line:" << std::endl;
                if (HttpMessage::getline(*self, self->_buffer))
                {
                        self->_decoding_phase = HttpMessage::decode_first_line(self, self->_buffer);
                        self->_buffer.clear();
                        return true;
                }
                return false;

        case HttpMessage::decoding_header:
                console::debug << "Decoding headers:" << std::endl;
                if (HttpMessage::getline(*self, self->_buffer))
                {
                        self->_decoding_phase = HttpMessage::decode_headers(self, self->_buffer);
                        self->_buffer.clear();
                        return true;
                }
                return false;

        case HttpMessage::decoding_body:
                // TODO: if multiple request on same connection,
                // we cannot consume the full rdbuf at once, because it may
                // contain data from the next request
                // WE MUST FIX THIS
                // for now, we ALWAYS set `Connection: close` header in res
        {
                console::debug << "Decoding body:" << std::endl;
                std::streamsize avail = self->rdbuf()->in_avail();
                if (avail > 0)
                {
                        // TODO: (see above):
                        // trim + reinsert! we may read more than the body
                        std::streampos pos_before = self->_body.tellp();
                        self->_body << self->rdbuf();
                        std::streampos pos_after = self->_body.tellp();
                        self->current_body_size += pos_after - pos_before;
                        if (self->_body.str().size() >= self->_content_length
                                        && self->_content_length > 0)
                        {
                                self->_decoding_phase = HttpMessage::decoding_done;
                        }
                        return true;
                }
                return false;
        }
        case HttpMessage::decoding_chunk_size:
                console::debug << "Decoding chunk size:" << std::endl;
                if (HttpMessage::getline(*self, self->_buffer))
                {

                        size_t size = self->decode_chunk_size(self->_buffer);

                        if (size > 0)
                        {
                                self->_buffer.resize(size, 0);
                                self->_decoding_phase = decoding_chunk_data;
                        }
                        else if (size == 0)
                        {
                                self->_buffer.clear();
                                self->_decoding_phase = decoding_trailers;
                        }

                        return true;
                }
                return false;

        case HttpMessage::decoding_chunk_data:
                console::debug << "Decoding chunk data:" << std::endl;
                if (HttpMessage::getchunk(*self, self->_buffer))
                {
                        self->_decoding_phase = HttpMessage::decoding_chunk_size;
                        self->_body << self->_buffer;
                        self->_buffer.clear();
                        return true;
                }
                return false;

        case HttpMessage::decoding_trailers:
                console::debug << "Decoding trailers:" << std::endl;
                if (HttpMessage::getline(*self, self->_buffer))
                {
                        self->HttpMessage::decode_trailers(self, self->_buffer);
                        return true;
                }
                return false;

        case HttpMessage::decoding_done:
                return false;

        default:
                throw std::runtime_error("Unexpected HTTP decoding phase.");

        }
        console::debug << "--- decode_once END ---" << std::endl;
        return (false);
}
