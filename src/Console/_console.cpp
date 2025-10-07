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

#include <fstream>
#include "color.hpp"
#include "_console.hpp"

#define	__red "\033[1;31m"
#define	__green "\033[1;32m"
#define	__yellow "\033[1;33m"
#define	__blue "\033[1;34m"
#define	__magenta "\033[1;35m"
#define	__cyan "\033[1;36m"
#define	__dflt "\033[1;0m"

ConsoleBuffer console::info_buff(
        //*(new std::ofstream("info.log")),
        std::cout,
        __yellow "info" __dflt
);

ConsoleBuffer console::debug_buff(
        //*(new std::ofstream("debug.log")),
        std::cout,
        __blue "debug" __dflt
);

ConsoleBuffer console::error_buff(
        // *(new std::ofstream("error.log")),
        std::cerr,
        __red "error" __dflt
);

Console				console::info(&console::info_buff);
Console				console::debug(&console::debug_buff);
Console				console::error(&console::error_buff);
