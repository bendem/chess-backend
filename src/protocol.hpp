#ifndef CHESS_BACKEND_PROTOCOL_HPP
#define CHESS_BACKEND_PROTOCOL_HPP

#include <cstddef>
#include <iostream>
#include <memory>
#include <string>

#include "board.hpp"
#include "json.hpp"


namespace chess {

using nlohmann::json;

enum class command_type {
    INVALID, RESET, UNSERIALIZE, SERIALIZE, GENERATE, MOVE, CHECK, EXIT
};

const std::map<enum command_type, std::string> command_type_to_string = {
    { command_type::RESET, "reset" },
    { command_type::UNSERIALIZE, "unserialize" },
    { command_type::SERIALIZE, "serialize" },
    { command_type::GENERATE, "generate" },
    { command_type::MOVE, "move" },
    { command_type::CHECK, "check" },
    { command_type::EXIT, "exit" },
};

const std::map<std::string, enum command_type> string_to_command_type = {
    { "reset", command_type::RESET },
    { "unserialize", command_type::UNSERIALIZE },
    { "serialize", command_type::SERIALIZE },
    { "generate", command_type::GENERATE },
    { "move", command_type::MOVE },
    { "check", command_type::CHECK },
    { "exit", command_type::EXIT },
};

const std::map<enum command_type, std::vector<std::string>> required_parameters = {
    { command_type::UNSERIALIZE, { "format", "value" } },
    { command_type::SERIALIZE, { "format" } },
    { command_type::GENERATE, { "x", "y" } },
    { command_type::MOVE, { "from_x", "from_y", "to_x", "to_y" } },
    { command_type::CHECK, { "from_x", "from_y", "to_x", "to_y" } },
};

enum class format {
    PNG, BASE64
};

const std::map<enum format, std::string> format_to_string = {
    { format::PNG, "png" },
    { format::BASE64, "base64" },
};


enum class response_status {
    OK, NOK
};

const std::map<enum response_status, std::string> response_status_to_string = {
    { response_status::OK, "ok" },
    { response_status::NOK, "nok" },
};


enum class error_type {
    NONE, INVALID_JSON, INVALID_COMMAND, INVALID_TYPE, MISSING_FIELD
};

const std::map<enum error_type, std::string> error_type_to_string = {
    { error_type::NONE, "none" },
    { error_type::INVALID_JSON, "invalid_json" },
    { error_type::INVALID_COMMAND, "invalid_command" },
    { error_type::INVALID_TYPE, "invalid_type" },
    { error_type::MISSING_FIELD, "missing_field" },
};



struct command {
    const enum command_type command_type;
    const nlohmann::json json;

    command() : command_type(command_type::INVALID), json() {}
    command(enum command_type command_type, const nlohmann::json& json)
        : command_type(command_type), json(json) {}
};


class protocol {
    std::istream& input;
    std::ostream& output;

    command error(error_type, const std::string& error_msg);

public:
    protocol(std::istream& is, std::ostream& os) : input(is), output(os) {}

    command next_command();

};


}

#endif
