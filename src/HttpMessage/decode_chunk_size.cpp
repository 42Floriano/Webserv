#include "HttpMessage.hpp"

static ssize_t hex2size(const std::string &line)
{
        // TODO: Issue: not yet returning -1 on error
        ssize_t value;
        std::stringstream iss(line);
        iss >> std::hex >> value;
        return (value);
}

size_t HttpMessage::decode_chunk_size(const std::string &chunk)
{

        ssize_t size = static_cast<size_t>(hex2size(chunk));

        if (size < 0)
        {
                throw std::runtime_error("Negative chunk size encountered");
        }

        return (size);
}
