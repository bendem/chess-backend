#include "protocol.hpp"

namespace chess {

using namespace std::string_literals;

command protocol::next_command() {
    if(!input || input.peek() == EOF) {
        return command(command_type::EXIT, {});
    }

    std::string string;
    std::getline(input, string);

    json j;
    try {
        j = json::parse(string);
    } catch (std::invalid_argument& e) {
        return error(error_type::INVALID_JSON, e.what());
    }

    if(!j.is_object()) {
        return error(error_type::INVALID_JSON, "Provided json is not an object");
    }

    json json_command_value = j["command"];
    if(json_command_value.empty()) {
        return error(error_type::INVALID_JSON, "Provided json does not contain a command field");
    }

    if(!json_command_value.is_string()) {
        return error(error_type::INVALID_COMMAND, "Command field does not contain a string");
    }

    auto it_command = string_to_command_type.find(json_command_value.get<std::string>());
    if(it_command == string_to_command_type.end()) {
        return error(error_type::INVALID_COMMAND, "Command field contains an invalid value");
    }

    auto command_type = it_command->second;
    auto it_params = required_parameters.find(command_type);
    if(it_params != required_parameters.end()) {
        for(auto& param : it_params->second) {
            if(j[param].empty()) {
                return error(error_type::MISSING_FIELD, "Field '"s + param + "' missing from the provided json");
            }
        }
    }

    return command(command_type, j);
}

command protocol::error(enum error_type error_type, const std::string& error_msg) {
    output << json {
        { "status", response_status_to_string.at(response_status::NOK) },
        { "error", error_type_to_string.at(error_type) },
        { "error_msg", error_msg },
    }.dump() << std::endl;

    return {};
}


}
