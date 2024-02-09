# HyperCube
Welcome to the official repository for HyperCube, a vibrant and engaging 2.5D rhythm-based platformer game!

## Steps to Set Up the Unreal Engine Project from GitHub

### 1. Clone the Repository
- Clone the GitHub repository to your local machine using your preferred Git client or command line. (Recommended GitHub Desktop)

### 2. Generate Project Files
- Navigate to the cloned project's directory using File Explorer.
- Right-click on the `.uproject` file, which is the Unreal Engine project file.
- Select "Generate Visual Studio project files" from the context menu.

### 3. Open the Solution in Visual Studio
- After the project files are generated, double-click the `.sln` file that appears in the project directory to open the project in Visual Studio.

### 4. Build the Project
- In Visual Studio, set the solution configuration to 'Development Editor' and platform to 'Win64'.
- Build the solution by right-clicking the project in the Solution Explorer and selecting "Build".

## Current Content Roadmap/Plan

### 1. Active Skills
- Active Skills will be obtained individually in each level and will serve as a requirement for progress in that level. 
- Once acquired, they will be retained throughout the rest of the game. 
- Double Jump: First acquired active skill. Allows the player to perform a second jump mid-air to achieve greater heights.
- Dash: Second acquired active skill. Allows the player to initiate a dash with a burst of speed in the direction they are moving, covering great distances without losing altitude. The player will retain the dash momentum until they touch any surface.
- Downward Slam: Last acquired active skill. Allows the player to swiftly slam into the ground, halting horizontal movement and destroying any breakable surfaces.

### 2. Power-Ups
- Power-ups are temporary abilities that either have a timer of activity when picked or are a single-use consumable that provides a certain bonus.
- Invincibility: Time-based power-up that activates on pick-up. Provides the player with immunity from obstacles and enemies for a limited time.
- 1-Up: Consumable power-up that grants the player a second chance upon death. Is automatically consumed upon death, and respawns the player a small distance back.
