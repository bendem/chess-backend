#include "chess.hpp"
#include "commands.hpp"
#include "protocol.hpp"

namespace chess {

void init(protocol& proto) {
    proto.new_registration(command_registration {
        "list_commands",
        "List all available commands",
        {},
        {},
        [&proto](const json& j, board& b) -> json {
            std::vector<json> json_commands;
            json_commands.reserve(proto.registrations().size());

            for (const auto& registration : proto.registrations()) {
                const std::vector<filter>& filters = registration.second.filters;
                std::vector<json> json_filters;
                json_filters.reserve(filters.size());

                for(auto filter : filters) {
                    json_filters.emplace_back(json {
                        { "field", filter.field },
                        { "description", filter.description },
                    });
                }

                json_commands.emplace_back(json {
                    { "name", registration.first },
                    { "description", registration.second.description },
                    { "required_fields", registration.second.required_fields },
                    { "filters",  json_filters },
                });
            }

            return json {
                { "status", "ok" },
                { "commands", json_commands }
            };
        }
    });



    proto.new_registration(command_registration {
        "reset",
        "Resets the state of the game",
        {},
        {},
        [](const json& j, board& b) -> json {
            b = starting_board();

            return {
                { "status", "ok" }
            };
        }
    });

    proto.new_registration(command_registration {
        "unserialize",
        "Loads the provided board in the specified format as the current board to work on",
        { "value", "format" },
        {
            type_filter("value", "string"),
            any_filter("format", { "pgn", "base-64" }),
        },
        [](const json& j, board& b) -> json {
            // NYI
            return {};
        }
    });

    proto.new_registration(command_registration {
        "serialize",
        "Serializes the current board in the specified format",
        { "format" },
        {
            any_filter("format", { "pgn", "base-64" })
        },
        [](const json& j, board& b) -> json {
            // NYI
            return {};
        }
    });

    proto.new_registration(command_registration {
        "generate_moves",
        "Generates a list of all the available moves for the specified coordinates",
        { "x", "y" },
        {
            range_filter("x", 0, 7),
            range_filter("y", 0, 7),
        },
        [](const json& j, board& b) -> json {
            // NYI
            return {};
        }
    });

    proto.new_registration(command_registration {
        "move",
        "Moves a piece on the board",
        { "from_x", "from_y", "to_x", "to_y" },
        {
            range_filter("from_x", 0, 7),
            range_filter("from_y", 0, 7),
            range_filter("to_x", 0, 7),
            range_filter("to_y", 0, 7),
        },
        [](const json& j, board& b) -> json {
            // NYI
            return {};
        }
    });

    proto.new_registration(command_registration {
        "check_move",
        "Checks if the provided move is a valid move",
        { "from_x", "from_y", "to_x", "to_y" },
        {
            range_filter("from_x", 0, 7),
            range_filter("from_y", 0, 7),
            range_filter("to_x", 0, 7),
            range_filter("to_y", 0, 7),
        },
        [](const json& j, board& b) -> json {
            // NYI
            return {};
        }
    });

    proto.new_registration(command_registration {
        "exit",
        "Exits the program",
        {},
        {},
        [](const json& j, board& b) -> json {
            return {};
        }
    });
}

}
