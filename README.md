[![GitHub release](https://img.shields.io/github/release/Grandbrain/VoiceDuino.svg)](https://github.com/Grandbrain/VoiceDuino/releases)
[![GitHub issues](https://img.shields.io/github/issues/Grandbrain/VoiceDuino.svg)](https://github.com/Grandbrain/VoiceDuino/issues)
[![GitHub forks](https://img.shields.io/github/forks/Grandbrain/VoiceDuino.svg)](https://github.com/Grandbrain/VoiceDuino/network/members)
[![GitHub stars](https://img.shields.io/github/stars/Grandbrain/VoiceDuino.svg)](https://github.com/Grandbrain/VoiceDuino/stargazers)
[![GitHub license](https://img.shields.io/github/license/Grandbrain/VoiceDuino.svg)](https://github.com/Grandbrain/VoiceDuino/blob/master/LICENSE)

# Welcome to VoiceDuino project!

[VoiceDuino](https://github.com/Grandbrain/VoiceDuino) is an application for speech recognition to control Arduino robot. The program uses CMU Sphinx library and third-party recognition models. The program is based on Qt Framework and includes the binaries of CMU Sphinx for Windows.


## Contribute

There are several ways to contribute to VoiceDuino project:
* [Submit bugs](https://github.com/Grandbrain/VoiceDuino/issues) and help me verify fixes.
* Review the [source code changes](https://github.com/Grandbrain/VoiceDuino/pulls).


## Building

* Download and extract the [latest release](https://github.com/Grandbrain/VoiceDuino/releases) of the source code.
* Download and install the latest version of [Qt Community](https://www.qt.io/ru/download-open-source).
* Load the sketch "VoiceDuino.ino" to the Arduino device.
* Launch Qt Creator and open the project file "VoiceDuino.pro".
* Rebuild the project by clicking "Rebuild all" in the "Build" menu.
* Launch the application by clicking "Run" in the "Build" menu.


## Usage

* Select preferred microphone and sample rate from the list.
* Specify the recognition models.
* Click "Initialization" to initialize recognition.
* Click "Begin recognition" to begin recognition.
