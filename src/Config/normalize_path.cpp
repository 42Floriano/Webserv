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

#include <sstream>
#include <string>
#include <vector>

std::string	normalize_path(const std::string& path)
{

        std::vector<std::string>	parts;
        std::stringstream			ss(path);
        std::string					segment;

        while (std::getline(ss, segment, '/'))
        {
                if (segment.empty() || segment == ".")
                        continue;
                else if (segment == "..")
                {
                        if (!parts.empty())
                                parts.pop_back();
                }
                else
                        parts.push_back(segment);
        }

        if (parts.empty())
                return "/";

        std::string	normalizedPath = "/";
        for (std::vector<std::string>::size_type i = 0; i < parts.size(); ++i)
        {
                normalizedPath += parts[i];
                if (i < parts.size() - 1)
                        normalizedPath += "/";
        }

        if (path[path.length() - 1] == '/' && normalizedPath != "/")
                normalizedPath += "/";

        return normalizedPath;
}
