# Bit Therapy C++

## What is this project?
This is a C++ porting of my Swift macOS app [BitTherapy](https://apps.apple.com/app/desktop-pets/id1575542220).

It's not feature-complete with the Swift version (and it's not intended to be), but it should run on Windows and Linux.

Currently only macOS is supported.

## ⏳ Status

### ✅ What's working
* Basic Command line interface
* Multi-monitor support
* Multi-pet support
* Tests are passing

### ⏳ Coming soon
* Windows support (maybe)

### ❌ Known issues
* Species descriptor is largely ignored
* Not all capabilities are supported

## 🛠️ Building 
> Warning!
> Before you start, you should get [Species](https://github.com/curzel-it/bit-therapy/tree/main/Species) and [Sprites](https://github.com/curzel-it/bit-therapy/tree/main/PetsAssets) from the main repo and update the path.

```bash
cd Sources/cpp
brew install googletests
brew install cmake
cd scripts
sh build.sh
./Main --species ape --species betta --screen ben
```

## 🚀 Running
Well, first follow the building steps, then tou can run the app from the command line, on any number of monitors with any number of pets.<br>
Run with `--help` for more information.

```
Allowed options:
  -h [ --help ]         Shows this help message
  --species arg         Species of pets to spawn (required)
  --screen arg          Monitors the app will display on (part of the name)
  --speed arg           Speed multiplier (default 1.0)
  --scale arg           Scale multiplier (default 1.0)
  --debug               Enable debug hud
```

### `--species`
The ids of the species you want to display...<br>
The list of bundled-in species is available [here](https://github.com/curzel-it/bit-therapy/tree/main/Species).<br>
For example:
* `--species betta` Shows a betta fish
* `--species ape --species betta` Shows an ape and betta fish
* At least one is required

### `--screen`
Monitors/screens are identified simply by part of the name.<br>
Here are some examples with the following setup:<br>
![Screenshot of Settings > Displays](docs/displays.png)<br>
* `--screen u34` only runs the app on the "U34G2G4R3"
* `--screen ben` only runs the app on "BenQ LCD"
* `--screen u34 --screen ben` runs on both displays
* Omitting the `--screen` param runs on all available displays

## ⚙️ Testing
```bash
cd Sources/cpp
brew install googletests
brew install cmake
cd scripts
sh test.sh
```