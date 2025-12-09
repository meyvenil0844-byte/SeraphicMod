#include <Geode/Geode.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>

using namespace geode::prelude;

// --- 1. Define Custom Difficulty IDs ---
// These are arbitrary IDs, carefully chosen to be outside the official GD range (0-10).
// We use these unique numbers to mark levels with the Seraphic difficulty.
constexpr int HYPO_SERAPHIC_ID = 90;
constexpr int OMNI_SERAPHIC_ID = 91;
constexpr int MEGA_SERAPHIC_ID = 92;
constexpr int KILO_SERAPHIC_ID = 93;
constexpr int MONO_SERAPHIC_ID = 94;
constexpr int SUB_SERAPHIC_ID = 95;
constexpr int MINI_SERAPHIC_ID = 96;

// --- 2. Hook LevelInfoLayer to Change the Icon Sprite ---
// The LevelInfoLayer is the screen where you see the level details (difficulty, stars, etc.).
class $modify(SeraphicLevelInfoLayer, LevelInfoLayer) {
    bool init(GJGameLevel* level, bool p1) {
        // Always call the original init function first
        if (!LevelInfoLayer::init(level, p1)) {
            return false;
        }

        int difficulty = level->m_difficulty;

        // Check if the level has one of our custom Seraphic IDs
        if (difficulty >= HYPO_SERAPHIC_ID && difficulty <= MINI_SERAPHIC_ID) {
            
            // --- A. Identify the correct file name based on the custom ID ---
            const char* spriteFileName;
            switch (difficulty) {
                case HYPO_SERAPHIC_ID:
                    spriteFileName = "HypoSeraphic.webp";
                    break;
                case OMNI_SERAPHIC_ID:
                    spriteFileName = "OmniSeraphic.webp";
                    break;
                case MEGA_SERAPHIC_ID:
                    spriteFileName = "MegaSeraphic.webp";
                    break;
                case KILO_SERAPHIC_ID:
                    spriteFileName = "KiloSeraphic.webp";
                    break;
                case MONO_SERAPHIC_ID:
                    spriteFileName = "MonoSeraphic.webp";
                    break;
                case SUB_SERAPHIC_ID:
                    spriteFileName = "SubSeraphic.webp";
                    break;
                case MINI_SERAPHIC_ID:
                    spriteFileName = "MiniSeraphic.webp";
                    break;
                default:
                    return true;
            }

            // --- B. Hide the default GD icon ---
            // "difficulty-sprite" is the common ID for the default difficulty icon.
            auto difficultySprite = this->getChildByIDRecursive("difficulty-sprite");
            if (difficultySprite) {
                difficultySprite->setVisible(false); // Hide the default GD icon
            }

            // --- C. Load and Position the Custom Icon ---
            
            // The full path is automatically constructed by Geode: 
            // YOUR_MOD_ID/sprites/HypoSeraphic.webp
            auto newIcon = CCSprite::create(fmt::format("{}/sprites/{}", Mod::get()->getID(), spriteFileName).c_str());

            if (newIcon && difficultySprite) {
                // Match the scale and position of the original icon for a clean look
                newIcon->setScale(difficultySprite->getScale());
                newIcon->setPosition(difficultySprite->getPosition());
                
                // Add the new icon to the same parent node as the original
                difficultySprite->getParent()->addChild(newIcon);
                
                // Give the custom icon an ID for potential future modifications
                newIcon->setID("seraphic-difficulty-sprite");
            }
        }

        return true;
    }
};
