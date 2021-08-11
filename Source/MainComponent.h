#pragma once

#include <JuceHeader.h>

struct MyComp : juce::Component
{
    void resized() override {}
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

    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
