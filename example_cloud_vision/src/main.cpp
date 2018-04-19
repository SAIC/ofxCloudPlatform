//
// Copyright (c) 2016 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofAppRunner.h"
#include "ofApp.h"


int main()
{
    ofGLWindowSettings settings;
    settings.setSize(1280, 720);
    settings.setGLVersion(3, 2);
    settings.windowMode = OF_WINDOW;
    auto window = ofCreateWindow(settings);
    auto app = std::make_shared<ofApp>();

    return ofRunApp(app);
}
