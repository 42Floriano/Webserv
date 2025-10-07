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

#ifndef HTTPMESSAGE_HPP
#define HTTPMESSAGE_HPP

#include "Console.hpp"
#include "HttpHeaders.hpp"
#include "Socket.hpp"
#include <exception>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#define CRLF "\r\n"

struct HttpMessage : public std::iostream
{
        enum /* decoding phases */
        {
                decoding_first_line,
                decoding_header,
                decoding_body,
                decoding_chunk_size,
                decoding_chunk_data,
                decoding_trailers,
                decoding_done,
        };

        enum /* encoding phases */
        {
                encoding_first_line,
                encoding_headers,
                encoding_body,
                encoding_chunk_size,
                encoding_chunk_data,
                encoding_done,
        };

        static bool getline(std::istream &is, std::string &dst);
        static bool getchunk(std::istream &is, std::string &dst);

        static void decode(HttpMessage &msg, int stop_at = HttpMessage::decoding_done);
        static bool	decode_once(HttpMessage *self);

        static int	decode_first_line(HttpMessage *self, const std::string &line);
        static int	decode_headers(HttpMessage *self, const std::string &line);
        static int	decode_trailers(HttpMessage *self, const std::string &line);
        static size_t decode_chunk_size(const std::string &chunk);

        static void encode(HttpMessage &msg);
        static bool	encode_once(HttpMessage *msg);

        HttpMessage(std::stringbuf &s);
        ~HttpMessage(void);

        std::string			_first_line[3];
        HttpHeaders			_headers;
        std::stringstream	_body;
        HttpHeaders			_trailers;

        std::string _buffer;
        int _decoding_phase;
        int _encoding_phase;
        bool _chunked;
        size_t current_body_size;
        size_t _content_length;
        size_t _header_bytelen;
};

#endif
