// =============================================================================
//
// Copyright (c) 2016 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "ofApp.h"

#include "Poco/Crypto/RSAKey.h"
#include "Poco/Crypto/RSADigestEngine.h"
#include "Poco/Base64Encoder.h"


using namespace ofx;


void ofApp::setup()
{
    using namespace CloudPlatform;
    using namespace CloudVision;

    auto credentials = ServiceAccountCredentials::fromFile("service-account-credentials.json");

    ServiceAccountTokenRequest request(credentials);

    PlatformClient client;

    auto response = client.request(request);

    if (response->isSuccess())
    {
        ServiceAccountToken token = ServiceAccountToken::fromJSON(response->json());

        std::cout << response->json().dump(4) << std::endl;

        PlatformClient client;
        client.credentials().setBearerToken(token.accessToken());
        client.credentials().setScheme(token.tokenType());

        VisionRequest visionRequest;
        visionRequest.addRequestItem(RequestItem("faulkner.jpg"));

        auto response = client.request(visionRequest);

        if (response->isSuccess())
        {
            std::cout << response->json().dump(4) << std::endl;
        }
        else
        {
            ofLogError() << response->data();

            ofLogError() << response->error();
        }
    }
    else
    {
        std::cout << ">>" << response->getStatus() << "<<" << std::endl;
        ofLogError() << response->data();
        ofLogError() << response->error();
    }
}


void ofApp::update()
{
}


void ofApp::draw()
{
}


void ofApp::keyPressed(int key)
{
}

