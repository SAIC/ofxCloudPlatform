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


std::unique_ptr<VisionResponse> VisionClient::annotate(const VisionRequestItem& item)
{
    return executeBuffered<VisionRequest, VisionResponse>(std::make_unique<VisionRequest>(item));
}


std::unique_ptr<VisionResponse> VisionClient::annotate(const std::vector<VisionRequestItem>& items)
{
    return executeBuffered<VisionRequest, VisionResponse>(std::make_unique<VisionRequest>(items));
}
    

} } // namespace ofx::CloudPlatform
