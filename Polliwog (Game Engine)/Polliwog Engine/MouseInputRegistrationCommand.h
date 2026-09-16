#pragma once

#ifndef _MouseInputRegistrationCmd
#define _MouseInputRegistrationCmd

#include "SceneCommand.h"
#include "EventType.h"
#include "../Mouse.h"

class Inputable;

class MouseInputRegistrationCmd : public SceneCommand
{
public:
    MouseInputRegistrationCmd() = default;
    MouseInputRegistrationCmd(const MouseInputRegistrationCmd&) = delete;
    MouseInputRegistrationCmd& operator=(const MouseInputRegistrationCmd&) = delete;
    ~MouseInputRegistrationCmd() = default;

    MouseInputRegistrationCmd(Inputable* in) : ptrInput(in) {}

    void setKey(FROG_MOUSE k);
    void setEvent(EVENT_TYPE e);
    virtual void execute();

private:
    Inputable* ptrInput;
    FROG_MOUSE key;
    EVENT_TYPE event;
};


#endif _MouseInputRegistrationCmd