//
// Copyright (c) 2016 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#pragma once


#include "ofx/HTTP/JSONRequest.h"
#include "ofx/CloudPlatform/VisionRequestItem.h"


namespace ofx {
namespace CloudPlatform {


/// \brief A Google Cloud Platform Vision request.
class VisionRequest: public HTTP::JSONRequest
{
public:
    /// \brief Create an empty VisionRequest.
    VisionRequest();

    /// \brief Creates a Vision request the given RequestItem.
    /// \param requestItem The request item to add.
    VisionRequest(const VisionRequestItem& requestItem);

    /// \brief Creates a Vision request the given RequestItem.
    /// \param requestItems The request items to add.
    VisionRequest(const std::vector<VisionRequestItem>& requestItems);

    /// \brief Destroy the VisionRequest.
    virtual ~VisionRequest();

    /// \brief Add a request item.
    /// \param requestItem The request item to add.
    void addRequestItem(const VisionRequestItem& requestItem);

    /// \brief Add a request items.
    /// \param requestItems The request items to add.
    void addRequestItems(const std::vector<VisionRequestItem>& requestItems);

    /// \brief The default request URI.
    static const std::string DEFAULT_VISION_REQUEST_URI;

protected:
    /// \brief We hide this method for data integreity.
    void setJSON(const ofJson& json) override;

};



} } // namespace ofx::CloudPlatform
