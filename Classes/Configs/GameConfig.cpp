#include "GameConfig.h"

namespace GameConfig {

    namespace PokerRules {
        const int DECK_TOTAL_CARDS = 52;
        const float TRI_PEAKS_TABLEAU_RATIO = 0.5f;
    }

    namespace UI {

        const Size HAND_AREA_SIZE = { 1080.0f, 580.0f };
        const Vector HAND_AREA_POSITION = { 540.0f, 290.0f };

        const Size MAIN_AREA_SIZE = { 1080.0f, 1500.0f };
        const Vector MAIN_AREA_POSITION = { 540.0f, 1320.0f };

        const Size CARD_SIZE = { 140.0f, 190.0f };
        const Vector OVERLAP = { 30.0f, 40.0f };
    }
}