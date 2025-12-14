#ifndef PATTERNS_H
#define PATTERNS_H

#include <vector>
#include <string>
#include <initializer_list>

namespace Patterns {

    struct CellPattern {
        std::vector<std::string> lines;


        CellPattern(const std::initializer_list<std::string>& data)
            : lines(data) {}

        // Metoda pro tisk vzoru (pouze deklarace v .h)
        void print() const;
    };


    extern const CellPattern H0D0L0R0;
    extern const CellPattern H0D1L0R0;
    extern const CellPattern H1D0L0R0;
    extern const CellPattern H0D0L1R0;
    extern const CellPattern H0D0L0R1;
    extern const CellPattern H0D1L0R1;
    extern const CellPattern H0D1L1R0;
    extern const CellPattern H1D1L0R0;
    extern const CellPattern H1D0L1R0;
    extern const CellPattern H1D0L0R1;
    extern const CellPattern H0D0L1R1;
    extern const CellPattern H1D1L1R0;
    extern const CellPattern H1D1L0R1;
    extern const CellPattern H1D0L1R1;
    extern const CellPattern H0D1L1R1;
    extern const CellPattern H1D1L1R1;
    extern const CellPattern H0D0L1R1EXIT;
}

#endif // PATTERNS_H