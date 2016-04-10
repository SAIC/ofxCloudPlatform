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
