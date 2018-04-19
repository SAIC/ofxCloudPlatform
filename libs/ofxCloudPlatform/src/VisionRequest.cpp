//
// Copyright (c) 2016 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


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
