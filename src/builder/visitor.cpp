#include <pch.hpp>

#include "builder/visitor.hpp"

void PGNVisitor::startPgn() {
    m_Board.setFen(STARTING_FEN);
    m_NumHalfMovesSoFar = 0;
}

void PGNVisitor::move(std::string_view move, [[maybe_unused]] std::string_view comment) {
    uint64_t halfmove_cutoff = m_MaxOpeningDepth * 2;
    Move parsed_move = uci::parseSan(m_Board, move);

    uint64_t key = m_Board.hash();
    uint16_t encoded_move = parsed_move.move();

    if (m_NumHalfMovesSoFar < halfmove_cutoff) {
        add_to_map(key, encoded_move);
    }

    m_Board.makeMove(parsed_move);
    m_NumHalfMovesSoFar++;
}

void PGNVisitor::endPgn() { try_flush(); }
