#ifndef CHESS_BACKEND_PROTOCOL_HPP
#define CHESS_BACKEND_PROTOCOL_HPP

#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "board.hpp"
#include "json.hpp"
#include "commands.hpp"


namespace chess {

using nlohmann::json;

struct filter {
    std::string field;
    std::string error;
    std::string description;
    std::function<bool(const json&)> predicate;
};

struct command_registration {
    std::string name;
    std::string description;
    std::vector<std::string> required_fields;
    std::vector<filter> filters;
    std::function<json(const json&, board&)> action;
};

filter range_filter(const std::string& name, int from, int to);
filter type_filter(const std::string& name, const std::string& type);
filter any_filter(const std::string& name, const std::unordered_set<std::string>& values);


class protocol {
    typedef std::vector<std::pair<std::string, command_registration>> command_map;
    std::istream& input;
    std::ostream& output;
    bool debug;
    command_map commands;

    bool error(const std::string&, const std::string&);

public:
    protocol(std::istream& is, std::ostream& os, bool debug = false) : input(is), output(os), debug(debug) {
        init(*this);
    }

    protocol& new_registration(const command_registration&);
    const command_map& registrations() const;

    bool handle_next_command(board&);

};


}

#endif
