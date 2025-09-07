#pragma once

class PGNVisitor : public pgn::Visitor {
  private:
    Board m_Board;
    uint64_t m_MaxOpeningDepth;

  public:
    PGNVisitor(uint64_t depth) : m_Board(), m_MaxOpeningDepth(depth) {}
    virtual ~PGNVisitor() {}

    virtual void startPgn() override;
    virtual void header(std::string_view key, std::string_view value) override;
    virtual void startMoves() override;
    virtual void move(std::string_view move, std::string_view comment) override;
    virtual void endPgn() override;
};