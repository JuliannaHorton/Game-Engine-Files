#pragma once

#ifndef _InputRegistrationCmd
#define _InputRegistrationCmd

#include "SceneCommand.h"
#include "EventType.h"
#include "../Keyboard.h"

class Inputable;

class InputRegistrationCmd : public SceneCommand
{
public:
    InputRegistrationCmd() = default;
    InputRegistrationCmd(const InputRegistrationCmd&) = delete;
    InputRegistrationCmd& operator=(const InputRegistrationCmd&) = delete;
    ~InputRegistrationCmd() = default;

    InputRegistrationCmd(Inputable* in) : ptrInput(in) {}

    void setKey(FROG_KEY k);
    void setEvent(EVENT_TYPE e);
    virtual void execute();

private:
    Inputable* ptrInput;
    FROG_KEY key;
    EVENT_TYPE event;
};


#endif _InputRegistrationCmd