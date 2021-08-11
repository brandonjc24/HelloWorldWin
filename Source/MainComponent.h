#pragma once

#include <JuceHeader.h>

//struct RepeatingThing;
struct DualButton : public juce::Component
{
    DualButton();
    void resized() override;

    void setButton1Handler(std::function<void()> f);
    void setButton2Handler(std::function<void()> f);

private:
//    RepeatingThing& timerThing;
    juce::TextButton button1{ "Button1" }, button2{ "Button2" };
};


struct MyAsyncHighResGui : juce::Component, juce::AsyncUpdater, juce::HighResolutionTimer
{
    void handleAsyncUpdate() override
    {
        paintColor = (paintColor + 1) % maxColors;
        repaint();
    }
    void hiResTimerCallback() override { triggerAsyncUpdate(); }

    void paint(juce::Graphics& g) override
    {
        switch (paintColor)
        {
        case 0:
            g.setColour(juce::Colours::red);
            break;
        case 1:
            g.setColour(juce::Colours::green);
            break;
        case 2:
            g.setColour(juce::Colours::blue);
            break;
        }
        g.fillAll();
    }

    MyAsyncHighResGui()
    {
        this->startTimer(1000 / 5);
    }
    ~MyAsyncHighResGui()
    {
        stopTimer();
        this->cancelPendingUpdate();
    }

private:
    int paintColor = 0;
    const int maxColors{ 3 };
};


struct RepeatingThing : juce::Component, juce::Timer
{
    void timerCallback() override
    {
        drawRed = !drawRed;
        repaint();
    }
    void paint(juce::Graphics& g) override
    {
        g.fillAll(drawRed ? juce::Colours::red : juce::Colours::green);
    }

    RepeatingThing() { startTimerHz(2); }
    ~RepeatingThing() { stopTimer(); }

private:
    bool drawRed = true;
};


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

struct OwnedArrayComponent : juce::Component, juce::Button::Listener
{
    OwnedArrayComponent();
    ~OwnedArrayComponent();
    void resized() override;
    void buttonClicked(juce::Button* ) override;
private:
    juce::OwnedArray<juce::TextButton> buttons;
};

struct MyComp : juce::Component
{
    //void resized() override {}
    void paint(juce::Graphics& g) override { g.fillAll(juce::Colours::green); }

    void mouseEnter(const juce::MouseEvent& e) override { DBG("MyComp mouseEnter");}
    void mouseExit(const juce::MouseEvent& e)  override { DBG("MyComp mouseExit");}
    void mouseMove(const juce::MouseEvent& e)  override { DBG("MyComp mouseMove " << ++counter); }

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

    void mouseEnter(const juce::MouseEvent& e) override 
    { 
        //DBG("MainComponent mouseEnter "); 
    }
    void mouseExit(const juce::MouseEvent& e) override 
    { 
        //DBG("MainComponent mouseExit " ); 
    }
    void mouseMove(const juce::MouseEvent& e) override 
    { 
        //DBG("MainComponent mouseMove " << ++counter); 
    }
    void mouseDown(const juce::MouseEvent& e) override
    {
        DBG("Mouse Click "); 
    }

private:
    //int counter = 0;
    MyComp comp;
    OwnedArrayComponent ownedArrayComp;
    RepeatingThing repeatingThing;
    DualButton dualButton;// {repeatingThing};
    MyAsyncHighResGui hiResGui;

    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
