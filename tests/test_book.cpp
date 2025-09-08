#include "test_framework/catch_amalgamated.hpp"
#include <pch.hpp>

#include "core/book.hpp"

static Book& opening_book = Book::instance();
static Ref<Board> board = CreateRef<Board>();

TEST_CASE("Position present") {
    board->setFen(constants::STARTPOS);
    REQUIRE(opening_book.is_book_pos(board));
}