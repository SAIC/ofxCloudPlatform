//
// Copyright (c) 2016 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofx/CloudPlatform/VisionClient.h"


namespace ofx {
namespace CloudPlatform {


VisionClient::~VisionClient()
{
}


std::vector<AnnotateImageResponse> VisionClient::annotate(const VisionRequestItem& item)
{
    std::vector<VisionRequestItem> items = { item };
    return annotate(items);
}


std::vector<AnnotateImageResponse> VisionClient::annotate(const std::vector<VisionRequestItem>& items)
{
    VisionRequest request(items);
    auto response = execute(request);

    if (!response->isSuccess() || !response->isJson())
    {
        throw Poco::Net::HTTPException(response->statusAndReason());
    }
 
    ofJson json = response->json();
        
    std::vector<AnnotateImageResponse> responses;
    
    auto iter = json.cbegin();
    while (iter != json.cend())
    {
        const auto& key = iter.key();
        const auto& value = iter.value();
        
        if (key == "responses")
        {
            for (const auto& response: value)
            {
                responses.push_back(AnnotateImageResponse::fromJSON(response));
            }
        }
        else ofLogWarning("VisionClient::annotate") << "Unknown key: " << key;
        
        ++iter;
    }
    
    return responses;
}
    

} } // namespace ofx::CloudPlatform
