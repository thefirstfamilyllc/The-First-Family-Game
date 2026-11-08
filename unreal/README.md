# The First Family: Build Your Empire — Unreal Edition

This folder is a **new Unreal Engine project scaffold**, not a playable game or finished character models. The old web prototype remains elsewhere in this repository.

## Requirements
- Unreal Engine 5.5 (the .uproject association can be changed to another compatible UE5 version)
- A supported Windows or macOS development computer
- Optional: Blender for original models

## Open
1. Download the repository to a computer.
2. Open `unreal/TheFirstFamily.uproject` with Unreal Engine.
3. Create a new **Third Person** level/template content in the editor, then save the level under `Content/Maps/Neighborhood`.
4. Import the approved character artwork as **references only**. Do not use portrait planes as characters.
5. Create or import actual skeletal meshes for Jay, Esined and Jahdē; each must have a skeleton, animations, materials and appearance customization assets.
6. Make a character-selection map with three 3D skeletal meshes and an orbit camera. On Accept, save the selected character and open the separate customization map.
7. Add gameplay only after verifying the character model and selection loop.

## Milestone acceptance criteria
- Character selection: 3 separately rotatable 3D models, correct approved likenesses, select + accept.
- Customization: isolated character preview, editable appearance assets (not screen filters), changes saved.
- World: playable third-person movement, camera, collision and one explorable block.
- Business: take a laundry order, collect it, wash/dry/fold, deliver it, receive in-game payment, track expenses.
- Vehicle: enter/exit and drive a van with collisions.
- Testing: editor playtest, packaged build, performance and save/load verification.

## Scope
Single-player offline prototype first. No copyrighted Sims/GTA assets or proprietary mechanics copied. No multiplayer/server cost assumed. Free-to-start tools do not eliminate computer or publishing costs.

## Current status
Project metadata/config only. **No playable level, skeletal mesh, blueprint, animation or tested build yet.**
