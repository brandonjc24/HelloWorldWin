#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/


template<typename ButtonType>
struct ButtonWrapper : public juce::Button::Listener
{
    template<typename ... Args>
    ButtonWrapper(std::function<void()> onClickHandler, 
        Args&& ... args) : 
        onClick(std::move(onClickHandler)),
        button( std::forward<Args>(args) ...)
    {
        button.addListener(this);
    }
    ~ButtonWrapper() { button.removeListener(this); }

    void buttonClicked(juce::Button* b) override
    {
        if (onClick)
            onClick();
    }

    //operator Component* () { return &button; }
    operator juce::Component& () { return button; }
    juce::Button* operator->() { return &button; }
private:
    std::function<void()> onClick;
    ButtonType button;
};

template<typename ButtonType>
struct HeapButtonWrapper : public juce::Button::Listener
{
    HeapButtonWrapper(std::function<void()> onClickHandler, std::unique_ptr<ButtonType> heapButton) :
        onClick( std::move(onClickHandler)), button( std::move(heapButton))
    {
        setupButton();
    }

    HeapButtonWrapper(std::function<void()> onClickHandler, ButtonType* rawButtonPtr) :
        HeapButtonWrapper(onClickHandler, std::unique_ptr<ButtonType>(rawButtonPtr)) { }


    ~HeapButtonWrapper() 
    { 
        if (button.get())
            button->removeListener(this); 
    }
    void buttonClicked(juce::Button* b) override
    {
        if (onClick)
            onClick();
    }
    operator juce::Component* () 
    { 
        if (button.get() != nullptr)
            return button.get(); 
        return nullptr;
    }
    juce::Button* operator->() { return button.get(); }

private:
    void setupButton()
    {
        jassert(button.get() != nullptr);
        if (button.get())
            button->addListener(this);
    }

    std::function<void()> onClick;
    std::unique_ptr<ButtonType> button;
};

class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
    ButtonWrapper<juce::TextButton> button{ []() { DBG("You clicked"); }, "Text Button" };
    std::unique_ptr<HeapButtonWrapper<juce::TextButton>> heapButton;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
