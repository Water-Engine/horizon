#include <pch.hpp>

#include "builder/visitor.hpp"

void PGNVisitor::startPgn() { m_Board.setFen(STARTING_FEN); }

void PGNVisitor::header(std::string_view key, std::string_view value) {}

void PGNVisitor::startMoves() {}

void PGNVisitor::move(std::string_view move, std::string_view comment) {}

void PGNVisitor::endPgn() {}
