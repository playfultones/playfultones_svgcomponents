#pragma once

class StaticImageComponent : public juce::Component
{
public:
    StaticImageComponent (const char* binaryData, int binaryDataSize);
    StaticImageComponent (const StaticImageComponent& other);
    StaticImageComponent& operator= (const StaticImageComponent& other);
    ~StaticImageComponent() override;

private:
    void resized() override;

    std::unique_ptr<jb::SVGComponent> svgComponent;
    const char* binaryData;
    int binaryDataSize;

    JUCE_LEAK_DETECTOR (StaticImageComponent)
};