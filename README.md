simple non-trivial gate VST3 plugin with AUv3 version (wrapped)

MacOS **only**

directions:
* ```brew install cmake```
* download/clone [steinberg vst3sdk](https://github.com/steinbergmedia/vst3sdk), [apple CoreAudio sdk](https://github.com/pongasoft/jamba/tree/8ace022ece2d1e1c639119c3268b3e0aba2deaea/audio-unit/CoreAudioSDK/CoreAudio), and this repo
* ```mkdir debug``` next to repo directory
* recommended file structure:

```
~/Documents/Code/plugin
+-- gate
|   +-- debug
|   +-- gate (this repo)
+-- sdk
|   +-- CoreAudio
|   +-- vst3sdk
```

* ```cd debug```
* ```cmake -GXcode -DCMAKE_BUILD_TYPE=Debug ../gate```
* ```xcodebuild```

build will produce a ```gate.vst3``` in ```~/Library/Audio/Plug-Ins/VST3/```, which is where a VST3-compatible host should be able to find it (try [Element](https://kushview.net/element/) for a lightweight VST3 testing host). build will also produce an Audio Unit app extension in ```debug/bin/Debug/```, where it will be automatically registered with ```pluginkit```. counterintuitively compared to auv2, nothing needs to be moved into any library folder.