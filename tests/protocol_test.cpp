#include <sstream>

#include "catch.hpp"
#include "protocol.hpp"

void assert_error(enum chess::error_type error_type, const std::string& string) {
    const chess::json j = chess::json::parse(string);
    REQUIRE(j.at("status").get<std::string>() == "nok");
    REQUIRE(chess::error_type_to_string.at(error_type) == j.at("error").get<std::string>());
}

TEST_CASE("Invalid json", "[proto]") {
    std::istringstream input(R"json([{])json");
    std::ostringstream output;
    chess::protocol proto(input, output);

    auto command = proto.next_command();
    REQUIRE(command.command_type == chess::command_type::INVALID);
    assert_error(chess::error_type::INVALID_JSON, output.str());
}

TEST_CASE("Not an object", "[proto]") {
    std::istringstream input(R"json([])json");
    std::ostringstream output;
    chess::protocol proto(input, output);

    auto command = proto.next_command();
    REQUIRE(command.command_type == chess::command_type::INVALID);
    assert_error(chess::error_type::INVALID_JSON, output.str());
}

TEST_CASE("Unknown command", "[proto]") {
    std::istringstream input(R"json({ "command": "hi" })json");
    std::ostringstream output;
    chess::protocol proto(input, output);

    auto command = proto.next_command();
    REQUIRE(command.command_type == chess::command_type::INVALID);
    assert_error(chess::error_type::INVALID_COMMAND, output.str());
}

TEST_CASE("Empty command", "[proto]") {
    std::istringstream input("");
    std::ostringstream output;
    chess::protocol proto(input, output);


    auto command = proto.next_command();
    REQUIRE(command.command_type == chess::command_type::EXIT);
}

TEST_CASE("Missing parameter", "[proto]") {
    std::istringstream input(R"json({ "command": "serialize" })json");
    std::ostringstream output;
    chess::protocol proto(input, output);

    auto command = proto.next_command();
    REQUIRE(command.command_type == chess::command_type::INVALID);
    assert_error(chess::error_type::MISSING_FIELD, output.str());
}

TEST_CASE("Correct input", "[proto]") {
    std::istringstream input(R"json({ "command": "reset" })json");
    std::ostringstream output;
    chess::protocol proto(input, output);

    auto command = proto.next_command();
    REQUIRE(command.command_type == chess::command_type::RESET);
}

TEST_CASE("Multiple inputs", "[proto]") {
    std::istringstream input(R"json({ "command": "reset" }
{ "command": "reset" })json");
    std::ostringstream output;
    chess::protocol proto(input, output);

    {
        auto command = proto.next_command();
        REQUIRE(command.command_type == chess::command_type::RESET);
    }
    {
        auto command = proto.next_command();
        REQUIRE(command.command_type == chess::command_type::RESET);
    }
    {
        auto command = proto.next_command();
        REQUIRE(command.command_type == chess::command_type::EXIT);
    }
}
