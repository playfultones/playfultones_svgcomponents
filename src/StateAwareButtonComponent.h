#pragma once

class StateAwareButtonComponent : public juce::Button
{
public:
    StateAwareButtonComponent (const juce::String& name,
        const char* offIdleBinaryData,
        int offIdleBinaryDataSize,
        const char* offDownBinaryData,
        int offDownBinaryDataSize,
        const char* onIdleBinaryData,
        int onIdleBinaryDataSize,
        const char* onDownBinaryData,
        int onDownBinaryDataSize);

    ~StateAwareButtonComponent() override;

    void paintButton (juce::Graphics& g, bool isMouseOverButton, bool isButtonDown) override;
    void resized() override;

private:
    StaticImageComponent offIdleImage;
    StaticImageComponent offDownImage;
    StaticImageComponent onIdleImage;
    StaticImageComponent onDownImage;

    JUCE_LEAK_DETECTOR (StateAwareButtonComponent)
};
