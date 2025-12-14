#include "patterns.h"
#include <iostream>

namespace Patterns {

    // --- Implementace metody print() ---
    void CellPattern::print() const {
        for (const auto& line : lines) {
            std::cout << line << std::endl;
        }
    }

    // --- Definice všech konstantních vzorů s použitím x jako zdi ---
    // Šířka je zachována na 5 znacích.

    // H0D0L0R0: Plný box (žádné průchody)
    const CellPattern H0D0L0R0({
        "xxxxx",
        "x   x",
        "xxxxx"
    });

    // H0D1L0R0: Chybí dolní segment (D=1)
    const CellPattern H0D1L0R0({
        "xxxxx",
        "x   x",
        "x   x"
    });

    // H1D0L0R0: Chybí horní segment (H=1)
    const CellPattern H1D0L0R0({
        "x   x",
        "x   x",
        "xxxxx"
    });

    // H0D0L1R0: Chybí levý segment (L=1)
    const CellPattern H0D0L1R0({
        "xxxxx",
        "    x", // 4 mezery na začátku (index 0 prázdný)
        "xxxxx"
    });

    // H0D0L0R1: Chybí pravý segment (R=1)
    const CellPattern H0D0L0R1({
        "xxxxx",
        "x    ", // 4 mezery na konci (index 4 prázdný)
        "xxxxx"
    });

    // H0D1L0R1: Chybí D a R
    const CellPattern H0D1L0R1({
        "xxxxx",
        "x    ", // R chybí
        "x   x" // D chybí
    });

    // H0D1L1R0: Chybí D a L
    const CellPattern H0D1L1R0({
        "xxxxx",
        "    x", // L chybí
        "x   x" // D chybí
    });

    // H1D1L0R0: Chybí H a D (pouze vertikální stěny)
    const CellPattern H1D1L0R0({
        "x   x", // H chybí
        "x   x",
        "x   x" // D chybí
    });

    // H1D0L1R0: Chybí H a L
    const CellPattern H1D0L1R0({
        "x   x", // H chybí
        "    x", // L chybí
        "xxxxx"
    });

    // H1D0L0R1: Chybí H a R
    const CellPattern H1D0L0R1({
        "x   x", // H chybí
        "x    ", // R chybí
        "xxxxx"
    });

    // H0D0L1R1: Chybí L a R (pouze horní a dolní stěny)
    const CellPattern H0D0L1R1({
        "xxxxx",
        "     ", // L a R chybí
        "xxxxx"
    });

    // H1D1L1R0: Chybí H, D a L
    const CellPattern H1D1L1R0({
        "x   x", // H chybí
        "    x", // L chybí
        "x   x"  // D chybí
    });

    // H1D1L0R1: Chybí H, D a R
    const CellPattern H1D1L0R1({
        "x   x", // H chybí
        "x    ", // R chybí
        "x   x"  // D chybí
    });

    // H1D0L1R1: Chybí H, L a R
    const CellPattern H1D0L1R1({
        "x   x", // H chybí
        "     ", // L a R chybí
        "xxxxx"
    });

    // H0D1L1R1: Chybí D, L a R
    const CellPattern H0D1L1R1({
        "xxxxx",
        "     ", // L a R chybí
        "x   x"  // D chybí
    });

    // H1D1L1R1: Všechny segmenty chybí (pouze 4 rohové body)
    const CellPattern H1D1L1R1({
        "x   x", // H chybí
        "     ", // L a R chybí
        "x   x"  // D chybí
    });

    // H0D0L1R1EXIT: Cíl
    const CellPattern H0D0L1R1EXIT({
        "xxxxx",
        "   ->", // Udržujeme 5 znaků šířky
        "xxxxx"
    });

} // namespace Patterns