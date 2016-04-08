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

    auto credentials = CloudPlatform::ServiceAccountCredentials::fromFile("motorola-wearables-6bc5a9f098e7.json");

    CloudPlatform::ServiceAccountTokenRequest request(credentials);

    CloudPlatform::ServiceAccountToken token;

    try
    {
        CloudPlatform::PlatformClient client;
        HTTP::Context context;
        HTTP::BaseResponse response;

        // Execute the request and get the response stream.
        std::istream& responseStream = client.execute(request,
                                                      response,
                                                      context);

//        respon

        // Request and response headers can be examined here.
        std::stringstream ss;

        // Copy the output to the terminal.
        Poco::StreamCopier::copyStream(responseStream, ss);

        ofJson json;
        ss >> json;

        std::cout << json.dump(4) << std::endl;

        token = CloudPlatform::ServiceAccountToken::fromJSON(json);

    }
    catch (const Poco::Exception& exc)
    {
        ofLogError("ofApp::setup") << "Got Exception " << exc.displayText() << " " << exc.code();
    }

    try
    {
        HTTP::Context context;
        HTTP::BaseResponse response;

        CloudPlatform::PlatformClient client;

        client.credentials().setBearerToken(token.accessToken());
        client.credentials().setScheme(token.tokenType());

        CloudVision::VisionRequest visionRequest;//("https://httpbin.org/post");

        visionRequest.addRequestItem(CloudVision::RequestItem("person.jpg"));
        
        // Execute the request and get the response stream.
        std::istream& responseStream = client.execute(visionRequest,
                                                      response,
                                                      context);

        // Request and response headers can be examined here.
        std::stringstream ss;

        // Copy the output to the terminal.
        Poco::StreamCopier::copyStream(responseStream, ss);

        std::cout << ss.str() << std::endl;

    }
    catch (const Poco::Exception& exc)
    {
        ofLogError("ofApp::setup") << "Got Exception " << exc.displayText() << " " << exc.code();
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

