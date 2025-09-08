#include <pch.hpp>

#include "launcher.hpp"

#include "core/book.hpp"

int main(int argc, char* argv[]) {
    PROFILE_BEGIN_SESSION("Horizon", "Horizon-Main.json");
#if 1
    int status = launch(argc, argv);
    exit(status);
#else
    // Example using using water's API
    auto board = CreateRef<Board>();
    auto& book = Book::instance();
    DBG(book.is_book_pos(board));
#endif
    PROFILE_END_SESSION();
}