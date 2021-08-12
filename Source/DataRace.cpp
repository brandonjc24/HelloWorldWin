/*
  ==============================================================================

    DataRace.cpp
    Created: 12 Aug 2021 3:47:16pm
    Author:  brand

  ==============================================================================
*/

#include "DataRace.h"

bool Data::operator==(const Data& other)
{
    return a == other.a && b == other.b;
}

bool Data::operator!=(const Data& other)
{
    return !(*this == other);
}

//==================================================================================
void A::run()
{
    while (true)
    {
        if (threadShouldExit())
            break;

        x = a;

        if (x != a && x != b)
        {
            auto _local = x;
            DBG("Thread A");
            std::cout << "A: "
                << "x = { .a=" << juce::String::toHexString(_local.a)
                << ", .b=" << juce::String::toHexString(_local.b) << " }" << std::endl;
        }
        wait(10);
    }
}

void B::run()
{
    while (true)
    {
        if (threadShouldExit())
            break;

        x = b;

        if (x != a && x != b)
        {
            auto _local = x;
            DBG("Thread B");
            DBG( "B: "
                << "x = { .a=" << juce::String::toHexString(_local.a)
                << ", .b=" << juce::String::toHexString(_local.b) << " }" ) ;
        }
        wait(10);
    }
}





