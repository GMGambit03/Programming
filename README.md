# Programming Repository

A collection of C and Python projects exploring system design, data structures, and game development.

**Language Composition:** C (92.8%) | Python (6.6%) | Makefile (0.6%)

---

## Main Projects

### 🎮 RPG - Terminal-Based Dungeon Crawler

A turn-based RPG written in C featuring procedurally generated dungeons, data-driven gameplay, and a custom JSON parser for configuration.

**Key Features:**
- **Class Selection & Character Creation** - Multiple character archetypes with distinct stats
- **Random Dungeon Generation** - Procedurally generated dungeons with varying room layouts
- **Turn-Based Combat** - Strategic enemy encounters with weapon/armor calculations
- **Inventory & Equipment System** - Loot generation, item management, and equipment swapping
- **Data-Driven Design** - Enemies, classes, items, and dungeons defined in JSON

**Current Implementation:**
- ✅ Class selection and player creation
- ✅ Item and enemy databases
- ✅ Dungeon navigation and room exploration
- ✅ Combat system with damage calculations
- ✅ Loot generation and collection
- ✅ JSON parsing for game data

**Known Issues:**
- Loot collection occasionally fails to add all items to inventory
- Segmentation fault when reaching the boss room

**In Development:**
- Weapon/stat scaling (e.g., staves using Wisdom)
- Enhanced combat UI and descriptions
- Inventory weight system
- Save/load game state
- NPC dialogue and quests
- Crafting and shops

**Project Structure:**
```
C_Programs/rpg/
├── src/
├── data/          # JSON files for enemies, items, classes, dungeons
├── Makefile
└── README.md
```

---

### 📝 JSON Parser

A robust JSON parser written in C, custom-built to support the RPG's data-driven architecture.

**Features:**
- Parse JSON objects, arrays, strings, numbers, and booleans
- Recursive nested object/array handling
- Comprehensive error handling for malformed JSON
- Support for game data structures (enemies, items, classes)

**Current Implementation:**
- ✅ Core JSON parsing (objects, arrays, values)
- ✅ Nested structure support
- ✅ Error detection and reporting
- ✅ Integration with RPG game data

**In Development:**
- Improve error messages for malformed JSON
- Add JSON null type support
- Optimize cursor rewinding
- Add cleanup/free functions
- Extensive testing for edge cases (empty arrays/objects, deeply nested structures)

**Why Custom Parser?**
This parser is tailored specifically for the RPG project's needs, providing lightweight JSON processing without external dependencies while serving as a learning experience in parsing algorithms.

---

## Project Organization

```
Programming/
├── C_Programs/
│   ├── rpg/              # Main RPG project
│   │   ├── src/
│   │   ├── data/
│   │   └── Makefile
│   └── jsonparser/       # Standalone JSON parser
├── Python/               # Python experiments and utilities
└── README.md
```

---

## Build Instructions

### RPG
```bash
cd C_Programs/rpg
make
./rpg
```

### JSON Parser (Standalone Testing)
```bash
cd C_Programs/jsonparser
make
./test_parser
```

---

## Development Practices

**Code Quality:**
- Compile with `-Wall -Wextra` warnings enabled
- Regular AddressSanitizer runs for memory safety
- Clear malloc/realloc/free ownership tracking
- Comprehensive comments and meaningful variable/function names

**Testing Focus:**
- Empty inventory and loot scenarios
- Malformed JSON input
- Repeated dungeon navigation
- Full inventory/weight limits
- Memory leak detection

---

## Roadmap

### Near Term
- Fix boss room segfault
- Improve loot collection reliability
- Enhanced combat UI and descriptions
- Wisdom stat and scaling system

### Medium Term
- Complete inventory weight system
- Save/load game functionality
- NPC dialogue system
- Equipment and inventory UI

### Long Term
- Crafting system
- Quest framework
- Shop system with currency
- Leveling and XP progression
- Status effects
- Multiple dungeon types
- 2D graphics exploration

---

## Contributing

This is a personal learning project. Feel free to explore the code, submit issues, or suggest improvements!

---

## License

No license specified. All rights reserved.

---

**Last Updated:** September 2026  
**Repository:** [GMGambit03/Programming](https://github.com/GMGambit03/Programming)
