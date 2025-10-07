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

#include <cstring>
#include "Process.hpp"

void		Process::_configure_env(void)
{

        std::map<std::string, std::string>::iterator	it = this->env.begin();
        std::map<std::string, std::string>::iterator	end = this->env.end();

        for (; it != end; it++)
        {

                char	*env_var = new char[it->first.size() + it->second.size() + 2];

                strcpy(env_var, it->first.c_str());
                strcpy(env_var + it->first.size(), "=");
                strcpy(env_var + it->first.size() + 1, it->second.c_str());
                env_var[it->first.size() + it->second.size() + 1] = 0;

                this->envp.push_back(env_var);
        }
}
