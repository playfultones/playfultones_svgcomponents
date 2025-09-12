#pragma once

class DropdownComponent : public juce::ComboBox
{
public:
    DropdownComponent (const juce::String& name, const char* binaryData, int binaryDataSize);
    ~DropdownComponent() override;

protected:
    virtual void paintDropdownContent (juce::Graphics& g) {}
    const juce::String& getComponentName() const { return componentName; }

private:
    void paintOverChildren (juce::Graphics& g) override;
    void resized() override;

    StaticImageComponent backgroundImage;
    juce::String componentName;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DropdownComponent)
};