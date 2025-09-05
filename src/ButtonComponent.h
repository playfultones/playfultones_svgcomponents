#pragma once

class ButtonComponent : public juce::Button
{
public:
    ButtonComponent (const juce::String& name,
        const char* offBinaryData,
        int offBinaryDataSize,
        const char* onBinaryData,
        int onBinaryDataSize);
    ~ButtonComponent() override;

    ButtonComponent withDisabledImage (const char* binaryData, int binaryDataSize) const;
    ButtonComponent withOnDisabledImage (const char* binaryData, int binaryDataSize) const;
    ButtonComponent withHoverImage (const char* binaryData, int binaryDataSize) const;

    void paintButton (juce::Graphics& g, bool isMouseOverButton, bool isButtonDown) override;
    void resized() override;

private:
    StaticImageComponent offImage;
    StaticImageComponent onImage;
    std::unique_ptr<StaticImageComponent> disabledImage;
    std::unique_ptr<StaticImageComponent> onDisabledImage;
    std::unique_ptr<StaticImageComponent> hoverImage;

    ButtonComponent (const ButtonComponent& other);

    JUCE_LEAK_DETECTOR (ButtonComponent)
};