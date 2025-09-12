DropdownComponent::DropdownComponent (const juce::String& name, const char* binaryData, int binaryDataSize)
    : juce::ComboBox (name), componentName (name), backgroundImage (binaryData, binaryDataSize)
{
    setOpaque (false);
    addAndMakeVisible (backgroundImage);
    backgroundImage.setInterceptsMouseClicks (false, false); // Background should not intercept clicks
    
    // Make ComboBox transparent so background shows through
    setColour (juce::ComboBox::backgroundColourId, juce::Colours::transparentBlack);
    setColour (juce::ComboBox::outlineColourId, juce::Colours::transparentBlack);
    setColour (juce::ComboBox::textColourId, juce::Colours::black);
    setColour (juce::ComboBox::arrowColourId, juce::Colours::transparentBlack);
}

DropdownComponent::~DropdownComponent() = default;


void DropdownComponent::paintOverChildren (juce::Graphics& g)
{
    paintDropdownContent (g);
}

void DropdownComponent::resized()
{
    backgroundImage.setBounds (getLocalBounds());
}

