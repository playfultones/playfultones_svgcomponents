#pragma once

class ButtonComponent : public juce::Button,
                        private juce::Timer
{
public:
    ButtonComponent (const juce::String& name,
        const char* offBinaryData,
        int offBinaryDataSize,
        const char* onBinaryData,
        int onBinaryDataSize);
    ButtonComponent (const ButtonComponent& other);
    ~ButtonComponent() override;

    ButtonComponent withDisabledImage (const char* binaryData, int binaryDataSize) const;
    ButtonComponent withOnDisabledImage (const char* binaryData, int binaryDataSize) const;
    ButtonComponent withHoverImage (const char* binaryData, int binaryDataSize) const;
    ButtonComponent withOnHoverImage (const char* binaryData, int binaryDataSize) const;

    /** Briefly flash between the on/off images without changing the toggle state.
        Useful for visual confirmation feedback*/
    void flash (int blinkCount = 4, int rateHz = 6);

    void paintButton (juce::Graphics& g, bool isMouseOverButton, bool isButtonDown) override;
    void resized() override;
    void visibilityChanged() override;

private:
    void timerCallback() override;

    StaticImageComponent offImage;
    StaticImageComponent onImage;
    std::unique_ptr<StaticImageComponent> disabledImage;
    std::unique_ptr<StaticImageComponent> onDisabledImage;
    std::unique_ptr<StaticImageComponent> hoverImage;
    std::unique_ptr<StaticImageComponent> onHoverImage;

    int flashCounter = 0;
    juce::Component* lastShownImage = nullptr;

    JUCE_LEAK_DETECTOR (ButtonComponent)
};