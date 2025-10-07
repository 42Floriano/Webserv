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

#include "Config.hpp"
#include "ConfigIter.hpp"

static bool starts_with(const std::string &value, const std::string &start)
{
        if (start.size() > value.size())
                return false;
        return std::equal(start.begin(), start.end(), value.begin());
}

// TODO: abstract this function
ConfigItem&	Config::match_location(const ConfigItem *self,
                                    const std::string &path)
{

        ConfigIter	it(*self);
        ConfigItem	*res = NULL;

        ConfigIter	start = ConfigIter::begin(*self, "location");
        ConfigIter	end = ConfigIter::end(*self);

        // If multiple matches, only the LAST matters
        for (it = start; it != end; ++it)
        {
                if ((*it)[0] && starts_with(path, *(*it)[0]))
                {
                        res = &(*it);
                }
        }
        if (res)
                return *res;
        throw std::runtime_error("No location match for " + path);
}
