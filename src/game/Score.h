#ifndef SCORE_H
#define SCORE_H

#define BUFFER_LEN 128

class Score {
public:
    int score;
    int level;

    Score();

    void toString(char *str);

    void toFormattedString(char *str);

    void fromString(const char *str);

    friend bool operator<(const Score &lhs, const Score &rhs) {
        return lhs.score < rhs.score;
    }

    friend bool operator<=(const Score &lhs, const Score &rhs) {
        return !(rhs < lhs);
    }

    friend bool operator>(const Score &lhs, const Score &rhs) {
        return rhs < lhs;
    }

    friend bool operator>=(const Score &lhs, const Score &rhs) {
        return !(lhs < rhs);
    }

    friend bool operator==(const Score &lhs, const Score &rhs) {
        return lhs.score == rhs.score;
    }

    friend bool operator!=(const Score &lhs, const Score &rhs) {
        return !(lhs == rhs);
    }
};

#endif
