#include <JuceHeader.h>


//File for storing references to colours commonly used througout the project

namespace ThemeColours{

inline constexpr juce::uint32 backgroundRaw = 0xFFFCFBF4;
inline constexpr juce::uint32 orangeRaw = 0xFFFBAE6A;
inline constexpr juce::uint32 blackRaw = 0xFF121212;
inline constexpr juce::uint32 greyRaw = 0xFFD9D9D9;


inline juce::Colour background(){return juce::Colour(backgroundRaw);}
inline juce::Colour orange(){return juce::Colour(orangeRaw);}
inline juce::Colour black(){return juce::Colour(blackRaw);}
inline juce::Colour grey(){return juce::Colour(greyRaw);}

}
