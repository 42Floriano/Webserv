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
#include <algorithm> // for std::equal
#include <map>
#include <string>
#include <sys/stat.h>
#include "ResponseHandler.hpp"

static bool	ends_with(const std::string& value, const std::string& ending)
{
        if (ending.size() > value.size())
                return false;
        return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}



static std::map<std::string, std::string>	init_dflt_mime();
static std::map<std::string, std::string>	dflt_mime = init_dflt_mime();

static std::map<std::string, std::string>	init_dflt_mime()
{

        std::map<std::string, std::string> m;

        m.insert(std::make_pair(".html", "text/html"));
        m.insert(std::make_pair(".abc", "text/html"));
        m.insert(std::make_pair(".css", "text/css"));
        m.insert(std::make_pair(".js", "application/javascript"));
        m.insert(std::make_pair(".json", "application/json"));
        m.insert(std::make_pair(".png", "image/png"));
        m.insert(std::make_pair(".jpg", "image/jpeg"));
        m.insert(std::make_pair(".jpeg", "image/jpeg"));
        m.insert(std::make_pair(".gif", "image/gif"));
        m.insert(std::make_pair(".svg", "image/svg+xml"));
        m.insert(std::make_pair(".ico", "image/x-icon"));
        m.insert(std::make_pair(".woff", "font/woff"));
        m.insert(std::make_pair(".woff2", "font/woff2"));
        m.insert(std::make_pair(".ttf", "font/ttf"));
        m.insert(std::make_pair(".otf", "font/otf"));
        m.insert(std::make_pair(".eot", "application/vnd.ms-fontobject"));
        m.insert(std::make_pair(".pdf", "application/pdf"));
        m.insert(std::make_pair(".zip", "application/zip"));
        m.insert(std::make_pair(".mp3", "audio/mpeg"));
        m.insert(std::make_pair(".mp4", "video/mp4"));
        m.insert(std::make_pair(".webm", "video/webm"));
        m.insert(std::make_pair(".txt", "text/plain"));

        return m;
}

static bool	is_directory(const std::string& path)
{

        struct stat	info;
        if (stat(path.c_str(), &info) != 0)
                return false;
        return (info.st_mode & S_IFMT) == S_IFDIR;
}

const std::string	*ResponseHandler::get_mime(const std::string &path)
{

        std::map<std::string, std::string>::const_iterator	i;

        if (is_directory(path))
                throw std::runtime_error("Forbidden request : " + path + " is a directory");
        for (i = dflt_mime.begin(); i != dflt_mime.end(); ++i)
        {

                const std::string	&ext = i->first;
                const std::string	&mime_type = i->second;

                if (ends_with(path, ext))
                {
                        return &mime_type;
                }
        }
        throw std::runtime_error("Unsupported MIME type for file: " + path);
		return NULL;
}
