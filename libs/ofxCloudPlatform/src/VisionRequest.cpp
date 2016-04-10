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


#include "ofx/CloudPlatform/VisionRequest.h"


namespace ofx {
namespace CloudPlatform {


const std::string VisionRequest::DEFAULT_VISION_REQUEST_URI = "https://vision.googleapis.com/v1/images:annotate";


VisionRequest::VisionRequest():
    HTTP::JSONRequest(DEFAULT_VISION_REQUEST_URI,
                      Poco::Net::HTTPMessage::HTTP_1_1)
{
}

    
VisionRequest::VisionRequest(const VisionRequestItem& requestItem):
    HTTP::JSONRequest(DEFAULT_VISION_REQUEST_URI,
                      Poco::Net::HTTPMessage::HTTP_1_1)
{
    addRequestItem(requestItem);
}


VisionRequest::VisionRequest(const std::vector<VisionRequestItem>& requestItems):
    HTTP::JSONRequest(DEFAULT_VISION_REQUEST_URI,
                      Poco::Net::HTTPMessage::HTTP_1_1)
{
    addRequestItems(requestItems);
}


VisionRequest::~VisionRequest()
{
}


void VisionRequest::addRequestItem(const VisionRequestItem& requestItem)
{
    _json["requests"].push_back(requestItem.json());
}


void VisionRequest::addRequestItems(const std::vector<VisionRequestItem>& requestItems)
{
    for (auto& item: requestItems)
    {
        addRequestItem(item);
    }
}


void VisionRequest::setJSON(const ofJson& json)
{
    JSONRequest::setJSON(json);
}


} } // namespace ofx::CloudPlatform
