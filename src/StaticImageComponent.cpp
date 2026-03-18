StaticImageComponent::StaticImageComponent (const char* binaryData, int binaryDataSize)
    : binaryData (binaryData), binaryDataSize (binaryDataSize)
{
    setOpaque (false);

    if (jb::Resvg::RenderTree tree; tree.loadFromBinaryData (binaryData, binaryDataSize))
    {
        svgComponent = std::make_unique<jb::SVGComponent> (std::move (tree));
        svgComponent->setCacheIdentity (binaryData, binaryDataSize);
        addAndMakeVisible (*svgComponent);
    }
}

StaticImageComponent::StaticImageComponent (const StaticImageComponent& other)
    : binaryData (other.binaryData), binaryDataSize (other.binaryDataSize)
{
    setOpaque (false);

    if (jb::Resvg::RenderTree tree; tree.loadFromBinaryData (binaryData, binaryDataSize))
    {
        svgComponent = std::make_unique<jb::SVGComponent> (std::move (tree));
        svgComponent->setCacheIdentity (binaryData, binaryDataSize);
        addAndMakeVisible (*svgComponent);
    }
}

StaticImageComponent& StaticImageComponent::operator= (const StaticImageComponent& other)
{
    if (this != &other)
    {
        binaryData = other.binaryData;
        binaryDataSize = other.binaryDataSize;

        svgComponent.reset();

        if (jb::Resvg::RenderTree tree; tree.loadFromBinaryData (binaryData, binaryDataSize))
        {
            svgComponent = std::make_unique<jb::SVGComponent> (std::move (tree));
            svgComponent->setCacheIdentity (binaryData, binaryDataSize);
            addAndMakeVisible (*svgComponent);
        }
    }
    return *this;
}

StaticImageComponent::~StaticImageComponent() = default;

void StaticImageComponent::resized()
{
    // Avoid rendering SVGs with zero dimensions (resvg panics on zero-size render)
    if (getWidth() <= 0 || getHeight() <= 0)
        return;

    if (svgComponent != nullptr)
    {
        svgComponent->setBounds (getLocalBounds());
    }
}