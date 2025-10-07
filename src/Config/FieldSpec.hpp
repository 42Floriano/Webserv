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

#ifndef FIELDSPEC_HPP
#define FIELDSPEC_HPP
#include <cstddef>
#include <set>
#include <string>

enum Scope
{
        GLOBAL,
        SERVER,
        LOCATION,
        BOTH
};

struct FieldSpec
{
        size_t minParams;
        size_t maxParams;
        std::set<std::string> allowedValues;
        std::string type;
        Scope scope;

        FieldSpec(size_t, size_t, const std::set<std::string>&, const std::string&,
                  Scope);
};

#endif
