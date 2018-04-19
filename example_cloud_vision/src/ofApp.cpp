//
// Copyright (c) 2016 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    image.load("sunbeamkitties.jpg");

    // Load the service account credentials. Get service account credentials
    // here: https://cloud.google.com/vision/docs/auth-template/cloud-api-auth#set_up_a_service_account
    auto credentials = ofxGCP::ServiceAccountCredentials::fromFile("motorola-wearables-6bc5a9f098e7.json");

    // Initialize a vision client.
    ofxGCP::VisionClient client(credentials);

    try
    {
        ofxGCP::VisionRequestItem request(image.getPixels());
        request.addAllFeatures();
        
        annotations = client.annotate(request);
    }
    catch (const std::exception& exc)
    {
        ofLogError() << exc.what();
    }
}


void ofApp::update()
{
}


void ofApp::draw()
{
    image.draw(0, 0);
    ofxGCP::VisionDebug::draw(annotations);
}


void ofApp::keyPressed(int key)
{
}

