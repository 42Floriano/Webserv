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

#ifndef AUTO_INDEX_GEN_HPP
# define AUTO_INDEX_GEN_HPP

#include <dirent.h>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <sys/stat.h>

class AutoIndexGen
{

public:
        enum /* methods */
        {
                GET,
                POST,
                DELETE,
        };

private:
        std::ostringstream	_label;

public:
        AutoIndexGen(const std::string &dirPath);
        ~AutoIndexGen(void);

        void		generateIndex(int method, const std::string &uploadDirPath);
        std::string	findMethod(int method);
};

#endif
