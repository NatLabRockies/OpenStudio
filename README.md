OpenStudio
==========

OpenStudio is a cross-platform (Windows, Mac, and Linux) collection of software tools to support whole building energy modeling using [EnergyPlus](https://github.com/NREL/EnergyPlus) and advanced daylight analysis using [Radiance](https://github.com/NREL/Radiance/).  OpenStudio is an open source project to facilitate community development, extension, and private sector adoption.

The OpenStudio SDK allows building researchers and software developers to quickly get started through its multiple entry levels, including access through C++, Ruby, Python, and C#.

More information and documentation is available at the [OpenStudio website](https://www.openstudio.net/). User support is available via the community moderated question and answer resource [unmethours.com](https://unmethours.com/questions/).

## Writing workflow results to another directory

By default, `openstudio run` follows the output paths in the OSW, which usually
place results beside the input OSW. Use `--output-directory` (or `-o`) when the
OSW is in a read-only location or when you want to keep each run separate:

```console
openstudio run --output-directory ./results -w /path/to/workflow.osw
```

The directory is resolved from the current working directory. Relative
`run_directory` and `out_name` settings in the OSW are resolved beneath it, so
their names and layout are preserved. The OSW's `root` continues to locate
inputs such as seeds, weather files, and measures. Both relative and absolute
OSW output paths are accepted when they resolve within the selected directory.
OpenStudio rejects any path, including a `..` path, that would place
`run_directory` or `out_name` outside it.

The run directory must be a child of the selected directory rather than the
directory itself. It also cannot be `reports`, `generated_files`, or a child of
either because OpenStudio manages those locations separately.

With the usual OSW defaults, the command above creates `results/run`,
`results/out.osw`, `results/reports`, and `results/generated_files`. Omitting
`--output-directory` retains the longstanding OSW path behavior.

## Installation Notes (macOS)

For development builds (artifacts downloaded from GitHub Actions), you may encounter a "Damaged" error or "Unidentified Developer" warning on macOS, especially on Apple Silicon (ARM) machines. This is because these builds are not notarized by Apple.

If you encounter these issues, please follow these steps to bypass the security check for this specific installer:

1.  **Mount the DMG**: Locate the downloaded `.dmg` file in Finder. Right-click (or Control-click) the file and select **Open**.
2.  **Launch Installer**: Inside the mounted disk image window, Right-click (or Control-click) the `OpenStudio-Installer.app` file and select **Open**.
3.  **Acknowledge Warning**: A security warning dialog will appear. Click **Open** if available. If only **OK** is available, click it (the installer might close).
4.  **Security Settings**: Open **System Settings** (or System Preferences) and navigate to **Privacy & Security**.
5.  **Allow the App**: Scroll down to the "Security" section. Look for a note about the OpenStudio application being blocked. Click the **Open Anyway** button.
6.  **Confirm Open**: A final confirmation dialog will appear. Click **Open**.
7.  **Authenticate**: Enter your system password when prompted to authorize the installation.
