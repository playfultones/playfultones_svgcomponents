ButtonComponent::ButtonComponent (const juce::String& name,
    const char* offBinaryData,
    int offBinaryDataSize,
    const char* onBinaryData,
    int onBinaryDataSize)
    : juce::Button (name), offImage (offBinaryData, offBinaryDataSize), onImage (onBinaryData, onBinaryDataSize)
{
    setOpaque (false);

    addChildComponent (offImage);
    addChildComponent (onImage);

    offImage.setInterceptsMouseClicks (false, false);
    onImage.setInterceptsMouseClicks (false, false);
}

ButtonComponent::ButtonComponent (const ButtonComponent& other)
    : juce::Button (other.getName()), offImage (other.offImage), onImage (other.onImage)
{
    setOpaque (false);

    addChildComponent (offImage);
    addChildComponent (onImage);

    offImage.setInterceptsMouseClicks (false, false);
    onImage.setInterceptsMouseClicks (false, false);

    if (other.disabledImage)
    {
        disabledImage = std::make_unique<StaticImageComponent> (*other.disabledImage);
        addChildComponent (*disabledImage);
        disabledImage->setInterceptsMouseClicks (false, false);
    }

    if (other.onDisabledImage)
    {
        onDisabledImage = std::make_unique<StaticImageComponent> (*other.onDisabledImage);
        addChildComponent (*onDisabledImage);
        onDisabledImage->setInterceptsMouseClicks (false, false);
    }

    if (other.hoverImage)
    {
        hoverImage = std::make_unique<StaticImageComponent> (*other.hoverImage);
        addChildComponent (*hoverImage);
        hoverImage->setInterceptsMouseClicks (false, false);
    }
}

ButtonComponent::~ButtonComponent() = default;

ButtonComponent ButtonComponent::withDisabledImage (const char* binaryData, int binaryDataSize) const
{
    ButtonComponent copy (*this);
    copy.disabledImage = std::make_unique<StaticImageComponent> (binaryData, binaryDataSize);
    copy.addChildComponent (*copy.disabledImage);
    copy.disabledImage->setInterceptsMouseClicks (false, false);
    return copy;
}

ButtonComponent ButtonComponent::withOnDisabledImage (const char* binaryData, int binaryDataSize) const
{
    ButtonComponent copy (*this);
    copy.onDisabledImage = std::make_unique<StaticImageComponent> (binaryData, binaryDataSize);
    copy.addChildComponent (*copy.onDisabledImage);
    copy.onDisabledImage->setInterceptsMouseClicks (false, false);
    return copy;
}

ButtonComponent ButtonComponent::withHoverImage (const char* binaryData, int binaryDataSize) const
{
    ButtonComponent copy (*this);
    copy.hoverImage = std::make_unique<StaticImageComponent> (binaryData, binaryDataSize);
    copy.addChildComponent (*copy.hoverImage);
    copy.hoverImage->setInterceptsMouseClicks (false, false);
    return copy;
}

void ButtonComponent::flash (int blinkCount, int rateHz)
{
    flashCounter = blinkCount;
    startTimerHz (rateHz);
}

void ButtonComponent::timerCallback()
{
    if (--flashCounter <= 0)
    {
        stopTimer();
        flashCounter = 0;
    }

    repaint();
}

void ButtonComponent::paintButton (juce::Graphics& g, bool isMouseOverButton, bool isButtonDown)
{
    juce::Component* imageToShow = nullptr;

    if (flashCounter > 0)
    {
        const bool showOn = (flashCounter & 1) != 0;
        imageToShow = showOn ? &onImage : &offImage;
    }
    else if (!isEnabled())
    {
        if (getToggleState() && onDisabledImage)
            imageToShow = onDisabledImage.get();
        else if (disabledImage)
            imageToShow = disabledImage.get();
        else if (getToggleState())
            imageToShow = &onImage;
        else
            imageToShow = &offImage;
    }
    else if (isMouseOverButton && hoverImage && !getToggleState())
    {
        imageToShow = hoverImage.get();
    }
    else if (getToggleState())
    {
        imageToShow = &onImage;
    }
    else
    {
        imageToShow = &offImage;
    }

    if (imageToShow != lastShownImage)
    {
        // Only toggle visibility when the selection actually changes, to avoid
        // setVisible() triggering a repaint cycle on every paint call.
        if (lastShownImage)
            lastShownImage->setVisible (false);
        if (imageToShow)
            imageToShow->setVisible (true);
        lastShownImage = imageToShow;
    }
}

void ButtonComponent::resized()
{
    if (getWidth() <= 0 || getHeight() <= 0)
        return;

    auto bounds = getLocalBounds();
    for (int i = 0; i < getNumChildComponents(); ++i)
    {
        getChildComponent (i)->setBounds (bounds);
    }
}