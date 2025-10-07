#include "HttpMessage.hpp"

static bool write_line(std::ostream &os, const std::string *line)
{
        if (!line[0].empty() && !line[1].empty() && !line[2].empty())
                os << line[0] << " " << line[1] << " " << line[2] << CRLF;
        return (true);
        return (false);
}

bool HttpMessage::encode_once(HttpMessage *self)
{
        static std::streampos startP = (*self).tellp();
        switch ((*self)._encoding_phase)
        {
        case HttpMessage::encoding_first_line:
                console::debug << "Encoding first line" << std::endl;
                if (write_line((*self), (*self)._first_line))
                {
                        (*self)._encoding_phase = HttpMessage::encoding_headers;
                        return (true);
                }
                break;
        case HttpMessage::encoding_headers:
                console::debug << "Encoding headers" << std::endl;
                if ((*self)._headers.is_sealed())
                {
                        // writes the headers to the raw stream
                        (*self)._headers.print((*self));
                        (*self) << CRLF;
                        (*self)._header_bytelen = (*self).tellp();
                        if ((*self)._headers.content_length() > -1)
                                (*self)._content_length = (*self)._headers.content_length();
                        (*self)._encoding_phase = HttpMessage::encoding_body;
                        return (true);
                }
                break;
        case HttpMessage::encoding_body:
        {
                console::debug << "Encoding body" << std::endl;

                std::stringstream schunk;

                size_t	encoded = (*self).tellp() - startP - (*self)._header_bytelen;

                console::debug
                                << "Already encoded: "
                                << encoded << "/" << (*self)._content_length
                                << std::endl;

                schunk << (*self)._body.rdbuf();
                if (!schunk.str().empty())
                {
                        (*self) << schunk.str();
                        return (true);
                }
                else
                {
                }
                if (encoded == (*self)._content_length)
                {
                        (*self)._encoding_phase = HttpMessage::encoding_done;
                        return (true);
                }
                console::debug << "Body not avail" << std::endl;
                break;
        }
        default:
                break;
        }
        return (false);
}
