//
// Copyright (c) 2016 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include "ofMain.h"
#include "ofxCloudPlatform.h"


class ofApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);

    ofImage image;
    ofxCloudPlatform::AnnotateImageResponse annotations;
    ofxCloudPlatform::VisionClient client;

};
