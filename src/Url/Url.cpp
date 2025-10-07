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

#include <string>
#include <stdexcept>
#include <iostream>
#include "Url.hpp"

Url&	Url::operator=(const std::string &url)
{
        this->std::string::operator=(url);
        this->protocol = Url::get_protocol(url);
        this->hier = Url::get_hier(url);
        this->query = Url::get_query(url);
        this->fragment = Url::get_fragment(url);
        return (*this);
}

std::ostream& operator<<(std::ostream &os, const Url &url)
{
        url.print(os);
        return os;
}

Url::Url(const std::string &url):
        std::string(url),
        protocol(Url::get_protocol(url)),
        hier(Url::get_hier(url)),
        query(Url::get_query(url)),
        fragment(Url::get_fragment(url))
{
        console::debug << "Creating url object from " << url << std::endl;
        this->print(console::debug);
}

void	Url::print(std::ostream &os) const
{

        os << "Url Object:" << std::endl;
        os << "> protocol: " << protocol << std::endl;
        os << "> hier: " << hier << std::endl;
        os << "> query: " << query << std::endl;
        os << "> fragment: " << fragment << std::endl;
        os << std::endl;
}

static int hexCharToInt(char c)
{

        if ('0' <= c && c <= '9') return c - '0';
        if ('a' <= c && c <= 'f') return c - 'a' + 10;
        if ('A' <= c && c <= 'F') return c - 'A' + 10;
        return -1;
}

std::string Url::decode(const std::string& str)
{

        std::string result;
        result.reserve(str.length());

        for (std::size_t i = 0; i < str.length(); ++i)
        {
                char c = str[i];

                if (c == '%' && i + 2 < str.length())
                {
                        int hi = hexCharToInt(str[i + 1]);
                        int lo = hexCharToInt(str[i + 2]);

                        if (hi != -1 && lo != -1)
                        {
                                result += static_cast<char>((hi << 4) | lo);
                                i += 2;
                        }
                        else
                        {
                                result += '%';
                        }
                }
                else if (c == '+')
                {
                        result += ' ';
                }
                else
                {
                        result += c;
                }
        }
        return result;
}

std::string Url::encode(const std::string& str)
{
        (void) str;
        throw std::runtime_error("Url::encode not implemented");
}

std::string Url::get_query(const std::string &url)
{
        size_t	query_start = url.find('?');
        size_t	query_end = url.find('#');
        if (query_start == std::string::npos)
                return std::string();
        if (query_end == std::string::npos)
                return url.substr(query_start + 1);
        return url.substr(query_start + 1, query_end - query_start - 1);
}

std::string	Url::get_fragment(const std::string &url)
{
        size_t	fragment_start = url.find('#');
        if (fragment_start == std::string::npos)
                return std::string();
        return url.substr(fragment_start + 1, std::string::npos);
}

std::string Url::get_protocol(const std::string &url)
{
        size_t protocol_end = url.find(":");
        if (protocol_end == std::string::npos)
        {
                return std::string();
        }
        return url.substr(0, protocol_end);
}

std::string	Url::get_hier(const std::string &url)
{
        size_t hier_start = url.find(':');
        if (hier_start == std::string::npos)
        {
                hier_start = 0;
        }

        size_t hier_end = url.find('?');
        if (hier_end == std::string::npos)
        {
                hier_end = url.find('#');
                if (hier_end == std::string::npos)
                {
                        return hier_start > 0 ? url.substr(hier_start + 1) : url;
                }
        }
        return url.substr(hier_start > 0 ? hier_start + 1 : 0,
                          hier_end - hier_start);
}
