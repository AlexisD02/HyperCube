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

### 5. Open the Project in Unreal Engine
- Double-click the `.uproject` file to open the project in Unreal Engine Editor.
- If prompted to rebuild binaries, click "Yes".

### 6. Run the Game
- Once open in Unreal Engine Editor, you can press the 'Play' button to run the game in the editor.
- For a standalone game, select 'Launch' or use the packaging options to create an executable.

## Version Control Best Practices and Common Issues in UE5

### Pulling and Pushing Best Practices
- **Pull Before Starting Work**: Always pull the latest changes from the repository before starting new work to ensure you're on the latest version.
- **Push Regularly**: Push your changes regularly to keep the repository updated and minimize conflicts.

### Regular Backups
- **Frequent Commits**: Commit changes regularly to avoid losing work and to minimize the impact of potential file corruption.
- **Project Backups**: Regularly backup your entire project to a separate location or cloud storage.

### Large File Handling with Git LFS
- **Enable Git LFS**: Ensure Git Large File Storage (LFS) is set up and enabled for handling large assets, such as textures, models, and audio files.
- **Track Large Files**: Use `.gitattributes` to specify which file types should be tracked by Git LFS.
- **Pull LFS Files**: Remember to pull LFS-tracked files after cloning or pulling from the repository (`git lfs pull`).
