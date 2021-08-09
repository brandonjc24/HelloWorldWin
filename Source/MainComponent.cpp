#include "MainComponent.h"





//==============================================================================
MainComponent::MainComponent()
{
    heapButton.reset( new HeapButtonWrapper<juce::TextButton>(  []() {DBG("You clicked the heap"); },
                                                                 new juce::TextButton("heapButton") 
                                                             )
                    );

    addAndMakeVisible(button);
    addAndMakeVisible( *heapButton );
    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::Font (48.0f));
    g.setColour (juce::Colours::orangered);
    g.drawText ("Hello New World!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    // toggleButton.setBounds(10, 10, 30, 30);
    button->setBounds( 498,
                        10, 
                        100, 30);
    (*heapButton)->setBounds(200, 10, 100, 30);
}
