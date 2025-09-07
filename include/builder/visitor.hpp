#pragma once

constexpr size_t MAX_BUFFER_SIZE = 64 * 1024;

struct PolyEntry {
    uint64_t key;
    uint16_t move;
    uint16_t weight;
    uint32_t learn;
};

class PGNVisitor : public pgn::Visitor {
  private:
    Board m_Board;
    uint64_t m_MaxOpeningDepth;
    std::vector<PolyEntry> m_Buffer;
    std::unordered_map<uint64_t, std::unordered_map<uint16_t, uint16_t>> m_PositionMap;

    uint64_t m_NumHalfMovesSoFar;
    
    std::ofstream m_OutFile;

  private:
    inline void flush() {
        PROFILE_FUNCTION();
        if (m_Buffer.empty()) {
            return;
        }

        m_OutFile.write(reinterpret_cast<const char*>(m_Buffer.data()),
                        m_Buffer.size() * sizeof(PolyEntry));
        m_Buffer.clear();
    }

    inline void try_flush() {
        PROFILE_FUNCTION();
        for (auto it = m_PositionMap.begin(); it != m_PositionMap.end();) {
            uint64_t key = it->first;
            auto& moves = it->second;

            for (auto move_it = moves.begin(); move_it != moves.end();) {
                uint16_t move = move_it->first;
                uint16_t weight = move_it->second;

                m_Buffer.push_back({key, move, weight, 0});
                move_it = moves.erase(move_it);

                if (m_Buffer.size() >= MAX_BUFFER_SIZE) {
                    flush();
                }
            }

            // If all moves for this key are processed, erase the key
            it = moves.empty() ? m_PositionMap.erase(it) : ++it;
        }
    }

    inline void add_to_map(uint64_t key, uint16_t move) {
        auto& move_map = m_PositionMap[key];
        if (move_map[move] < UINT16_MAX) {
            move_map[move] += 1;
        }
    }

  public:
    PGNVisitor(uint64_t depth, const std::string& out_file)
        : m_Board(), m_MaxOpeningDepth(depth), m_NumHalfMovesSoFar(0),
          m_OutFile(out_file, std::ios::binary | std::ios::out) {
        if (!m_OutFile.is_open()) {
            throw std::runtime_error("Failed to open output file");
        }
        m_Buffer.reserve(MAX_BUFFER_SIZE);
    }

    virtual ~PGNVisitor() {
        try_flush();
        flush();
    }

    virtual void startPgn() override;
    virtual void header([[maybe_unused]] std::string_view key, [[maybe_unused]] std::string_view value) override {}
    virtual void startMoves() override {}
    virtual void move([[maybe_unused]] std::string_view move, [[maybe_unused]] std::string_view comment) override;
    virtual void endPgn() override;
};