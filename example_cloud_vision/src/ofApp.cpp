//
// Copyright (c) 2016 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    using namespace ofxCloudPlatform;

    image.load("faulkner.jpg");

    // Load the service account credentials. Get service account credentials
    // here: https://cloud.google.com/vision/docs/auth-template/cloud-api-auth#set_up_a_service_account
    auto credentials = ServiceAccountCredentials::fromFile("service-account-credentials.json");

    // Initialize a 
    VisionClient client(credentials);

    auto response = client.annotate(VisionRequestItem(image.getPixels()));

    if (response->isSuccess())
    {
        annotations = response->responses()[0];
    }
    else
    {
        std::cout << ">>" << response->getStatus() << "<<" << std::endl;
        ofLogError() << response->getBuffer();
        ofLogError() << response->error();
    }
}


void ofApp::update()
{
}


void ofApp::draw()
{
    image.draw(0, 0);
    ofxCloudPlatform::VisionDebug::draw(annotations);
}


void ofApp::keyPressed(int key)
{
}

