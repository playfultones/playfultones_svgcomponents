DropdownComponent::DropdownComponent (const juce::String& name, const char* binaryData, int binaryDataSize)
    : componentName (name), backgroundImage (binaryData, binaryDataSize)
{
    setOpaque (false);
    addAndMakeVisible (backgroundImage);
    backgroundImage.setInterceptsMouseClicks (false, false); // Background should not intercept clicks
}

DropdownComponent::~DropdownComponent() = default;

void DropdownComponent::addItem (const juce::String& itemText, int itemId)
{
    items.push_back ({ itemText, itemId });

    if (selectedId == -1 && !items.empty())
    {
        selectedId = itemId;
        selectedText = itemText;
    }
}

void DropdownComponent::setSelectedId (int itemId, juce::NotificationType notification)
{
    if (selectedId != itemId)
    {
        selectedId = itemId;

        selectedText.clear();
        for (const auto& item : items)
        {
            if (item.id == itemId)
            {
                selectedText = item.text;
                break;
            }
        }

        repaint();

        if (notification != juce::dontSendNotification && onSelectionChanged)
        {
            onSelectionChanged (itemId);
        }
    }
}

int DropdownComponent::getSelectedId() const
{
    return selectedId;
}

const juce::String& DropdownComponent::getSelectedText() const
{
    return selectedText;
}

juce::PopupMenu::Options DropdownComponent::configurePopupOptions (juce::PopupMenu::Options options)
{
    return options.withTargetComponent (this)
        .withPreferredPopupDirection (juce::PopupMenu::Options::PopupDirection::downwards)
        .withMinimumWidth (getWidth())
        .withMaximumNumColumns (1)
        .withStandardItemHeight (getHeight());
}

void DropdownComponent::paintOverChildren (juce::Graphics& g)
{
    paintDropdownContent (g);
}

void DropdownComponent::resized()
{
    backgroundImage.setBounds (getLocalBounds());
}

void DropdownComponent::mouseDown (const juce::MouseEvent& event)
{
    if (event.mods.isLeftButtonDown())
    {
        showPopupMenu();
    }
}

void DropdownComponent::showPopupMenu()
{
    juce::PopupMenu menu;

    customizePopupMenu (menu);

    for (const auto& item : items)
    {
        menu.addItem (item.id, item.text, true, item.id == selectedId);
    }

    juce::PopupMenu::Options options;
    options = configurePopupOptions (options);

    menu.showMenuAsync (options, [this] (int result) {
        if (result != 0)
        {
            setSelectedId (result, juce::sendNotification);
        }
    });
}