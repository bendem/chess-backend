#include <sstream>

#include "catch.hpp"
#include "protocol.hpp"

void assert_error(const std::string& error_type, const std::string& string) {
    const chess::json j = chess::json::parse(string);
    REQUIRE(j["status"].get<std::string>() == "nok");
    REQUIRE(error_type == j["error"].get<std::string>());
}

void assert_ok(const std::string& string) {
    const chess::json j = chess::json::parse(string);
    REQUIRE(j["status"].get<std::string>() == "ok");
}

TEST_CASE("Invalid json", "[proto]") {
    std::istringstream input(R"json([{])json");
    std::ostringstream output;
    chess::protocol proto(input, output);
    chess::board b;

    auto should_continue = proto.handle_next_command(b);

    REQUIRE(should_continue);
    assert_error("invalid_json", output.str());
}

TEST_CASE("Not an object", "[proto]") {
    std::istringstream input(R"json([])json");
    std::ostringstream output;
    chess::protocol proto(input, output);
    chess::board b;

    auto should_continue = proto.handle_next_command(b);

    REQUIRE(should_continue);
    assert_error("invalid_json", output.str());
}

TEST_CASE("Unknown command", "[proto]") {
    std::istringstream input(R"json({ "command": "hi" })json");
    std::ostringstream output;
    chess::protocol proto(input, output);
    chess::board b;

    auto should_continue = proto.handle_next_command(b);

    REQUIRE(should_continue);
    assert_error("invalid_command", output.str());
}

TEST_CASE("Empty command", "[proto]") {
    std::istringstream input("");
    std::ostringstream output;
    chess::protocol proto(input, output);
    chess::board b;

    auto should_continue = proto.handle_next_command(b);

    REQUIRE_FALSE(should_continue);
}

TEST_CASE("Missing parameter", "[proto]") {
    std::istringstream input(R"json({ "command": "serialize" })json");
    std::ostringstream output;
    chess::protocol proto(input, output);
    chess::board b;

    auto should_continue = proto.handle_next_command(b);
    REQUIRE(should_continue);
    assert_error("missing_field", output.str());
}

TEST_CASE("Correct input", "[proto]") {
    std::istringstream input(R"json({ "command": "reset" })json");
    std::ostringstream output;
    chess::protocol proto(input, output);
    chess::board b;

    auto should_continue = proto.handle_next_command(b);
    REQUIRE(should_continue);
    assert_ok(output.str());
}

TEST_CASE("Multiple inputs", "[proto]") {
    std::istringstream input(R"json({ "command": "reset" }
{ "command": "reset" })json");
    std::ostringstream output;
    chess::protocol proto(input, output);
    chess::board b;

    {
        auto should_continue = proto.handle_next_command(b);
        REQUIRE(should_continue);
        assert_ok(output.str());
    }
    output.str("");
    {
        auto should_continue = proto.handle_next_command(b);
        REQUIRE(should_continue);
        assert_ok(output.str());
    }
    output.str("");
    {
        auto should_continue = proto.handle_next_command(b);
        REQUIRE_FALSE(should_continue);
    }
}
