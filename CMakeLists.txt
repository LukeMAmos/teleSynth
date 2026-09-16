cmake_minimum_required(VERSION 3.22)
project(teleSynth VERSION 0.0.1)

include(FetchContent)

FetchContent_Declare(
	JUCE
	GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
	GIT_TAG 8.0.12
)

FetchContent_MakeAvailable(JUCE)

if(IOS)
    set(teleSynth_FORMATS Standalone)
else()
    set(teleSynth_FORMATS AU VST3 Standalone)
endif()


juce_add_plugin(teleSynth
	COMPANY_NAME                "Luke Amos"
    BUNDLE_ID                   com.lukeamos.teleSynth
    IS_SYNTH                    TRUE 
    NEEDS_MIDI_INPUT            TRUE
    NEEDS_MIDI_OUTPUT           FALSE
    IS_MIDI_EFFECT              FALSE
    COPY_PLUGIN_AFTER_BUILD     TRUE
    PLUGIN_MANUFACTURER_CODE    Lkam
    PLUGIN_CODE                 tesy
    FORMATS                      ${teleSynth_FORMATS}
    PRODUCT_NAME                "iPhone Audio"
)

if(IOS)
    set_target_properties(teleSynth_Standalone PROPERTIES
        XCODE_ATTRIBUTE_CODE_SIGN_STYLE "Automatic"
        XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "Apple Development"
        XCODE_ATTRIBUTE_ARCHS "arm64"
        XCODE_ATTRIBUTE_VALID_ARCHS "arm64"
        XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1"
        
        # Cleaned XML string without hidden formatting tabs inside tags
        CUSTOM_PLIST "<plist><dict><key>UIBackgroundModes</key><array><string>audio</string></array><key>NSMicrophoneUsageDescription</key><string>Audio playback authorization.</string></dict></plist>"
    )
    
    # Overrides iOS ambient muting defaults
    target_compile_definitions(teleSynth PRIVATE JUCE_AUDIO_ALLOWS_ANY_OS_AUDIO_RULES=1)
endif()



juce_generate_juce_header(teleSynth)

target_sources(teleSynth
    PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h
    Source/UI/DraggableComponent/DraggableComponent.h
    Source/UI/DraggableComponent/DraggableComponent.cpp

)




source_group("Source" FILES
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h
)


source_group("Source\\UI\\DraggableComponent" FILES 
    Source/UI/DraggableComponent/DraggableComponent.h
    Source/UI/DraggableComponent/DraggableComponent.cpp
)

target_compile_definitions(teleSynth
    PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(teleSynth
    PRIVATE
        juce::juce_audio_utils
	juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)