// component category
#define kAUcomponentType 'aufx'
#define kAUcomponentType1 aufx

// subtype code (unique ID)
#define kAUcomponentSubType 'gate'
#define kAUcomponentSubType1 gate

// manufacturer code
#define kAUcomponentManufacturer 'Wdcl'
#define kAUcomponentManufacturer1 Wdcl

// component descriptors
#define kAUcomponentDescription AUv3WrapperExtension
#define kAUcomponentName WordCel: Gate
#define kAUcomponentTag Effects

// A version number for the Audio Unit app extension (decimal value of hexadecimal representation with zeros between subversions)
// Hexadecimal indexes representing: [0] = main version, [1] = 0 = dot, [2] = sub version, [3] = 0 = dot, [4] = sub-sub version,
// e.g. 1.0.0 == 0x10000 == 65536, 1.2.3 = 0x10203 = 66051
#define kAUcomponentVersion 65536

// Supported number of channels of your audio unit.
// Integer indexes representing: [0] = input count, [1] = output count, [2] = 2nd input count,
// [3]=2nd output count, etc.
// e.g. 1122 == config1: [mono input, mono output], config2: [stereo input, stereo output]
// see channelCapabilities for discussion
#define kSupportedNumChannels 1122

// componentFlags (leave at 0)
#define kAUcomponentFlags 0

// componentFlagsMask (leave at 0)
#define kAUcomponentFlagsMask 0

// class name for the application delegate
#define kAUapplicationDelegateClassName AppDelegate~
