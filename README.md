# HyperCube
Welcome to the official repository for HyperCube, a vibrant and engaging 2.5D rhythm-based platformer game!

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
