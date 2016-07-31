#include <numeric>
#include "protocol.hpp"

namespace chess {

using namespace std::string_literals;

filter range_filter(const std::string& name, int from, int to) {
    return filter {
        name,
        "value_not_in_range",
        std::string("Field '") + name + "' should contain an integer between " + std::to_string(from) + " and " + std::to_string(to),
        [from, to](const json& j) {
            if(!j.is_number_integer()) {
                return false;
            }
            int value = j.get<int>();
            return value >= from && value <= to;
        }
    };
}

filter type_filter(const std::string& name, const std::string& type) {
    return filter {
        name,
        "invalid_type",
        std::string("Field '") + name + "' should contain a value of type " + type,
        [type](const json& j) {
            return (type == "string" && j.is_string())
                || (type == "number" && j.is_number())
                || (type == "integer" && j.is_number_integer())
                || (type == "unsigned" && j.is_number_unsigned())
                || (type == "float" && j.is_number_float())
                || (type == "boolean" && j.is_boolean());
        }
    };
}

filter any_filter(const std::string& name, const std::unordered_set<std::string>& values) {
    auto it = values.begin();
    std::string joined = "'" + *it + "'";
    for(++it; it != values.end(); ++it) {
        joined += ", ";
        joined += "'" + *it + "'";
    }
    return filter {
        name,
        "invalid_value",
        std::string("Field '") + name + "' should be one of " + joined,
        [values](const json& j) {
            return j.is_string()
               && values.find(j.get<std::string>()) != values.end();
        }
    };
}


protocol& protocol::new_registration(const command_registration& command) {
    commands.emplace_back(command.name, command);

    return *this;
}

const protocol::command_map& protocol::registrations() const {
    return commands;
}

bool protocol::handle_next_command(board& b) {
    std::string string;
    json j;

    if(!input || input.peek() == EOF) {
        return false;
    }

    std::getline(input, string);

    try {
        j = json::parse(string);
    } catch (std::invalid_argument& e) {
        return error("invalid_json", e.what());
    }

    if(!j.is_object()) {
        return error("invalid_json", "Provided json is not an object");
    }

    json json_command_value = j["command"];
    if(json_command_value.empty()) {
        return error("invalid_json", "Provided json does not contain a 'command' field");
    }

    if(!json_command_value.is_string()) {
        return error("invalid_command", "'command' field does not contain a string");
    }

    std::string command_name = json_command_value.get<std::string>();
    auto it_command = std::find_if(commands.begin(), commands.end(), [&command_name](const auto& value) {
        return value.first == command_name;
    });
    if(it_command == commands.end()) {
        return error("invalid_command", "No command '"s + command_name + "' found, try 'list_commands' to get a list of the commands available");
    }

    auto command = it_command->second;
    for(const auto& required_field : command.required_fields) {
        if(j[required_field].empty()) {
            return error("missing_field", "Field '"s + required_field + " missing from the provided json");
        }
    }

    for(auto& filter : command.filters) {
        if(!filter.predicate(j)) {
            return error(filter.error, filter.description);
        }
    }

    json out = command.action(j, b);
    if(out.empty()) {
        return false;
    }

    output << out.dump(debug ? 2 : -1) << std::endl;
    return true;
}

bool protocol::error(const std::string& error_type, const std::string& error_msg) {
    output << json {
        { "status", "nok" },
        { "error", error_type },
        { "error_msg", error_msg },
    }.dump(debug ? 2 : -1) << std::endl;

    return true;
}


}
