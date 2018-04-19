//
// Copyright (c) 2016 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include "ofx/CloudPlatform/PlatformClient.h"
#include "ofx/CloudPlatform/VisionResponse.h"
#include "ofx/CloudPlatform/VisionRequest.h"
#include "ofx/CloudPlatform/VisionRequestItem.h"


namespace ofx {
namespace CloudPlatform {


/// \brief A Google Cloud Platform Vision request.
class VisionClient: public PlatformClient
{
public:
    using PlatformClient::PlatformClient;
    
    virtual ~VisionClient();

    std::vector<AnnotateImageResponse> annotate(const VisionRequestItem& item);
    
    std::vector<AnnotateImageResponse> annotate(const std::vector<VisionRequestItem>& items);

};



} } // namespace ofx::CloudPlatform
