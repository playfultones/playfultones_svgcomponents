#pragma once

class DropdownComponent : public juce::Component
{
public:
    struct DropdownItem
    {
        juce::String text;
        int id;
    };

    DropdownComponent (const juce::String& name, const char* binaryData, int binaryDataSize);
    ~DropdownComponent() override;

    void addItem (const juce::String& itemText, int itemId);
    void setSelectedId (int itemId, juce::NotificationType notification = juce::sendNotification);
    int getSelectedId() const;
    const juce::String& getSelectedText() const;

    const std::vector<DropdownItem>& getItems() const { return items; }

    std::function<void (int)> onSelectionChanged;

protected:

    virtual void paintDropdownContent (juce::Graphics& g) {}
    virtual juce::PopupMenu::Options configurePopupOptions (juce::PopupMenu::Options options);
    virtual void customizePopupMenu (juce::PopupMenu& menu) {}

    const juce::String& getComponentName() const { return componentName; }

private:
    void paintOverChildren (juce::Graphics& g) override;
    void resized() override;
    void mouseDown (const juce::MouseEvent& event) override;
    void showPopupMenu();

    StaticImageComponent backgroundImage;
    std::vector<DropdownItem> items;
    int selectedId = -1;
    juce::String componentName;
    juce::String selectedText;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DropdownComponent)
};