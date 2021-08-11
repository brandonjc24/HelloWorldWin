#pragma once

#include <JuceHeader.h>

struct Widget : juce::Component
{
    void paint(juce::Graphics& g) override 
    { 
        g.fillAll(juce::Colours::red); 
        g.setColour(juce::Colours::black);
        g.drawRect(getLocalBounds().reduced(2));

        g.drawFittedText(juce::String(num), getLocalBounds(), juce::Justification::centred, 1);
    }

    Widget(int i) : num(i) {}

private:
    int num = 0;
};

struct OwnedArrayComponent : juce::Component
{
    OwnedArrayComponent()
    {
        for (int ii = 0; ii < 10; ++ii)
        {
            auto* widget = widgets.add(new Widget(ii));
            addAndMakeVisible(widget);
        }
    }

    void resized() override
    {
        auto width = getWidth() / static_cast<float>(widgets.size());
        int x = 0;
        auto h = getHeight();

        for (auto* widget : widgets)
        {
            widget->setBounds(x, 0, width, h);
            x += width;
        }

    }

    juce::OwnedArray<Widget> widgets;
};

struct MyComp : juce::Component
{
    //void resized() override {}
    void paint(juce::Graphics& g) override { g.fillAll(juce::Colours::green); }

    void mouseEnter(const juce::MouseEvent& e) override { DBG("MyComp mouseEnter"); }
    void mouseExit(const juce::MouseEvent& e) override { DBG("MyComp mouseExit"); }
    void mouseMove(const juce::MouseEvent& e) override { DBG("MyComp mouseMove " << ++counter); }

private:
    int counter = 0;
};

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void mouseEnter(const juce::MouseEvent& e) override { DBG("MainComponent mouseEnter "); }
    void mouseExit(const juce::MouseEvent& e) override { DBG("MainComponent mouseExit " ); }
    void mouseMove(const juce::MouseEvent& e) override { DBG("MainComponent mouseMove " << ++counter); }

private:
    int counter = 0;
    MyComp comp;
    OwnedArrayComponent ownedArrayComp;

    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
