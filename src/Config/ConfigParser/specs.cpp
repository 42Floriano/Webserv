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

#include "ConfigParser.hpp"
#include <map>

static std::map<std::string, FieldSpec> create_contextSpecs(void);
static std::map<std::string, FieldSpec> create_directiveSpecs(void);

const ConfigParser::Specs ConfigParser::_directiveSpecs =
        create_directiveSpecs();
const ConfigParser::Specs ConfigParser::_contextSpecs = create_contextSpecs();

/* --- Specs ---------------------------------------------------------------- */

static std::map<std::string, FieldSpec> create_contextSpecs()
{
        std::map<std::string, FieldSpec> m;
        m.insert(std::make_pair(
                         "server", FieldSpec(0, 0, std::set<std::string>(), "string", GLOBAL)));
        m.insert(std::make_pair(
                         "location", FieldSpec(1, 1, std::set<std::string>(), "string", SERVER)));
        return m;
}

static std::map<std::string, FieldSpec> create_directiveSpecs()
{

        std::map<std::string, FieldSpec> m;
        std::set<std::string> on_off;
        std::set<std::string> http_methods;

        on_off.insert("on");
        on_off.insert("off");
        http_methods.insert("GET");
        http_methods.insert("POST");
        http_methods.insert("DELETE");

        m.insert(std::make_pair(
                         "listen", FieldSpec(1, 1, std::set<std::string>(), "string", SERVER)));
        m.insert(std::make_pair(
                         "host", FieldSpec(1, 1, std::set<std::string>(), "string", SERVER)));
        m.insert(
                std::make_pair("server_name", FieldSpec(1, 1, std::set<std::string>(),
                                "string", SERVER)));
        m.insert(
                std::make_pair("upload_filename_header", FieldSpec(1, 1,
                                std::set<std::string>(),
                                "string", LOCATION)));
        m.insert(
                std::make_pair("cgi_extension", FieldSpec(1, 1, std::set<std::string>(),
                                "string", LOCATION)));
        m.insert(std::make_pair("cgi_path", FieldSpec(1, 1, std::set<std::string>(),
                                "string", LOCATION)));
        m.insert(std::make_pair(
                         "root", FieldSpec(1, 1, std::set<std::string>(), "string", BOTH)));
        m.insert(std::make_pair(
                         "index", FieldSpec(1, 999, std::set<std::string>(), "string", LOCATION)));
        m.insert(std::make_pair("methods",
                                FieldSpec(1, 3, http_methods, "string", LOCATION)));
        m.insert(std::make_pair(
                         "return", FieldSpec(2, 2, std::set<std::string>(), "string", LOCATION)));
//        m.insert(std::make_pair(
//                         "type", FieldSpec(1, 1, std::set<std::string>(), "string", LOCATION)));
//        m.insert(std::make_pair(
//                         "default_mime_types",
//                         FieldSpec(1, 1, std::set<std::string>(), "string", LOCATION)));
//        m.insert(std::make_pair(
//                         "timeout", FieldSpec(1, 1, std::set<std::string>(), "int", LOCATION)));
//        m.insert(std::make_pair("server_tokens",
//                                FieldSpec(1, 1, on_off, "bool", LOCATION)));
        m.insert(std::make_pair("error_page", FieldSpec(2, 2, std::set<std::string>(),
                                "string", SERVER)));
        m.insert(
                std::make_pair("max_body_size",
                               FieldSpec(1, 1, std::set<std::string>(), "int", SERVER)));
//        m.insert(std::make_pair("redirect", FieldSpec(2, 2, std::set<std::string>(),
//                                "string", LOCATION)));
//        m.insert(
//                std::make_pair("autoindex", FieldSpec(1, 1, on_off, "bool", LOCATION)));
//        m.insert(std::make_pair("upload_enable",
//                                FieldSpec(1, 1, on_off, "bool", LOCATION)));
        return m;
}
