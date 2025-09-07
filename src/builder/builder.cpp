#include <pch.hpp>

#include "builder/builder.hpp"
#include "builder/visitor.hpp"

std::vector<std::filesystem::path> collect_pgns(std::string pgn_parent_directory,
                                                std::string pgn_file_extension) {
    if (!std::filesystem::exists(pgn_parent_directory)) {
        return {};
    }

    std::vector<std::filesystem::path> paths;
    try {
        for (const auto& entry :
             std::filesystem::recursive_directory_iterator(pgn_parent_directory)) {
            if (entry.is_regular_file() && entry.path().extension() == pgn_file_extension) {
                paths.push_back(entry.path());
            }
        }
    } catch (const std::exception& e) {
        fmt::eprintln("Error: {}", e.what());
        return {};
    }

    return paths;
}

int make_book(int depth, const std::vector<std::filesystem::path>& files, std::string output_file) {
    if (files.empty()) {
        return 1;
    }

    std::ifstream file_stream(files[0]);
    pgn::StreamParser parser(file_stream);

    PGNVisitor visitor(depth, output_file);
    auto error = parser.readGames(visitor);

    if (error.hasError()) {
        fmt::eprintln(error.message());
        return error.code();
    }

    return 0;
}
