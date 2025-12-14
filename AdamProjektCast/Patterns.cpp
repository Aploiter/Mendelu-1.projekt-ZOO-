#include "patterns.h"
#include <iostream>

namespace Patterns {

    // --- Implementace metody print() ---
    // Definuje, jak se vzor vypíše na konzoli.
    void CellPattern::print() const {
        for (const auto& line : lines) {
            std::cout << line << std::endl;
        }
    }

    // --- Definice všech konstantních vzorů (H = Horní, D = Dolní, L = Levá, R = Pravá) ---
    // Pamatujte: 0 = Plný/Nepřerušovaný segment, 1 = Průchozí/Chybějící segment

    // H0D0L0R0: Plný box (žádné průchody)
    const CellPattern H0D0L0R0({
        "#####",
        "#   #",
        "#####"
    });

    // H0D1L0R0: Chybí dolní segment (D=1)
    const CellPattern H0D1L0R0({
        "#####",
        "#   #",
        "#   #"
    });

    // H1D0L0R0: Chybí horní segment (H=1)
    const CellPattern H1D0L0R0({
        "#   #",
        "#   #",
        "#####"
    });

    // H0D0L1R0: Chybí levý segment (L=1)
    const CellPattern H0D0L1R0({
        "#####",
        "    #",
        "#####"
    });

    // H0D0L0R1: Chybí pravý segment (R=1)
    const CellPattern H0D0L0R1({
        "#####",
        "#    ",
        "#####"
    });

    // H0D1L0R1: Chybí D a R
    const CellPattern H0D1L0R1({
        "#####",
        "#    ",
        "#   #"
    });

    // H0D1L1R0: Chybí D a L
    const CellPattern H0D1L1R0({
        "#####",
        "    #",
        "#   #"
    });

    // H1D1L0R0: Chybí H a D (pouze vertikální stěny)
    const CellPattern H1D1L0R0({
        "#   #",
        "#   #",
        "#   #"
    });

    // H1D0L1R0: Chybí H a L
    const CellPattern H1D0L1R0({
        "#   #",
        "    #",
        "#####"
    });

    // H1D0L0R1: Chybí H a R
    const CellPattern H1D0L0R1({
        "#   #",
        "#    ",
        "#####"
    });

    // H0D0L1R1: Chybí L a R (pouze horní a dolní stěny)
    const CellPattern H0D0L1R1({
        "#####",
        "     ",
        "#####"
    });

    // H1D1L1R0: Chybí H, D a L
    const CellPattern H1D1L1R0({
        "#   #",
        "    #",
        "#   #"
    });

    // H1D1L0R1: Chybí H, D a R
    const CellPattern H1D1L0R1({
        "#   #",
        "#    ",
        "#   #"
    });

    // H1D0L1R1: Chybí H, L a R
    const CellPattern H1D0L1R1({
        "#   #",
        "     ",
        "#####"
    });

    // H0D1L1R1: Chybí D, L a R
    const CellPattern H0D1L1R1({
        "#####",
        "     ",
        "#   #"
    });

    // H1D1L1R1: Všechny segmenty chybí (pouze 4 rohové body)
    const CellPattern H1D1L1R1({
        "#   #",
        "     ",
        "#   #"
    });

    const CellPattern H0D0L1R1EXIT({
        "#####",
        "   ->",
        "#####"
    });

} // namespace Patterns

