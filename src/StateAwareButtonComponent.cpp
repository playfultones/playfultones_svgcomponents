StateAwareButtonComponent::StateAwareButtonComponent (const juce::String& name,
    const char* offIdleBinaryData,
    int offIdleBinaryDataSize,
    const char* offDownBinaryData,
    int offDownBinaryDataSize,
    const char* onIdleBinaryData,
    int onIdleBinaryDataSize,
    const char* onDownBinaryData,
    int onDownBinaryDataSize)
    : juce::Button (name),
      offIdleImage (offIdleBinaryData, offIdleBinaryDataSize),
      offDownImage (offDownBinaryData, offDownBinaryDataSize),
      onIdleImage (onIdleBinaryData, onIdleBinaryDataSize),
      onDownImage (onDownBinaryData, onDownBinaryDataSize)
{
    setOpaque (false);

    addChildComponent (offIdleImage);
    addChildComponent (offDownImage);
    addChildComponent (onIdleImage);
    addChildComponent (onDownImage);

    offIdleImage.setInterceptsMouseClicks (false, false);
    offDownImage.setInterceptsMouseClicks (false, false);
    onIdleImage.setInterceptsMouseClicks (false, false);
    onDownImage.setInterceptsMouseClicks (false, false);
}

StateAwareButtonComponent::~StateAwareButtonComponent() = default;

void StateAwareButtonComponent::paintButton (juce::Graphics& g, bool isMouseOverButton, bool isButtonDown)
{
    for (int i = 0; i < getNumChildComponents(); ++i)
    {
        getChildComponent (i)->setVisible (false);
    }

    juce::Component* imageToShow = nullptr;

    if (getToggleState())
    {
        if (isButtonDown)
            imageToShow = &onDownImage;
        else
            imageToShow = &onIdleImage;
    }
    else
    {
        if (isButtonDown)
            imageToShow = &offDownImage;
        else
            imageToShow = &offIdleImage;
    }

    if (imageToShow)
        imageToShow->setVisible (true);
}

void StateAwareButtonComponent::resized()
{
    auto bounds = getLocalBounds();
    for (int i = 0; i < getNumChildComponents(); ++i)
    {
        getChildComponent (i)->setBounds (bounds);
    }
}
